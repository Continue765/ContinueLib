---
documentation_of: //graph/tree/centroid.hpp
---

# centroidDecompsition

在头文件 `centroid.hpp` 中定义

```cpp
template <typename T, typename F>
void centroidDecompsition(const Tree<T>& tree, F&& f);
```

对 `tree` 做点分治，每确定一个重心就以该重心的分治块为参数调用一次 `f(fa, vt, pos)`，总计 $O(n \log n)$。

## 参数

| 参数 | 说明 |
| --- | --- |
| `tree` | 树 |
| `f` | 回调，对每个重心调用 `f(fa, vt, pos)`，三个参数均为 `vector<int>` |

## 回调参数

| 参数 | 说明 |
| --- | --- |
| `vt` | 当前分治块内的点，局部编号从 $0$ 开始，编号 $0$ 为重心 |
| `fa` | `fa[i]` 为 `vt[i]` 的父节点局部编号，`fa[0] = -1` |
| `pos` | 以重心为根的各分支在 `vt` 中的边界：`pos[0] = 0`，`pos[1] = 1`，第 $j$ 个分支（从 $0$ 起）占区间 $[\text{pos}[j+1], \text{pos}[j+2])$ |

## 示例

```cpp
Undigraph<int> g(n);
g.add(0, 1);
g.add(1, 2);

Tree<int> tree(g);
vector<int> cen;
centroidDecompsition(tree, [&](vector<int>& fa, vector<int>& vt, vector<int>& pos) {
    cen.push_back(vt[0]);
});
```
