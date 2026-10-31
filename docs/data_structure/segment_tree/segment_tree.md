---
documentation_of: //data_structure/segment_tree/segment_tree.hpp
---

# SegmentTree

Defined in `segment_tree.hpp`.

```cpp
template <typename Mono>
struct SegmentTree;
```

`Mono` 需满足：

```cpp
using Type = X;
static X e();
static X op(const X&, const X&);
```

`op` 可结合，`e()` 是 `op` 的单位元。维护长度 $n$ 的序列 $a$，区间为 $[l, r)$。

**Member functions**

| 签名 | 语义 | 复杂度 |
| --- | --- | --- |
| `SegmentTree(int n)` | $a_i = e()$ | $O(n)$ |
| `SegmentTree(const std::vector<X>& init)` | $a_i = \text{init}_i$ | $O(n)$ |
| `void modify(int p, const X& v)` | $a_p \leftarrow v$ | $O(\log n)$ |
| `X query(int l, int r)` | 返回 `op(a_l, …, a_{r-1})` | $O(\log n)$ |
| `template <typename F> int findFirst(int l, int r, F&& pred)` | 最小的 $i \in [l, r)$ 使 `pred(a_i)` 为真，无则 $-1$ | $O(\log n)$ |
| `template <typename F> int findLast(int l, int r, F&& pred)` | 最大的 $i \in [l, r)$ 使 `pred(a_i)` 为真，无则 $-1$ | $O(\log n)$ |
| `template <typename F> int maxRight(int l, F&& pred, X& sum)` | 最大的 $r$ 使 `pred(op(a_l, …, a_{r-1}))` 为真 | $O(\log n)$ |
| `template <typename F> int minLeft(int r, F&& pred, X& sum)` | 最小的 $l$ 使 `pred(op(a_l, …, a_{r-1}))` 为真 | $O(\log n)$ |

`pred` 须对 `op` 单调；`maxRight` / `minLeft` 的 `sum` 初值为 `e()`，返回时写回区间聚合值。