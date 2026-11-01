---
documentation_of: //graph/components/block_cut_tree.hpp
---

# BlockCutTree

定义于头文件 `block_cut_tree.hpp`

```cpp
struct BlockCutTree;
```

构造无向图的圆方树，$O(n + m)$。

## 成员变量

| 成员变量 | 说明 |
| --- | --- |
| `int n` | 原图点数 |
| `int tot` | 圆方树点数，即圆点与方点之和 |
| `Undigraph<int> tree` | 圆方树，点 $0, \dots, n - 1$ 为原图的圆点，其余为方点 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `template <typename T> BlockCutTree(const Undigraph<T>& g)` | 构造 `g` 的圆方树，$O(n + m)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `bool isCut(int u) const` | 原图的点 `u` 是否为割点，$O(1)$ |

## 示例

```cpp
Undigraph<int> g(4);
g.add(0, 1);
g.add(1, 2);
g.add(2, 0);
g.add(2, 3);

BlockCutTree bct(g);
bool cut = bct.isCut(2);
int k = bct.tot;
for (auto [v, id] : bct.tree[2]) {
    int u = v;
}
```
