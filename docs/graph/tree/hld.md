---
documentation_of: //graph/tree/hld.hpp
---

# HLD

在头文件 `hld.hpp` 中定义

```cpp
template <typename T>
struct HLD;
```

维护 `tree` 的重链剖分，支持 LCA、距离、跳祖先、换根子树与路径分解，各查询 $O(\log n)$。构造后 `tree.seq` 为 HL 序，`tree.in[u]`、`tree.out[u]` 为以 $u$ 为根的子树的 HL 序区间。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 树 `tree` 的边权类型 |

## 成员变量

| 成员变量 | 说明 |
| --- | --- |
| `he[u]` | $u$ 的重儿子，无重儿子为 $-1$ |
| `top[u]` | $u$ 所在重链的链顶 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `HLD(Tree<T>& tree)` | 对 `tree` 做重链剖分并重写 `tree.in`、`tree.out`、`tree.seq`，$O(n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int lca(int u, int v)` | $u, v$ 的最近公共祖先 |
| `int dist(int u, int v)` | $u, v$ 间的边数 |
| `int jump(int u, int k)` | $u$ 的第 $k$ 级祖先，$k = 0$ 时为 $u$；$k > \text{dep}[u]$ 时返回 $-1$ |
| `int jump(int u, int v, int k)` | 路径 $u \to v$ 上距 $u$ 为 $k$ 条边的点；$k > \text{dist}(u, v)$ 时返回 $-1$ |
| `bool isAncester(int u, int v)` | $u$ 是否为 $v$ 的祖先 |
| `int rootedParent(int root, int v)` | 以 `root` 为根时 $v$ 的父节点，`v == root` 时返回 `v` |
| `int rootedSize(int root, int v)` | 以 `root` 为根时 $v$ 的子树大小 |
| `int rootedLca(int root, int u, int v)` | 以 `root` 为根时 $u, v$ 的最近公共祖先 |

**路径分解**

| 成员函数 | 说明 |
| --- | --- |
| `template <typename F> void forPath(int u, int v, bool edge, F&& f)` | 将路径 $u \to v$ 分解为若干 HL 序区间，按从 $u$ 到 $v$ 的顺序对每个区间调用 `f(l, r, rev)` |

## 注解

`forPath` 的回调区间为 $[l, r)$；`rev` 为 `true` 表示该段路径方向与 HL 序方向相反，即第 $i$ 个点对应下标 $r - 1 - i$；`edge` 为 `true` 时路径不含 $u, v$ 的最近公共祖先。

## 示例

```cpp
Undigraph<int> g(n);
Tree<int> tree(g);
HLD<int> hld(tree);

int p = hld.lca(0, 1);
int d = hld.dist(0, 1);
int a = hld.jump(1, 1);
int b = hld.jump(0, 1, 1);
bool sub = hld.isAncester(0, 1);
int sz = hld.rootedSize(1, 0);
int q = hld.rootedLca(2, 0, 1);

i64 len = 0;
hld.forPath(0, 1, false, [&](int l, int r, bool rev) { len += r - l; });
```
