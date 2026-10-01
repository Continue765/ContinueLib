#!/usr/bin/env python3
# 生成并编译 ICPC 模板 PDF 用法：./build.py
import shutil
import subprocess
import sys
import time
import tomllib
from itertools import count
from pathlib import Path

CFG_NAME = "config.toml"
ROOT_CFG = Path(CFG_NAME)
MAIN = Path("out/main.tex")
BODY = Path("out/body.tex")
OUT = Path("out")
HEADINGS = ("\\section", "\\subsection", "\\subsubsection")
KEYS = {"name", "file", "dir", "tex"}
MAX_PASSES = 6


def read_items(cfg):
    """读一个 config.toml，校验后返回 [{name, file, dir, tex}, ...]。"""
    if not cfg.is_file():
        sys.exit(f"错误：找不到 {cfg}（请在仓库根目录运行）")
    try:
        data = tomllib.loads(cfg.read_text(encoding="utf-8"))
    except tomllib.TOMLDecodeError as e:
        sys.exit(f"错误：{cfg} 不是合法的 TOML：{e}")
    items = []
    for it in data.get("item", []):
        if bad := set(it) - KEYS:
            sys.exit(f"错误：{cfg} 里出现无法识别的字段 {sorted(bad)}")
        name = it.get("name")
        if not name:
            sys.exit(f"错误：{cfg} 有条目缺少 name")
        if ("file" in it) == ("dir" in it):
            sys.exit(f"错误：{cfg} 的条目「{name}」必须恰好给出 file 或 dir 之一")
        for key in ("file", "tex"):
            if it.get(key) and not (cfg.parent / it[key]).is_file():
                sys.exit(f"错误：{cfg} 的条目「{name}」引用了不存在的文件 {cfg.parent / it[key]}")
        items.append({"name": name, "file": it.get("file"),
                      "dir": it.get("dir"), "tex": it.get("tex")})
    return items


def emit_tex(out, cfg, depth):
    """按 config 层级写出 tex；depth 决定标题级别，路径相对当前工作目录。"""
    if depth >= len(HEADINGS):
        sys.exit(f"错误：{cfg} 层级过深，生成器只支持到 {HEADINGS[-1]}"
                 f"（第 {depth + 1} 层无法表示）")
    for it in read_items(cfg):
        label = HEADINGS[depth][1:]
        src = it["dir"] or it["file"] or ""
        print(f"{'  ' * depth}{label}: {it['name']}" + (f" ({src})" if src else ""))
        out.write(f"{HEADINGS[depth]}{{{it['name']}}}\n")
        if it["tex"]:
            out.write("\\begin{spacing}{1.5}\n"
                      f"\\input{{{cfg.parent / it['tex']}}}\n"
                      "\\end{spacing}\n")
        if it["dir"]:
            emit_tex(out, cfg.parent / it["dir"] / CFG_NAME, depth + 1)
        if it["file"]:
            out.write(f"\\lstinputlisting{{{cfg.parent / it['file']}}}\n")


def generate():
    with BODY.open("w", encoding="utf-8") as out:
        emit_tex(out, ROOT_CFG, 0)
    print(f">> 生成 {BODY}")


def build_pdf():
    if not MAIN.is_file():
        sys.exit(f"错误：找不到 {MAIN}。它是手写文件（不入库），不会被构建过程生成或删除。")
    if not shutil.which("xelatex"):
        sys.exit("错误：找不到 xelatex。请安装 TeX Live（需 XeLaTeX），"
                 "并确认中文所需的 fandol 包已安装。")
    for stale in ("main.aux", "main.toc", "main.out", "main.pdf", "missfont.log", "texput.log"):
        (OUT / stale).unlink(missing_ok=True)
    for old in OUT.glob("xelatex-*.log"):
        old.unlink()

    # 必须编译到 .aux/.toc 稳定为止：目录自身可能跨页，页数一变所有页码都会挪，
    # 固定两遍会留下差 1 的目录（实测本模板要 3 遍）。
    snap = None
    for i in count(1):
        if i > MAX_PASSES:
            sys.exit(f"错误：编译 {MAX_PASSES} 遍后 .aux/.toc 仍未稳定，检查是否互相引用成环。")
        log = OUT / f"xelatex-{i}.log"
        print(f">> xelatex 第 {i} 遍（日志：{log}）")
        start = time.monotonic()
        with log.open("w", encoding="utf-8") as lf:
            rc = subprocess.run(
                ["xelatex", "-interaction=nonstopmode", "-halt-on-error",
                 f"-output-directory={OUT}", str(MAIN)],
                stdout=lf, stderr=subprocess.STDOUT).returncode
        if rc:
            tail = log.read_text(encoding="utf-8", errors="replace").splitlines()[-20:]
            sys.exit("xelatex 第 %d 遍失败，末尾日志：\n%s\n（完整日志：%s 与 %s）"
                     % (i, "\n".join(tail), log, OUT / "main.log"))
        spent = time.monotonic() - start
        cur = tuple((OUT / f).read_bytes() if (OUT / f).is_file() else b""
                    for f in ("main.aux", "main.toc"))
        if cur == snap:
            print(f"   第 {i} 遍后 .aux/.toc 未再变化，编译结束（共 {i} 遍，"
                  f"本遍 {spent:.1f} 秒）")
            break
        snap = cur
        print(f"   第 {i} 遍完成，耗时 {spent:.1f} 秒")


def main():
    generate()
    build_pdf()
    print(f">> 完成：{OUT / 'main.pdf'}")


if __name__ == "__main__":
    main()
