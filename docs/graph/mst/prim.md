---
documentation_of: //graph/mst/prim.hpp
---

# prim

定义于头文件 `prim.hpp`

```cpp
template <typename T, typename F>
vector<Edge<T>> prim(int n, F&& cost);  // (1)

template <typename T>
pair<vector<int>, T> prim(Undigraph<T>& g);  // (2)
```

求最小生成树。`prim(n, cost)` 返回生成树的 $n - 1$ 条边，`prim(g)` 返回 `{res, cost}`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `n` | 点数 |
| `cost` | `T cost(int u, int v)`，点 `u`、`v` 之间边的权值 |
| `g` | 无向图 |

## 返回值

`prim(n, cost)` 返回生成树的 $n - 1$ 条边；`prim(g)` 返回 `{res, cost}`：`res` 为选中的边编号，`cost` 为选中边的权值之和。

## 复杂度

$O(n^2)$。

## 示例

```cpp
Undigraph<i64> g(3);
g.add(0, 1, 2);
g.add(1, 2, 5);

auto [ids, cost] = prim(g);

auto edges = prim<i64>(3, [](int u, int v) { return abs(u - v); });
```
