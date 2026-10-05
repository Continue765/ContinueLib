# ContinueLib

## 构建

```
./build.py
```

在仓库根目录运行，需要 Python 3.11+ 和 Typst。每次生成一份共享章节内容，依次编译两份 PDF：

- `out/portrait.pdf`：A4 竖版。
- `out/landscape.pdf`：A4 横向双栏。

## 添加模板

1. 把 `.hpp` 丢到对应的一级目录，比如 `graph/lca.hpp`；
2. 在**同一个目录**的 `config.toml` 里加一条：

```toml
[[item]]
name = "LCA"
file = "lca.hpp"
```

3. `./build.py`。

`name` 是 PDF 里的标题，`file` 是同目录的代码文件。书写顺序就是 PDF 里的顺序。

## 子目录

那一节写成：

```toml
[[item]]
name = "最短路"
dir = "shortest_path"
```

再在 `graph/shortest_path/` 里放一个 `config.toml` 写它下面的条目。

`file` 和 `dir` 二选一。

## 加说明文字

想在某节代码前面插一段说明，用 `description`（相对同一个目录，内容用 Typst 写）：

```toml
[[item]]
name = "莫比乌斯反演"
file = "mobius.hpp"
description = "mobius.typ"
```

说明文件是普通 Typst 片段，公式、`*强调*`、`` `行内代码` `` 都能直接用。

## 改排版

竖版改 `out/main.typ` 和 `out/portrait.tmTheme`，横版改 `out/landscape.typ` 和
`out/landscape.tmTheme`。两个入口独立设置字体、代码样式、页眉、封面和目录，读取同一份
`out/body.typ`；横版的目录与正文为双栏，长代码行自动换行，续行不重复行号。
这四个文件都是入库的手写文件，不会被构建覆盖。

字体：正文 TeX Gyre Termes + FandolSong，代码 Consolas，页眉中文楷体 KaiTi。

## VS Code Snippets

```
python3 generate_snippets.py
```

快捷键就是文件名小写：如 `dijkstra.hpp` -> 敲 `dijkstra`。

## TODO
- 重写kruskal重构树
- k短路
- MST敏感性
- 次小/严格次小生成树
- Hierholzer
