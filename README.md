# Continue's Library for Competitive Programming

## 构建

```
./build.py
```

在仓库根目录跑。产物是 `out/main.pdf`。需要 Python 3.11+ 和 XeLaTeX。

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

`file` 和 `dir` 二选一，都写或都不写会直接报错。根目录的 `config.toml` 就是这么列出 8 个一级章节的。

## 加说明文字

想在某节代码前面插一段说明，用 `tex`（相对同一个目录）：

```toml
[[item]]
name = "莫比乌斯反演"
file = "mobius.hpp"
tex = "莫比乌斯反演.tex"
```

## 改排版

改 `out/main.tex`，手写的，不会被覆盖。`out/body.tex` 是每次构建生成的，不要改。

## VS Code Snippets

```
python3 generate_snippets.py
```

快捷键就是文件名小写：`dijkstra.hpp` → 敲 `dijkstra`。