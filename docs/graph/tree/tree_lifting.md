---
documentation_of: //graph/tree/tree_lifting.hpp
---

# TreeLifting

定义于头文件 `tree_lifting.hpp`

```cpp
template <typename Mono, typename T>
struct TreeLifting;
```

在 `Tree` 上建倍增表，支持 LCA 与路径信息聚合。构造 $O(n \log n)$，单次操作 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `Mono` | 聚合运算类型，满足 Monoid 要求 |
| `T` | 边权类型 |

## 成员类型

| 成员类型 | 定义 |
| --- | --- |
| `X` | `typename Mono::Type` |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `TreeLifting(Tree<T>& tree)` | 以各点父边经 `Mono::from` 转换后建表，$O(n \log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int lca(int u, int v)` | 最近公共祖先，$O(\log n)$ |
| `pair<int, X> query(int u, int v)` | 返回 `{lca(u, v), 路径 u–v 上边权的聚合}`，$O(\log n)$ |

## 注解

`Mono` 沿自底向上方向聚合，`query` 中 $u \to \text{lca}$ 段在前、$v \to \text{lca}$ 段在后。

## 示例

```cpp
Undigraph<i64> g(n);
g.add(0, 1, 5);
g.add(1, 2, 7);

Tree<i64> tree(g, 0);
TreeLifting<AddMono<i64>, i64> lift(tree);
int l = lift.lca(1, 2);
auto [p, dist] = lift.query(0, 2);
```
