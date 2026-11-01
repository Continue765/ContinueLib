---
documentation_of: //graph/shortest_path/dijkstra.hpp
---

# dijkstra

定义于头文件 `dijkstra.hpp`

```cpp
template <typename T, bool dir>
pair<vector<T>, vector<int>> dijkstra(const Graph<T, dir>& g, int s);  // (1)

template <typename T, bool dir>
pair<vector<T>, vector<int>> dijkstraDense(const Graph<T, dir>& g, int s);  // (2)

template <typename T, bool dir>
tuple<vector<T>, vector<int>, vector<int>> dijkstra(const Graph<T, dir>& g, vector<int>& s);  // (3)
```

求单源最短路，要求边权非负。前两个重载返回 `{dist, pre}`，第三个重载返回 `{dist, pre, root}`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图，边权非负 |
| `s` | 源点；第三个重载为源点集合 |

## 返回值

返回 `{dist, pre}` 或 `{dist, pre, root}`：`dist[v]` 为到最近源点的距离，不可达为 `inf<T>`；`pre[v]` 为最短路树上 `v` 的前驱，`v` 为源点或不可达时为 `-1`；`root[v]` 为 `v` 所属的最近源点，不可达时为 `-1`。

## 复杂度

`dijkstra` 为 $O((n + m) \log m)$，`dijkstraDense` 为 $O(n^2 + m)$。

## 示例

```cpp
Digraph<int> g(n);
g.add(0, 1, 4);
g.add(1, 2, 3);

auto [dist, pre] = dijkstra(g, 0);
auto [dist2, pre2] = dijkstraDense(g, 0);

vector<int> s = {0, 2};
auto [dist3, pre3, root] = dijkstra(g, s);
```
