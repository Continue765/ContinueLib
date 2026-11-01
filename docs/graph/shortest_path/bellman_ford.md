---
documentation_of: //graph/shortest_path/bellman_ford.hpp
---

# bellmanFord

定义于头文件 `bellman_ford.hpp`

```cpp
template <typename T, bool dir>
pair<vector<T>, vector<int>> bellmanFord(const Graph<T, dir>& g, int s);
```

求 `g` 中以 `s` 为源点的单源最短路，允许负权边，返回 `{dist, pre}`；存在从 `s` 可达的负环时返回 `{ {}, {} }`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图 |
| `s` | 源点 |

## 返回值

返回 `{dist, pre}`：`dist[v]` 为 `s` 到 `v` 的最短距离，不可达为 `inf<T>`；`pre[v]` 为最短路树上 `v` 的前驱，`v = s` 或不可达时为 `-1`。

## 复杂度

$O(nm)$，$n$ 为点数，$m$ 为边数。

## 示例

```cpp
Graph<int> g(n);
g.add(0, 1, 5);
g.add(1, 2, -3);
auto [dist, pre] = bellmanFord(g, 0);
```
