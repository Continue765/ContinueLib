---
documentation_of: //graph/shortest_path/bfs_01.hpp
---

# bfs_01

定义于头文件 `bfs_01.hpp`

```cpp
template <typename T, bool dir>
pair<vector<T>, vector<int>> bfs_01(const Graph<T, dir>& g, int s);  // (1)

template <typename T, bool dir>
tuple<vector<T>, vector<int>, vector<int>> bfs_01(const Graph<T, dir>& g, vector<int>& s);  // (2)
```

求边权为 $0$ 或 $1$ 时的最短路。第一个重载返回 `{dist, pre}`，第二个重载返回 `{dist, pre, root}`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图，边权为 $0$ 或 $1$ |
| `s` | 源点；第二个重载为源点集合 |

## 返回值

返回 `{dist, pre}` 或 `{dist, pre, root}`：`dist[v]` 为到最近源点的距离，不可达为 `inf<T>`；`pre[v]` 为最短路树上 `v` 的前驱，`v` 为源点或不可达时为 `-1`；`root[v]` 为 `v` 所属的最近源点，不可达时为 `-1`。

## 复杂度

$O(n + m)$。

## 示例

```cpp
Digraph<int> g(n);
g.add(0, 1, 0);
g.add(1, 2, 1);

auto [dist, pre] = bfs_01(g, 0);

vector<int> s = {0, 2};
auto [dist2, pre2, root] = bfs_01(g, s);
```
