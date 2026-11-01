---
documentation_of: //graph/shortest_path/dijkstra.hpp
---

# dijkstra

在头文件 `dijkstra.hpp` 中定义

```cpp
template <typename T, bool dir>
pair<vector<T>, vector<int>> dijkstra(const Graph<T, dir>& g, int s);
```

求 `g` 中以 `s` 为源点的单源最短路，要求边权非负，返回 `{dist, pre}`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图，边权非负 |
| `s` | 源点 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `dist[v]` | `s` 到 `v` 的最短距离，不可达为 `inf<T>` |
| `pre[v]` | 最短路树上 `v` 的前驱，`v = s` 或 `v` 不可达时为 `-1` |

## 复杂度

$O((n + m) \log m)$，$n$ 为点数，$m$ 为边数。

## 示例

```cpp
Graph<int> g(n);
g.add(0, 1, 4);
g.add(1, 2, 3);
auto [dist, pre] = dijkstra(g, 0);
```

## dijkstraDense

```cpp
template <typename T, bool dir>
pair<vector<T>, vector<int>> dijkstraDense(const Graph<T, dir>& g, int s);
```

求 `g` 中以 `s` 为源点的单源最短路，要求边权非负，返回 `{dist, pre}`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图，边权非负 |
| `s` | 源点 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `dist[v]` | `s` 到 `v` 的最短距离，不可达为 `inf<T>` |
| `pre[v]` | 最短路树上 `v` 的前驱，`v = s` 或 `v` 不可达时为 `-1` |

$O(n^2 + m)$，$n$ 为点数，$m$ 为边数。

## 示例

```cpp
Graph<int> g(n);
g.add(0, 1, 4);
auto [dist, pre] = dijkstraDense(g, 0);
```

## 多源最短路

```cpp
template <typename T, bool dir>
tuple<vector<T>, vector<int>, vector<int>> dijkstra(const Graph<T, dir>& g, vector<int>& s);
```

求各源点到全图的最短距离，要求边权非负，返回 `{dist, pre, root}`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图，边权非负 |
| `s` | 源点集合 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `dist[v]` | `v` 到最近源点的距离，不可达为 `inf<T>` |
| `pre[v]` | 最短路树上 `v` 的前驱，`v` 为源点或不可达时为 `-1` |
| `root[v]` | `v` 所属的最近源点，`v` 不可达时为 `-1` |

## 复杂度

$O((n + m) \log m)$。

## 注解

`s` 以非 const 引用传入，函数不修改其内容。

## 示例

```cpp
Graph<int> g(n);
g.add(0, 1, 4);
g.add(1, 2, 3);
vector<int> s = {0, 2};
auto [dist, pre, root] = dijkstra(g, s);
```
