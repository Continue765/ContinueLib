---
documentation_of: //graph/components/scc.hpp
---

# SCC

定义于头文件 `scc.hpp`

```cpp
template <typename T>
pair<int, vector<int>> SCC(const Digraph<T>& g);
```

求有向图 `g` 的强连通分量，返回 `{cnt, comp}`。分量编号按拓扑序：对任意边 `u → v`，若 `comp[u] != comp[v]` 则 `comp[u] < comp[v]`。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向图 |

## 返回值

返回 `{cnt, comp}`：`cnt` 为强连通分量个数，`comp[u]` 为点 `u` 所属分量编号，$0 \le \text{comp}[u] < \text{cnt}$。

## 复杂度

$O(n + m)$，$n$ 为点数，$m$ 为边数。

## 示例

```cpp
Digraph<int> g(n);
g.add(0, 1);
g.add(1, 0);
auto [cnt, comp] = SCC(g);
```
