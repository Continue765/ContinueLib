---
documentation_of: //data_structure/segment_tree/lazy_segment_tree.hpp
---

# LazySegmentTree

定义于头文件 `lazy_segment_tree.hpp`

```cpp
template <typename ActMono>
struct LazySegmentTree;
```

维护长度 $n$ 的序列 $a$，支持单点赋值、区间作用与区间聚合。建树 $O(n)$，其余操作 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `ActMono` | 作用与聚合类型 |

## 成员类型

| 成员类型 | 定义 |
| --- | --- |
| `X` | `typename ActMono::X` |
| `Y` | `typename ActMono::Y` |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `LazySegmentTree(int n)` | 构造 $n$ 个 `Mono::e()` 的序列，$O(n)$ |
| `LazySegmentTree(const vector<X>& init)` | 以 `init` 构造，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void modify(int p, const X& v)` | $a_p \leftarrow v$，$O(\log n)$ |
| `void apply(int l, int r, const Y& v)` | 对 $i \in [l, r)$ 作用 `v`，$O(\log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int l, int r)` | 返回 $[l, r)$ 的聚合值，$O(\log n)$ |
| `template <typename F> int findFirst(int l, int r, F&& pred)` | 返回 $[l, r)$ 内最小的 $i$ 使 `pred(a_i)` 为真，无则 $-1$，$O(\log n)$ |
| `template <typename F> int findLast(int l, int r, F&& pred)` | 返回 $[l, r)$ 内最大的 $i$ 使 `pred(a_i)` 为真，无则 $-1$，$O(\log n)$ |
| `template <typename F> int maxRight(int l, F&& pred, X& sum)` | 返回最大的 $r$ 使 `pred(a_l op … op a_{r-1})` 为真，$O(\log n)$ |
| `template <typename F> int minLeft(int r, F&& pred, X& sum)` | 返回最小的 $l$ 使 `pred(a_l op … op a_{r-1})` 为真，$O(\log n)$ |

## 注解

`pred` 须对聚合运算单调。

## 示例

```cpp
LazySegmentTree<SumAdd<i64>> seg(vector<i64>{3, 1, 4, 1, 5});
LazySegmentTree<SumAdd<i64>> fresh(5);

seg.modify(2, 0);
seg.apply(0, 3, 10);
i64 s = seg.query(1, 4);

i64 sum = 0;
int r = seg.maxRight(0, [](i64 v) { return v <= 30; }, sum);
sum = 0;
int l = seg.minLeft(5, [](i64 v) { return v <= 30; }, sum);

int i = seg.findFirst(0, 5, [](i64 v) { return v <= 0; });
int j = seg.findLast(0, 5, [](i64 v) { return v <= 0; });
```
