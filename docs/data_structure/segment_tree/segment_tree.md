---
documentation_of: //data_structure/segment_tree/segment_tree.hpp
---

# SegmentTree

定义于头文件 `segment_tree.hpp`

```cpp
template <typename Mono>
struct SegmentTree;
```

维护长度 $n$ 的序列 $a$，支持单点赋值与区间聚合。建树 $O(n)$，其余操作 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `Mono` | 聚合运算类型，满足 Monoid 要求 |

## 成员类型

| 成员类型 | 定义 |
| --- | --- |
| `X` | `typename Mono::Type` |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `SegmentTree(int n)` | 构造 $n$ 个 `e()` 的序列，$O(n)$ |
| `SegmentTree(const vector<X>& init)` | 以 `init` 构造，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void modify(int p, const X& v)` | $a_p \leftarrow v$，$O(\log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int l, int r)` | 返回 `op(a_l, …, a_{r-1})`，$O(\log n)$ |
| `template <typename F> int findFirst(int l, int r, F&& pred)` | 返回 $[l, r)$ 内最小的 $i$ 使 `pred(a_i)` 为真，无则 $-1$，$O(\log n)$ |
| `template <typename F> int findLast(int l, int r, F&& pred)` | 返回最大的 $i$ 使 `pred(a_i)` 为真，无则 $-1$，$O(\log n)$ |
| `template <typename F> int maxRight(int l, F&& pred, X& sum)` | 返回最大的 $r$ 使 `pred(op(a_l, …, a_{r-1}))` 为真，$O(\log n)$ |
| `template <typename F> int minLeft(int r, F&& pred, X& sum)` | 返回最小的 $l$ 使 `pred(op(a_l, …, a_{r-1}))` 为真，$O(\log n)$ |

## 注解

`pred` 须对 `op` 单调。

## 示例

```cpp
SegmentTree<AddMono<i64>> seg(vector<i64>{3, 1, 4, 1, 5});
SegmentTree<AddMono<i64>> fresh(5);

seg.modify(2, 0);
i64 s = seg.query(1, 4);

i64 sum = 0;
int r = seg.maxRight(0, [](i64 v) { return v <= 4; }, sum);
sum = 0;
int l = seg.minLeft(5, [](i64 v) { return v <= 6; }, sum);

SegmentTree<MinMono<i64>> mn({3, 1, 4, 1, 5});
int i = mn.findFirst(0, 5, [](i64 v) { return v <= 1; });
int j = mn.findLast(0, 5, [](i64 v) { return v <= 1; });
```
