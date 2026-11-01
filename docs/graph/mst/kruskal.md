---
documentation_of: //graph/mst/kruskal.hpp
---

# kruskal

定义于头文件 `kruskal.hpp`

```cpp
template <typename T>
pair<vector<int>, T> kruskal(const Undigraph<T>& g);
```

求无向图 `g` 的最小生成森林，返回 `{res, cost}`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 无向图 |

## 返回值

返回 `{res, cost}`：`res` 为选中的边编号，按权值非降序；`cost` 为选中边的权值之和。

## 复杂度

$O(m \log m)$，$m$ 为边数。

## 示例

```cpp
Undigraph<i64> g(4);
g.add(0, 1, 3);
g.add(1, 2, 1);
g.add(2, 3, 2);

auto [ids, cost] = kruskal(g);
```
