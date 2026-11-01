---
documentation_of: //graph/tree/lca.hpp
---

# LCA

定义于头文件 `lca.hpp`

```cpp
template <typename T>
struct LCA;
```

倍增求最近公共祖先，构造 $O(n \log n)$，单次查询 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 树 `tree` 的边权类型 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `LCA(Tree<T>& tree)` | 预处理倍增表，$O(n \log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int get(int u, int v)` | $u, v$ 的最近公共祖先 |
| `int dist(int u, int v)` | $u, v$ 间的边数 |

## 示例

```cpp
Undigraph<int> g(n);
Tree<int> tree(g);

LCA<int> lca(tree);
int p = lca.get(0, 1);
int d = lca.dist(0, 1);
```

# FastLCA

定义于头文件 `lca.hpp`

```cpp
template <typename T>
struct FastLCA;
```

基于 dfn 序与稀疏表求最近公共祖先，构造 $O(n \log n)$，单次查询 $O(1)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 树 `tree` 的边权类型 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `FastLCA(Tree<T>& tree)` | 建立稀疏表，$O(n \log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int query(int u, int v)` | $u, v$ 的最近公共祖先，$O(1)$ |
| `int dist(int u, int v)` | $u, v$ 间的边数，$O(1)$ |

## 示例

```cpp
Undigraph<int> g(n);
Tree<int> tree(g);

FastLCA<int> lca(tree);
int p = lca.query(0, 1);
int d = lca.dist(0, 1);
```
