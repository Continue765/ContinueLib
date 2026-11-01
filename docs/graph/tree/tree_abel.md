---
documentation_of: //graph/tree/tree_abel.hpp
---

# TreeAbel

定义于头文件 `tree_abel.hpp`

```cpp
template <typename T, typename Abel, bool edge = false>
struct TreeAbel;
```

在 `HLD` 上维护点权或边权，支持根路径、路径与子树的聚合查询。构造 $O(n)$，单次查询 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 边权类型 |
| `Abel` | 聚合运算类型，满足 Abel 群要求 |
| `edge` | 为 `true` 时维护边权，否则维护点权 |

## 成员类型

| 成员类型 | 定义 |
| --- | --- |
| `X` | `typename Abel::Type` |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `TreeAbel(HLD<T>& hld)` | 全部取 `e()` |
| `TreeAbel(HLD<T>& hld, const vector<X>& init)` | 以 `init` 初始化，$O(n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X rootQuery(int u)` | 根到 `u` 路径的聚合，$O(\log n)$ |
| `X pathQuery(int u, int v)` | 路径 `u`–`v` 的聚合，$O(\log n)$ |
| `X subtreeQuery(int u, int root = -1)` | 以 `root` 为根时子树 `u` 的聚合，$O(\log n)$ |

## 注解

`edge = true` 时 `init[i]` 为第 `i` 条边的权值，`init` 长度为 $n - 1$；`pathQuery` 只含路径上的边。

## 示例

```cpp
Undigraph<int> g(n);
g.add(0, 1);
g.add(1, 2);

Tree<int> tree(g, 0);
HLD<int> hld(tree);

TreeAbel<int, AddMono<i64>> on_vertex(hld, vector<i64>(n, 0));
i64 a = on_vertex.rootQuery(n - 1);
i64 b = on_vertex.pathQuery(0, n - 1);
i64 c = on_vertex.subtreeQuery(0);

TreeAbel<int, AddMono<i64>, true> on_edge(hld, vector<i64>(n - 1, 1));
i64 d = on_edge.pathQuery(0, n - 1);
i64 e = on_edge.subtreeQuery(0, 2);
```
