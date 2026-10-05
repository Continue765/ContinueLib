# Continue's Library for Competitive Programming

## 构建

```
./build.py
```

产物是 `out/main.pdf`。需要 Python 3.11+ 和 typst。

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

## 子目录（三级标题）

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

改 `out/main.typ`（骨架：字体、代码样式、页眉、封面、目录）和 `out/theme.tmTheme`
（代码高亮的配色），都是手写的，不会被覆盖。

字体：正文 TeX Gyre Termes + FandolSong，代码 Consolas，页眉中文楷体 KaiTi。

## VS Code Snippets

```
python3 generate_snippets.py
```

快捷键就是文件名小写：如 `dijkstra.hpp` -> 敲 `dijkstra`。

## TODO
- 添加对横板双栏pdf的支持
- 重写kruskal重构树
- k短路
- MST敏感性
- 次小/严格次小生成树
- Hierholzer