---
documentation_of: //graph/shortest_path/spfa.hpp
---

# spfa

在头文件 `spfa.hpp` 中定义

```cpp
template <typename T, bool dir>
pair<vector<T>, vector<int>> spfa(const Graph<T, dir>& g, int s);
```

求 `g` 中以 `s` 为源点的单源最短路，允许负权边，返回 `{dist, pre}`；存在从 `s` 可达的负环时返回 `{ {}, {} }`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图 |
| `s` | 源点 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `dist[v]` | `s` 到 `v` 的最短距离，不可达为 `inf<T>` |
| `pre[v]` | 最短路树上 `v` 的前驱，`v = s` 或 `v` 不可达时为 `-1` |

## 复杂度

最坏 $O(nm)$，$n$ 为点数，$m$ 为边数。

## 示例

```cpp
Graph<int> g(n);
g.add(0, 1, 5);
g.add(1, 2, -3);
auto [dist, pre] = spfa(g, 0);
```
