---
documentation_of: //graph/tree/virtual_tree.hpp
---

# VirtualTree

定义于头文件 `virtual_tree.hpp`

```cpp
template <typename T>
struct VirtualTree;
```

由给定点集构造虚树：`vt` 为虚树结点按 `in` 排列的原树编号，`adj` 为以 `vt` 下标编号的邻接表，边权取两端点的深度差。$O(|h| \log |h| + |h| \log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 边权类型 |

## 成员变量

| 成员变量 | 说明 |
| --- | --- |
| `tree` | 建虚树所依据的 `TreeLifting`，以引用保存 |
| `vt` | 虚树结点，原树编号，按 `in` 升序 |
| `adj` | 虚树邻接表，`adj[u]` 的元素为 `(v, w)` |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `VirtualTree(TreeLifting<AddMono<i64>, T>& tree)` | 以 `tree` 为原树 |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `pair<vector<int>&, vector<vector<pair<int, T>>>&> build(vector<int>& h)` | 构造点集 `h` 的虚树，返回 `{vt, adj}` |

## 示例

```cpp
Undigraph<i64> g(n);
g.add(0, 1, 1);
g.add(1, 2, 1);

Tree<i64> tree(g, 0);
TreeLifting<AddMono<i64>, i64> lift(tree);
VirtualTree<i64> vt(lift);

vector<int> h{1, 2};
auto [nodes, adj] = vt.build(h);
int sz = nodes.size();
auto [to, w] = adj[0][0];
```
