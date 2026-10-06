#!/usr/bin/env python3
"""Expand ContinueLib headers and conservatively remove unused declarations."""
import re
import sys
from collections import defaultdict, deque
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent
PRAGMA_ONCE_RE = re.compile(r"^[ \t]*#[ \t]*pragma[ \t]+once[ \t]*(?:\r?\n)?$")
INCLUDE_RE = re.compile(
    r'^[ \t]*#[ \t]*include[ \t]*'
    r'(?:<(?P<angle>[^>\r\n]+)>|"(?P<quoted>[^"\r\n]+)")'
    r'[^\r\n]*(?P<newline>\r?\n)?$'
)


class Expander:
    def __init__(self, root):
        self.root = root
        self.expanded = set()
        self.resolve_cache = {}

    def resolve(self, parent, name, angle):
        key = (parent, name, angle)
        if key in self.resolve_cache:
            return self.resolve_cache[key]

        include_path = Path(name.replace("\\", "/"))
        if include_path.is_absolute():
            self.resolve_cache[key] = None
            return None

        bases = (self.root,) if angle else (parent, self.root)
        for base in bases:
            candidate = (base / include_path).resolve()
            if angle and not candidate.is_relative_to(self.root):
                continue
            if candidate.is_file():
                self.resolve_cache[key] = candidate
                return candidate

        self.resolve_cache[key] = None
        return None

    def expand(self, path):
        path = path.resolve()
        if path in self.expanded:
            return ""
        self.expanded.add(path)

        try:
            source = path.read_text(encoding="utf-8")
        except OSError as exc:
            raise SystemExit(f"错误：无法读取 {path}: {exc}") from exc

        output = []
        for line in source.splitlines(keepends=True):
            if PRAGMA_ONCE_RE.match(line):
                continue
            match = INCLUDE_RE.match(line)
            if not match:
                output.append(line)
                continue

            angle_name = match.group("angle")
            quoted_name = match.group("quoted")
            target = self.resolve(path.parent, angle_name or quoted_name, angle_name is not None)
            if target is None:
                output.append(line)
                continue

            replacement = self.expand(target)
            newline = match.group("newline") or ""
            if newline and replacement and not replacement.endswith(("\n", "\r")):
                replacement += newline
            output.append(replacement)

        return "".join(output)


IDENT_RE = re.compile(r"[A-Za-z_]\w*")
RAW_STRING_RE = re.compile(r'(?:u8|u|U|L)?R"([^ ()\\\t\r\n]{0,16})\(')
STRING_RE = re.compile(r'''(?:u8|u|U|L)?(["'])''')
DIRECTIVE_RE = re.compile(r"^[ \t]*#")
TEMPLATE_RE = re.compile(r"\s*template\s*<")
SKIP_FUNCTION_NAMES = {
    "alignas", "catch", "decltype", "if", "noexcept", "requires",
    "sizeof", "static_assert", "switch", "typeid", "while",
}
SUSPICIOUS_PREFIX_RE = re.compile(
    r"\b(?:alignas|decltype|requires|__attribute__)\b|\[\[|\boperator\b"
)
QUALIFIED_NAME_RE = re.compile(r"(?:[A-Za-z_]\w*::)+$")


@dataclass(frozen=True)
class Declaration:
    start: int
    end: int
    name: str
    kind: str


def blank(chars, start, end):
    for i in range(start, end):
        if chars[i] not in "\r\n":
            chars[i] = " "


def mask_literals_and_comments(source):
    """Blank comments and literals while preserving offsets and newlines."""
    chars = list(source)
    i = 0
    while i < len(source):
        if source.startswith("//", i):
            end = source.find("\n", i)
            if end == -1:
                end = len(source)
            blank(chars, i, end)
            i = end
            continue
        if source.startswith("/*", i):
            end = source.find("*/", i + 2)
            end = len(source) if end == -1 else end + 2
            blank(chars, i, end)
            i = end
            continue

        raw = RAW_STRING_RE.match(source, i)
        if raw:
            closing = ")" + raw.group(1) + '"'
            end = source.find(closing, raw.end())
            end = len(source) if end == -1 else end + len(closing)
            blank(chars, i, end)
            i = end
            continue

        string = STRING_RE.match(source, i)
        if string:
            quote = string.group(1)
            end = string.end()
            while end < len(source):
                if source[end] == "\\":
                    end += 2
                elif source[end] == quote:
                    end += 1
                    break
                else:
                    end += 1
            end = min(end, len(source))
            blank(chars, i, end)
            i = end
            continue
        i += 1
    return chars


def mask_directives(source, chars):
    """Blank preprocessor lines for C++ scanning and retain their identifiers."""
    directives = []
    directive_texts = []
    directive_names = set()
    macro_pasting = False
    lines = source.splitlines(keepends=True)
    offset = 0
    i = 0
    while i < len(lines):
        line = lines[i]
        end = offset + len(line)
        if DIRECTIVE_RE.match("".join(chars[offset:end])):
            start = offset
            directive = [line]
            while line.rstrip("\r\n").endswith("\\") and i + 1 < len(lines):
                i += 1
                line = lines[i]
                end += len(line)
                directive.append(line)

            directive_text = "".join(directive)
            directives.append((start, end))
            directive_texts.append((start, end, directive_text))
            directive_names.update(IDENT_RE.findall(directive_text))
            define = re.match(
                r"\s*#\s*define\s+[A-Za-z_]\w*(?:\s*\([^)]*\))?(.*)",
                directive_text,
                re.DOTALL,
            )
            if define and ("##" in define.group(1) or "#" in define.group(1)):
                macro_pasting = True
            blank(chars, start, end)

        offset = end
        i += 1
    controls = []
    for start, _, text in directive_texts:
        match = re.match(r"\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(?:\s+([A-Za-z_]\w*))?", text)
        if match:
            controls.append((start, match.group(1), match.group(2)))

    # Only accept a plain outer include guard. Other conditional compilation
    # can change which declarations exist, so leave those files untouched.
    conditional_safe = not controls
    if len(controls) == 2 and controls[0][1] == "ifndef" and controls[1][1] == "endif":
        guard_name = controls[0][2]
        first_control, last_control = controls[0][0], controls[1][0]
        define_guard = any(
            start > first_control
            and start < last_control
            and re.match(rf"\s*#\s*define\s+{re.escape(guard_name or '')}\b", text)
            for start, _, text in directive_texts
        )
        conditional_safe = define_guard

    return directives, directive_names, macro_pasting, conditional_safe


def skip_template_prefix(prefix):
    """Skip leading template parameter lists; return the remaining prefix."""
    pos = 0
    while True:
        match = TEMPLATE_RE.match(prefix, pos)
        if not match:
            return prefix[pos:]
        depth = 1
        i = match.end()
        while i < len(prefix) and depth:
            if prefix[i] == "<":
                depth += 1
            elif prefix[i] == ">":
                depth -= 1
            i += 1
        if depth:
            return ""
        pos = i


def function_name(prefix):
    prefix = skip_template_prefix(prefix)
    if not prefix or SUSPICIOUS_PREFIX_RE.search(prefix):
        return None

    angle_depth = 0
    for i, char in enumerate(prefix):
        if char == "<":
            angle_depth += 1
        elif char == ">" and angle_depth:
            angle_depth -= 1
        elif char == "(" and angle_depth == 0:
            before = prefix[:i]
            match = re.search(r"([A-Za-z_]\w*)\s*$", before)
            if not match:
                return None
            name = match.group(1)
            if name in SKIP_FUNCTION_NAMES:
                return None
            if "=" in before or QUALIFIED_NAME_RE.search(before[:match.start()]):
                return None
            return name
    return None


def class_name(prefix):
    """Return a simple top-level class/struct name, or None when uncertain."""
    prefix = skip_template_prefix(prefix)
    if not prefix or re.search(r"\b(?:typedef|using|operator|__attribute__)\b", prefix):
        return None
    match = re.search(r"\b(?:class|struct|union)\s+([A-Za-z_]\w*)", prefix)
    if not match:
        return None
    suffix = prefix[match.end():].strip()
    # Explicit specialisations and unusual attributes need semantic parsing.
    if suffix.startswith("<") or "[[" in suffix:
        return None
    return match.group(1)


def matching_brace(code, opening):
    depth = 0
    for i in range(opening, len(code)):
        if code[i] == "{":
            depth += 1
        elif code[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    return None


def find_functions(code, directives):
    functions = []
    directive_index = 0
    brace_depth = 0
    top_level_block = False
    paren_depth = 0
    bracket_depth = 0
    statement_start = 0
    i = 0

    while i < len(code):
        while directive_index < len(directives) and directives[directive_index][1] <= i:
            directive_index += 1
        in_directive = (
            directive_index < len(directives)
            and directives[directive_index][0] <= i < directives[directive_index][1]
        )
        if in_directive:
            i = directives[directive_index][1]
            continue

        char = code[i]
        if brace_depth:
            if char == "{":
                brace_depth += 1
            elif char == "}":
                brace_depth -= 1
                if brace_depth == 0 and top_level_block:
                    statement_start = i + 1
            i += 1
            continue

        if char == "(":
            paren_depth += 1
        elif char == ")" and paren_depth:
            paren_depth -= 1
        elif char == "[":
            bracket_depth += 1
        elif char == "]" and bracket_depth:
            bracket_depth -= 1
        elif char == ";" and paren_depth == 0 and bracket_depth == 0:
            statement_start = i + 1
        elif char == "{" and paren_depth == 0 and bracket_depth == 0:
            name = function_name(code[statement_start:i])
            end = matching_brace(code, i)
            if end is None:
                break
            has_directive = any(start < end and stop > i for start, stop in directives)
            next_token = end + 1
            while next_token < len(code) and code[next_token].isspace():
                next_token += 1
            function_try_block = code.startswith("catch", next_token)
            if name and not has_directive and not function_try_block:
                start = statement_start
                while start < i and code[start].isspace():
                    start += 1
                functions.append(Declaration(start, end + 1, name, "function"))
                i = end + 1
                statement_start = i
                paren_depth = bracket_depth = 0
                continue
            brace_depth = 1
            top_level_block = True
        elif char == "{" and (paren_depth or bracket_depth):
            brace_depth = 1
            top_level_block = False
        elif char == "}" and paren_depth == 0 and bracket_depth == 0:
            statement_start = i + 1
        i += 1

    return functions


def find_classes(code, directives):
    """Find simple top-level class/struct definitions as whole units."""
    classes = []
    directive_index = 0
    brace_depth = 0
    paren_depth = 0
    bracket_depth = 0
    statement_start = 0
    i = 0

    while i < len(code):
        while directive_index < len(directives) and directives[directive_index][1] <= i:
            directive_index += 1
        if (
            directive_index < len(directives)
            and directives[directive_index][0] <= i < directives[directive_index][1]
        ):
            i = directives[directive_index][1]
            continue

        char = code[i]
        if brace_depth:
            if char == "{":
                brace_depth += 1
            elif char == "}":
                brace_depth -= 1
                if brace_depth == 0:
                    statement_start = i + 1
            i += 1
            continue

        if char == "(":
            paren_depth += 1
        elif char == ")" and paren_depth:
            paren_depth -= 1
        elif char == "[":
            bracket_depth += 1
        elif char == "]" and bracket_depth:
            bracket_depth -= 1
        elif char == ";" and paren_depth == 0 and bracket_depth == 0:
            statement_start = i + 1
        elif char == "{" and paren_depth == 0 and bracket_depth == 0:
            name = class_name(code[statement_start:i])
            end = matching_brace(code, i)
            if end is None:
                break
            after = end + 1
            while after < len(code) and code[after].isspace():
                after += 1
            has_directive = any(start < end and stop > i for start, stop in directives)
            # A declaration followed directly by ';' is safe to remove as a unit.
            # `struct X {} value;` also declares an object, so leave it alone.
            if name and after < len(code) and code[after] == ";" and not has_directive:
                start = statement_start
                while start < i and code[start].isspace():
                    start += 1
                classes.append(Declaration(start, after + 1, name, "class"))
                i = after + 1
                statement_start = i
                paren_depth = bracket_depth = 0
                continue
            brace_depth = 1
        i += 1

    return classes


def identifiers(text):
    return set(IDENT_RE.findall(text))


def deletion_span(source, declaration):
    """Expand a declaration range to its full lines when it stands alone."""
    start = source.rfind("\n", 0, declaration.start) + 1
    if source[start:declaration.start].strip():
        start = declaration.start

    end = source.find("\n", max(declaration.start, declaration.end - 1))
    end = len(source) if end == -1 else end + 1
    if source[declaration.end:end].strip():
        end = declaration.end
    return start, end


def skip_blank_lines(source, pos):
    """Skip blank lines after a removed declaration, preserving other text."""
    while pos < len(source):
        newline = source.find("\n", pos)
        end = len(source) if newline == -1 else newline + 1
        if source[pos:end].strip():
            break
        pos = end
    return pos


def shrink(source):
    chars = mask_literals_and_comments(source)
    directives, directive_names, macro_pasting, conditional_safe = mask_directives(source, chars)
    code = "".join(chars)

    # Token pasting/stringification can hide a function reference from a text scan.
    if macro_pasting or not conditional_safe or re.search(r"\b(?:asm|__asm__)\b", code):
        return source, []

    declarations = find_functions(code, directives) + find_classes(code, directives)
    if not declarations or not any(
        declaration.name == "main" and declaration.kind == "function"
        for declaration in declarations
    ):
        return source, []

    names = {declaration.name for declaration in declarations}
    covered = [False] * len(code)
    for declaration in declarations:
        covered[declaration.start:declaration.end] = [True] * (
            declaration.end - declaration.start
        )

    outside = "".join(char for i, char in enumerate(code) if not covered[i])
    roots = (identifiers(outside) | directive_names) & names
    roots.add("main")

    dependencies = defaultdict(set)
    for declaration in declarations:
        dependencies[declaration.name].update(
            identifiers(code[declaration.start:declaration.end]) & names
        )

    live = set()
    queue = deque(roots)
    while queue:
        name = queue.popleft()
        if name in live:
            continue
        live.add(name)
        queue.extend(dependencies[name] - live)

    removed = [declaration for declaration in declarations if declaration.name not in live]
    if not removed:
        return source, []

    output = []
    pos = 0
    for declaration in sorted(removed, key=lambda item: item.start):
        start, end = deletion_span(source, declaration)
        if start < pos:
            continue
        output.append(source[pos:start])
        pos = skip_blank_lines(source, end)
    output.append(source[pos:])
    return "".join(output), removed

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 amalgamate.py main.cpp", file=sys.stderr)
        raise SystemExit(1)

    source = Path(sys.argv[1]).resolve()
    if not source.is_file():
        print(f"错误：找不到输入文件 {sys.argv[1]}", file=sys.stderr)
        raise SystemExit(1)

    expanded = Expander(ROOT).expand(source)
    result, _ = shrink(expanded)
    sys.stdout.write(result)


if __name__ == "__main__":
    main()
