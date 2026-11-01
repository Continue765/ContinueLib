---
documentation_of: //graph/components/ebcc.hpp
---

# EBCC

在头文件 `ebcc.hpp` 中定义

```cpp
template <typename T>
pair<int, vector<int>> EBCC(const Undigraph<T>& g);
```

求无向图 `g` 的边双连通分量，返回 `{cnt, comp}`。同一分量内任意两点之间存在两条边不相交的路径。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 无向图 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `cnt` | 边双连通分量个数 |
| `comp[u]` | 点 `u` 所属分量编号，$0 \le \text{comp}[u] < \text{cnt}$ |

## 复杂度

$O(n + m)$，$n$ 为点数，$m$ 为边数。

## 示例

```cpp
Undigraph<int> g(3);
g.add(0, 1);
g.add(1, 2);

auto [cnt, comp] = EBCC(g);
for (int u = 0; u < g.n; u++) {
    int id = comp[u];
}
```
