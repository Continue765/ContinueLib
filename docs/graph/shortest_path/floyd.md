---
documentation_of: //graph/shortest_path/floyd.hpp
---

# floyd

在头文件 `floyd.hpp` 中定义

```cpp
template <typename T>
void floyd(vector<vector<T>>& dist);

template <typename T, bool dir>
vector<vector<T>> floyd(const Graph<T, dir>& g);
```

求全源最短路。第一个重载就地把邻接矩阵 `dist` 更新为最短路矩阵，第二个重载由 `g` 构造最短路矩阵并返回。

## 参数

| 参数 | 说明 |
| --- | --- |
| `dist` | $n \times n$ 邻接矩阵，无边与不可达为 `inf<T>`，`dist[i][i]` 为 $0$ |
| `g` | 有向或无向图 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `dist[u][v]` | $u$ 到 $v$ 的最短距离，不可达为 `inf<T>` |

`floyd(dist)` 无返回值；`floyd(g)` 返回 $n \times n$ 的矩阵，`dist[u][u] = 0`，重边取权值最小者。

## 复杂度

$O(n^3)$，$n$ 为点数。

## 示例

```cpp
vector dist(n, vector<int>(n, inf<int>));
for (int u = 0; u < n; u++) {
    dist[u][u] = 0;
}
dist[0][1] = 3;
floyd(dist);

Graph<int> g(n);
g.add(0, 1, 3);
auto all = floyd(g);
```
