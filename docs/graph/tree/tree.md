---
documentation_of: //graph/tree/tree.hpp
---

# Tree

定义于头文件 `tree.hpp`

```cpp
template <typename T>
struct Tree;
```

以 `rt` 为根预处理无向树 `g`，$O(n)$；给出父子关系、深度、子树大小与欧拉序，子树 $u$ 对应连续下标区间 $[\text{in}_u, \text{out}_u)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 边权类型 |

## 成员变量

| 成员变量 | 说明 |
| --- | --- |
| `g` | 树的邻接表，以引用保存 |
| `n` | 点数 |
| `root` | 根 |
| `fa[u]` | 父结点，根为 $-1$ |
| `pe[u]` | $u$ 到父结点的边编号，根为 $-1$ |
| `dep[u]` | 深度，根为 $0$ |
| `siz[u]` | 子树点数 |
| `in[u]`, `out[u]` | 子树 $u$ 的欧拉序区间 $[\text{in}_u, \text{out}_u)$ |
| `seq[i]` | 欧拉序第 $i$ 个点 |
| `dist[u]` | 根到 $u$ 的路径长度 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `Tree(Undigraph<T>& g, int rt = 0)` | 以 `rt` 为根预处理，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void build(int rt = 0)` | 以 `rt` 为根重新预处理，$O(n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int eToV(int i)` | 边 `i` 的两端点中较深者，$O(1)$ |
| `int vToE(int u)` | $u$ 到父结点的边编号，根返回 $-1$，$O(1)$ |
| `vector<int> subtree(int u)` | 子树 $u$ 的点，按欧拉序排列，$O(\text{siz}_u)$ |

## 注解

`g` 须为 $n$ 个点、$n - 1$ 条边的无向树。

## 示例

```cpp
Undigraph<int> g(n);
g.add(0, 1);
g.add(1, 2);

Tree<int> tree(g, 0);
int v = tree.eToV(0);
int e = tree.vToE(1);
vector<int> s = tree.subtree(0);
i64 d = tree.dist[2];

tree.build(2);
int dep = tree.dep[0];
```
