---
documentation_of: //graph/shortest_path/floyd.hpp
---

# floyd

定义于头文件 `floyd.hpp`

```cpp
template <typename T>
void floyd(vector<vector<T>>& dist);  // (1)

template <typename T, bool dir>
vector<vector<T>> floyd(const Graph<T, dir>& g);  // (2)
```

求全源最短路。`floyd(dist)` 就地更新邻接矩阵，`floyd(g)` 返回最短路矩阵。

## 参数

| 参数 | 说明 |
| --- | --- |
| `dist` | $n \times n$ 邻接矩阵，无边与不可达为 `inf<T>`，`dist[i][i]` 为 $0$ |
| `g` | 有向或无向图 |

## 返回值

`floyd(dist)` 无返回值；`floyd(g)` 返回 $n \times n$ 矩阵，`dist[u][v]` 为 `u` 到 `v` 的最短距离，不可达为 `inf<T>`。

## 复杂度

$O(n^3)$。

## 示例

```cpp
vector dist(n, vector<int>(n, inf<int>));
for (int u = 0; u < n; u++) {
    dist[u][u] = 0;
}
dist[0][1] = 3;
floyd(dist);

Digraph<int> g(n);
g.add(0, 1, 3);
auto all = floyd(g);
```
