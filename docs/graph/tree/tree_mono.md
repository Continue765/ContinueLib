---
documentation_of: //graph/tree/tree_mono.hpp
---

# TreeMono

在头文件 `tree_mono.hpp` 中定义

```cpp
template <typename T, typename Mono, bool edge = false>
struct TreeMono;
```

在 `HLD` 上维护点权或边权，支持单点修改、路径 / 子树 / 全局聚合与路径上的前缀查找。构造 $O(n)$，单点修改与子树查询 $O(\log n)$，路径查询与 `maxPath` $O(\log^2 n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 边权类型 |
| `Mono` | 聚合运算类型，满足 Monoid 要求 |
| `edge` | 为 `true` 时维护边权，否则维护点权 |

## 成员类型

| 成员类型 | 定义 |
| --- | --- |
| `X` | `typename Mono::Type` |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `TreeMono(HLD<T>& hld)` | 全部取 `e()` |
| `TreeMono(HLD<T>& hld, const vector<X>& init)` | 以 `init` 初始化，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void modify(int i, const X& x)` | 第 `i` 个点（或边）置为 `x` |
| `void apply(int i, const X& x)` | 第 `i` 个点（或边）$a_i \leftarrow \text{op}(a_i, x)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X pathQuery(int u, int v)` | 路径 `u`–`v` 的聚合，按自 `u` 至 `v` 的顺序 |
| `X subtreeQuery(int u, int root = -1)` | 以 `root` 为根时子树 `u` 的聚合 |
| `X allQuery()` | 全部点（或边）的聚合，$O(1)$ |
| `int maxPath(F&& pred, int u, int v)` | 沿 $u \to v$ 取使 `pred` 恒成立的最长前缀，返回该前缀末端的顶点编号 |
| `int id(int i)` | 第 `i` 个点（或边）在欧拉序中的下标，$O(1)$ |

## 注解

`init` 的长度须为 $n$（`edge = false`）或 $n - 1$（`edge = true`）；`edge = true` 时 `init[i]`、`modify` 与 `apply` 的参数 `i` 指编号 `i` 的边。`pathQuery` 在 `edge = false` 时包含两端点，`edge = true` 时只含路径上的边。`subtreeQuery` 的 `root` 取 $-1$ 时使用 `tree.root`。

`maxPath` 的 `pred` 须对前缀单调：路径上自 $u$ 起的取值前缀满足 `pred` 后即不再满足。返回值为 `edge = false` 时该前缀最后一个顶点，`edge = true` 时最后一条边靠 `v` 一侧的端点（无满足的边时返回 `u`）；`edge = false` 且 `u` 不合 `pred` 时返回 $-1$，`edge = true` 且 `pred(e())` 为假时返回 $-1$。

## 示例

```cpp
Undigraph<int> g(n);
g.add(0, 1);
g.add(1, 2);

Tree<int> tree(g, 0);
HLD<int> hld(tree);

TreeMono<int, AddMono<i64>> on_vertex(hld, vector<i64>(n, 0));
on_vertex.modify(0, 3);
on_vertex.apply(1, 5);
i64 a = on_vertex.pathQuery(0, n - 1);
i64 b = on_vertex.subtreeQuery(0);
i64 c = on_vertex.allQuery();
int p = on_vertex.maxPath([](i64 s) { return s <= 10; }, 0, n - 1);

TreeMono<int, AddMono<i64>, true> on_edge(hld, vector<i64>(n - 1, 1));
on_edge.modify(0, 2);
i64 d = on_edge.pathQuery(0, n - 1);
int q = on_edge.maxPath([](i64 s) { return s <= 1; }, 1, n - 1);
```
