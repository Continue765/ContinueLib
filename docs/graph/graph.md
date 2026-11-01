---
documentation_of: //graph/graph.hpp
---

# Graph

定义于头文件 `graph.hpp`

```cpp
template <typename T = int, bool dir = true>
struct Graph;
```

邻接表存储的有向或无向图，每条边单独保存 `u`、`v`、`w`。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 边权类型 |
| `dir` | `true` 为有向图，`false` 为无向图 |

## 成员类型

| 成员类型 | 定义 |
| --- | --- |
| `Edge<T>` | 边，含 `u`、`v`、`w` 三个成员 |
| `Digraph<T>` | `Graph<T, true>` |
| `Undigraph<T>` | `Graph<T, false>` |

## 数据成员

| 成员 | 说明 |
| --- | --- |
| `int n` | 点数 |
| `vector<Edge<T>> edges` | 全部边，下标即边编号 |
| `vector<vector<pair<int, int>>> adj` | `adj[u]` 含 `(v, id)`，无向图两个端点各含一次 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `Graph(int n)` | 构造 $n$ 个点、无边，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `int add(int u, int v, T w = 1)` | 加入边 $u \to v$（无向图加入 $u$–$v$），返回边编号，$O(1)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `const vector<pair<int, int>>& operator[](int u)` | `adj[u]` 的只读引用 |

## 自由函数

| 函数 | 说明 |
| --- | --- |
| `Digraph<T> reverse(const Digraph<T>& g)` | 所有边反向，$O(n + m)$ |
| `vector<int> degree(const Undigraph<T>& g)` | 各点度数，$O(n + m)$ |
| `pair<vector<int>, vector<int>> degree(const Digraph<T>& g)` | 各点 `{入度, 出度}`，$O(n + m)$ |
| `Graph<T, dir> induced(const Graph<T, dir>& g, const vector<int>& a)` | 点集 `a` 的诱导子图，点按 `a` 的顺序重编号为 $0, \dots, |a|-1$，$O(n + m)$ |
| `Undigraph<T> toUndigraph(const Digraph<T>& g)` | 边改为无向，$O(n + m)$ |

## 示例

```cpp
Graph<int> g(n);
int id = g.add(0, 1, 2);
auto [v, eid] = g[0][0];
auto rg = reverse(g);
auto outDeg = degree(g).second;
auto sub = induced(g, {0, 1, 2});
auto ug = toUndigraph(g);
```
