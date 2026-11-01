---
documentation_of: //graph/mst/prim.hpp
---

# prim

在头文件 `prim.hpp` 中定义

```cpp
template <typename T, typename F>
vector<Edge<T>> prim(int n, F&& cost);

template <typename T>
pair<vector<int>, T> prim(Undigraph<T>& g);
```

求最小生成树，$O(n^2)$。

## 参数

**`prim(n, cost)`**

| 参数 | 说明 |
| --- | --- |
| `n` | 点数 |
| `cost` | `T cost(int u, int v)`，返回点 `u` 与 `v` 之间边的权值 |

**`prim(g)`**

| 参数 | 说明 |
| --- | --- |
| `g` | 无向图 |

## 返回值

**`prim(n, cost)`**

| 值 | 说明 |
| --- | --- |
| `vector<Edge<T>>` | 生成树的 $n - 1$ 条边，`Edge<T>` 的 `u`、`v` 为端点，`w` 为权值 |

**`prim(g)`**

| 值 | 说明 |
| --- | --- |
| `first` | 选中的边编号 |
| `second` | 选中边的权值之和 |

## 示例

```cpp
Undigraph<i64> g(3);
g.add(0, 1, 2);
g.add(1, 2, 5);

auto [ids, cost] = prim(g);

auto edges = prim<i64>(3, [](int u, int v) { return abs(u - v); });
```
