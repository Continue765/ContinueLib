# ContinueLib

XCPC C++ 模板库

## 编译环境

模板按 C++20 编写，并使用了 GNU 扩展（例如 `__int128` 和 `bits/stdc++.h`）。请使用支持这些扩展的编译器，并以 GNU C++20 模式编译，例如 GCC，或使用 libstdc++ 的 Clang。

## build.py

`build.py` 用来生成模板文档。需要 Python 3.11+ 和 Typst，在仓库根目录运行：

```bash
./build.py
```

生成的文件是 `out/portrait.pdf`（竖版）和 `out/landscape.pdf`（横向双栏）。添加模板时，把文件放到对应目录，再在同目录的 `config.toml` 里登记即可。

## expander.py

提交 Online Judge 前，可以把引用的模板展开成一个文件：

```bash
./expander.py solution.cpp > solution.submit.cpp
```

脚本会递归展开仓库里的头文件、去掉重复的 `#pragma once`，并尝试删除没有用到的顶层函数和简单类。

## TODO

- 重写 Kruskal 重构树
- k 短路
- 次小 / 严格次小生成树
- Hierholzer
