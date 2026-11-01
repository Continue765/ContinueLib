---
documentation_of: //data_structure/segment_tree/dynamic_segment_tree.hpp
---

# DynamicSegmentTree

定义于头文件 `dynamic_segment_tree.hpp`

```cpp
template <typename ActMono>
struct DynamicSegmentTree;
```

维护值域 $[0, n)$ 上的序列 $a$，支持单点赋值、区间作用与区间聚合。节点按需分配，操作 $O(\log n)$。

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
| `DynamicSegmentTree(int n)` | 值域为 $[0, n)$ 的全 `Mono::e()` 序列，$O(1)$ |
| `DynamicSegmentTree(const vector<X>& init)` | 以 `init` 构造，令 $n$ 为其长度，$O(n)$ |

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
| `template <typename F> int maxRight(int l, F&& pred, X& sum)` | 返回最大的 $r$ 使 `pred(a_l op … op a_{r-1})` 为真，无则 $n$，$O(\log n)$ |
| `template <typename F> int minLeft(int r, F&& pred, X& sum)` | 返回最小的 $l$ 使 `pred(a_l op … op a_{r-1})` 为真，无则 $0$，$O(\log n)$ |

## 注解

`pred` 须对聚合运算单调。

## 示例

```cpp
DynamicSegmentTree<SumAdd<i64>> seg(1 << 30);
DynamicSegmentTree<SumAdd<i64>> full(vector<i64>{3, 1, 4, 1, 5});

seg.modify(123456, 7);
seg.apply(0, 1000, 2);
i64 s = seg.query(0, 1 << 20);

i64 sum = 0;
int r = seg.maxRight(0, [](i64 v) { return v <= 1000; }, sum);
sum = 0;
int l = seg.minLeft(1000, [](i64 v) { return v <= 1000; }, sum);

int i = seg.findFirst(0, 2000, [](i64 v) { return v > 0; });
int j = seg.findLast(0, 2000, [](i64 v) { return v > 0; });
```
