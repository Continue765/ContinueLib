---
documentation_of: //data_structure/cartesian_tree.hpp
---

# CartesianTree

定义于头文件 `cartesian_tree.hpp`

```cpp
template <typename T, bool IS_MIN = false>
struct CartesianTree;
```

以序列 $a$ 为键构造笛卡尔树，$O(n)$。`IS_MIN = false` 时为大根堆，否则为小根堆。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 键类型 |
| `IS_MIN` | 为 `true` 时根取区间最小值，否则取最大值 |

## 成员变量

| 成员变量 | 说明 |
| --- | --- |
| `n` | 序列长度 |
| `L[i]` | 结点 $i$ 的左儿子，无则 $-1$ |
| `R[i]` | 结点 $i$ 的右儿子，无则 $-1$ |
| `p[i]` | 结点 $i$ 的父结点，根为 $-1$ |
| `range[i]` | $[l, r)$，子树 $i$ 覆盖的下标区间 |
| `root` | 根结点编号 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `CartesianTree(vector<T>& a)` | 以 `a` 构造，$O(n)$ |

## 注解

键相等时下标小者作为祖先。

## 示例

```cpp
vector<int> a{3, 1, 4, 1, 5};
CartesianTree<int> mx(a);
CartesianTree<int, true> mn(a);
int r = mx.root;
auto [l, rr] = mx.range[2];
int par = mx.p[2];
```
