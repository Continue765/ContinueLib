#!/usr/bin/env python3
# 生成 VS Code 片段文件 template/cpp.json。

import json
import os
import sys

ROOT = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(ROOT, "template", "cpp.json")
ALIAS = {"template": "acm"}
SKIP = {".git", "out", "template", ".vscode"}

snippets = {}


def add(path, prefix):
    if prefix in snippets:
        sys.exit(f"error: duplicate prefix '{prefix}'  ({path})")
    with open(path, encoding="utf-8") as f:
        body = [line.rstrip("\r\n").replace("\\", "\\\\") for line in f]
    rel = os.path.relpath(path, ROOT)
    snippets[prefix] = {"prefix": prefix, "body": body, "description": rel}
    print(f"  {prefix:<28} <- {rel}", file=sys.stderr)


tdir = os.path.join(ROOT, "template")
for name in sorted(os.listdir(tdir)):
    if name.endswith(".cpp"):
        stem = name[:-len(".cpp")]
        add(os.path.join(tdir, name), ALIAS.get(stem, stem.lower()))

for dirpath, dirnames, filenames in os.walk(ROOT):
    dirnames[:] = sorted(d for d in dirnames if d not in SKIP)
    for name in sorted(filenames):
        if name.endswith(".hpp"):
            add(os.path.join(dirpath, name), name[:-len(".hpp")].lower())

with open(OUT, "w", encoding="utf-8") as f:
    json.dump(snippets, f, indent=2, ensure_ascii=False)
    f.write("\n")

print(f"{len(snippets)} snippets -> {os.path.relpath(OUT, ROOT)}", file=sys.stderr)
