---
documentation_of: //graph/mst/kruskal_tree.hpp
---

# kruskalTree

在头文件 `kruskal_tree.hpp` 中定义

```cpp
template <typename T>
pair<Undigraph<int>, vector<T>> kruskalTree(const Undigraph<T>& g);
```

构造无向图 `g` 的 Kruskal 重构树，返回 `{res, val}`。`res` 共 $n + c$ 个点，其中 $c$ 为最小生成森林的边数。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 无向图 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `res` | Kruskal 重构树，点 $0, \dots, n - 1$ 为原图点，点 $n + i$ 为第 $i$ 条选中的边对应的新点 |
| `val[p]` | 点 `p` 的权值，原图点为 $0$，新点为其对应边的权值 |

## 复杂度

$O(m \log m)$，$m$ 为边数。

## 示例

```cpp
Undigraph<i64> g(3);
g.add(0, 1, 4);
g.add(1, 2, 7);

auto [tree, val] = kruskalTree(g);
int root = tree.n - 1;
i64 w = val[root];
```
