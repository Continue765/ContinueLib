#!/usr/bin/env python3
# 生成并编译 ICPC 模板 PDF 用法：./build.py
import shutil
import subprocess
import sys
import time
import tomllib
from pathlib import Path

CFG_NAME = "config.toml"
ROOT_CFG = Path(CFG_NAME)
MAIN = Path("out/main.typ")
BODY = Path("out/body.typ")
PDF = Path("out/main.pdf")
HEADINGS = ("=", "==", "===")
KEYS = {"name", "file", "dir", "description"}


def read_items(cfg):
    """读一个 config.toml，校验后返回 [{name, file, dir, description}, ...]。"""
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
        for key in ("file", "description"):
            if it.get(key) and not (cfg.parent / it[key]).is_file():
                sys.exit(f"错误：{cfg} 的条目「{name}」引用了不存在的文件 {cfg.parent / it[key]}")
        items.append({"name": name, "file": it.get("file"),
                      "dir": it.get("dir"), "description": it.get("description")})
    return items


def marker(lang, path):
    """生成器只写标记块，由 out/main.typ 的 show 规则接住，避免生成文件依赖 import。"""
    return f"```{lang}\n{path}\n```\n\n"


def emit_typ(out, cfg, root, depth):
    """按 config 层级写出 Typst；depth 决定标题级别，路径写成仓库根相对（"/graph/lca.hpp"）。"""
    if depth >= len(HEADINGS):
        sys.exit(f"错误：{cfg} 层级过深，生成器只支持到 {HEADINGS[-1]}"
                 f"（第 {depth + 1} 层无法表示）")
    for it in read_items(cfg):
        label = HEADINGS[depth]
        src = it["dir"] or it["file"] or ""
        print(f"{'  ' * depth}{label}: {it['name']}" + (f" ({src})" if src else ""))
        out.write(f"{label} {it['name']}\n\n")
        if it["description"]:
            rel = (cfg.parent / it["description"]).resolve().relative_to(root)
            out.write(marker("typ-prose", f"/{rel}"))
        if it["dir"]:
            emit_typ(out, cfg.parent / it["dir"] / CFG_NAME, root, depth + 1)
        if it["file"]:
            src_file = (cfg.parent / it["file"]).resolve().relative_to(root)
            out.write(marker("cpp-ref", f"/{src_file}"))


def generate():
    with BODY.open("w", encoding="utf-8") as out:
        emit_typ(out, ROOT_CFG, Path.cwd().resolve(), 0)
    print(f">> 生成 {BODY}")


def build_pdf():
    if not MAIN.is_file():
        sys.exit(f"错误：找不到 {MAIN}。它是手写文件（不入库），不会被构建过程生成或删除。")
    if not shutil.which("typst"):
        sys.exit("错误：找不到 typst。安装方式：cargo install --locked typst-cli，"
                 "或从 github.com/typst/typst/releases 下预编译二进制放进 PATH。")
    # 先删旧产物：编译失败时不会留下让人误以为是新结果的 PDF
    PDF.unlink(missing_ok=True)
    cmd = ["typst", "compile", "--root", ".", str(MAIN), str(PDF)]
    print(">> 编译 " + " ".join(cmd))
    if subprocess.run(cmd).returncode != 0:
        sys.exit("错误：typst 编译失败（详见上面的报错）")
    print(f">> 完成 {PDF}")


def main():
    t0 = time.time()
    generate()
    build_pdf()
    print(f">> 用时 {time.time() - t0:.2f}s")


if __name__ == "__main__":
    main()
