---
documentation_of: //data_structure/segment_tree/segment_tree.hpp
---

# SegmentTree

在头文件 `segment_tree.hpp` 中定义

```cpp
template <typename Mono>
struct SegmentTree;
```

维护长度 $n$ 的序列 $a$，支持单点赋值和区间聚合。建树 $O(n)$，其余操作 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `Mono` | 聚合运算类型，需提供 `using Type = X`、`static X e()`、`static X op(const X&, const X&)`；`op` 可结合，`e()` 为单位元 |

## 成员类型

| 类型 | 定义 |
| --- | --- |
| `X` | `typename Mono::Type` |

## 成员函数

**构造**

| 函数 | 说明 |
| --- | --- |
| `SegmentTree(int n)` | 构造 $n$ 个 `e()` 的序列，$O(n)$ |
| `SegmentTree(const std::vector<X>& init)` | 以 `init` 构造，$O(n)$ |

**修改**

| 函数 | 说明 |
| --- | --- |
| `void modify(int p, const X& v)` | $a_p \leftarrow v$，$O(\log n)$ |

**查询**

| 函数 | 说明 |
| --- | --- |
| `X query(int l, int r)` | 返回 `op(a_l, …, a_{r-1})`，$O(\log n)$ |
| `template <typename F> int findFirst(int l, int r, F&& pred)` | 返回 $[l, r)$ 内最小的 $i$ 使 `pred(a_i)` 为真，无则 $-1$，$O(\log n)$ |
| `template <typename F> int findLast(int l, int r, F&& pred)` | 返回最大的 $i$ 使 `pred(a_i)` 为真，无则 $-1$，$O(\log n)$ |
| `template <typename F> int maxRight(int l, F&& pred, X& sum)` | 返回最大的 $r$ 使 `pred(op(a_l, …, a_{r-1}))` 为真，$O(\log n)$ |
| `template <typename F> int minLeft(int r, F&& pred, X& sum)` | 返回最小的 $l$ 使 `pred(op(a_l, …, a_{r-1}))` 为真，$O(\log n)$ |

## 注解

`pred` 须对 `op` 单调。`maxRight` / `minLeft` 的 `sum` 初值为 `e()`，返回时写回区间聚合值。

## 示例

```cpp
SegmentTree<AddMono<int>> seg({1, 2, 3, 4});
int s = 0;
int r = seg.maxRight(0, [](int v) { return v <= 12; }, s);  // r = 2, s = 11
```
