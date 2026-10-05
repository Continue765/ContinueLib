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
BODY = Path("out/body.typ")
BUILD_TARGETS = (
    (Path("out/portrait.typ"), Path("out/portrait.pdf")),
    (Path("out/landscape.typ"), Path("out/landscape.pdf")),
)
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
    """生成器只写标记块，由各 Typst 入口的 show 规则接住。"""
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


def check_dependencies():
    missing = [str(entry) for entry, _ in BUILD_TARGETS if not entry.is_file()]
    if missing:
        sys.exit(f"错误：找不到手写 Typst 入口：{', '.join(missing)}")
    if not shutil.which("typst"):
        sys.exit("错误：找不到 typst。安装方式：cargo install --locked typst-cli，"
                 "或从 github.com/typst/typst/releases 下预编译二进制放进 PATH。")


def build_pdfs():
    # 清除两个旧产物，避免任一编译失败时误用旧 PDF。
    for _, pdf in BUILD_TARGETS:
        pdf.unlink(missing_ok=True)

    succeeded = []
    failed = []
    for entry, pdf in BUILD_TARGETS:
        cmd = ["typst", "compile", "--root", ".", str(entry), str(pdf)]
        print(">> 编译 " + " ".join(cmd))
        if subprocess.run(cmd).returncode == 0:
            succeeded.append(pdf)
            print(f">> 完成 {pdf}")
        else:
            pdf.unlink(missing_ok=True)
            failed.append((entry, pdf))

    print(">> 成功：" + (", ".join(map(str, succeeded)) if succeeded else "无"))
    if failed:
        print(">> 失败：" + ", ".join(f"{entry} -> {pdf}" for entry, pdf in failed))
        sys.exit("错误：一个或多个 Typst 目标编译失败")


def main():
    t0 = time.time()
    check_dependencies()
    generate()
    build_pdfs()
    print(f">> 用时 {time.time() - t0:.2f}s")


if __name__ == "__main__":
    main()
