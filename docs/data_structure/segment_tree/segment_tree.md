---
documentation_of: //data_structure/segment_tree/segment_tree.hpp
---

# SegmentTree

单点赋值 + 区间聚合，区间 $[l, r)$，下标从 $0$ 起。

`Mono` 提供 `Type`、`e()`（单位元）、`op(a, b)`（可结合）。

| 接口 | 说明 |
| --- | --- |
| `SegmentTree(int n)` / `SegmentTree(vector<X> init)` | 建树，$O(n)$ |
| `modify(p, v)` | $a_p \leftarrow v$ |
| `query(l, r)` | `op` 作用于 $a_l, \dots, a_{r-1}$ |
| `findFirst(l, r, pred)` | 区间内首个使 `pred` 成立的下标，无则 $-1$ |
| `findLast(l, r, pred)` | 同上，从右往左 |
| `maxRight(l, pred, sum)` / `minLeft(r, pred, sum)` | 从 `sum = e()` 起向一侧累加，返回边界 |

除建树外均为 $O(\log n)$。`pred` 对 `op` 单调时 `findFirst` / `findLast` / `maxRight` / `minLeft` 才成立。

```cpp
SegmentTree<AddMono<int>> seg({1, 2, 3, 4});
int s = 0;
int r = seg.maxRight(0, [](int v) { return v <= 12; }, s);  // r = 2, s = 11
```
