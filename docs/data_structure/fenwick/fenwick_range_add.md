---
documentation_of: //data_structure/fenwick/fenwick_range_add.hpp
---

# FenwickRangeAdd

在头文件 `fenwick_range_add.hpp` 中定义

```cpp
template <typename Abel>
struct FenwickRangeAdd;
```

维护长度 $n$ 的序列 $a$，支持区间聚合与区间查询，各操作 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `Abel` | 聚合运算类型，满足 Abel 群要求 |

## 成员类型

| 成员类型 | 定义 |
| --- | --- |
| `X` | `typename Abel::Type` |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `FenwickRangeAdd(int n)` | 构造 $n$ 个 `e()` 的序列，$O(n)$ |
| `FenwickRangeAdd(const vector<X>& init)` | 以 `init` 构造，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void add(int l, int r, const X& v)` | 对 $i \in [l, r)$ 执行 $a_i \leftarrow \text{op}(a_i, v)$，$O(\log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int r)` | 返回 $\text{op}(a_0, \dots, a_{r-1})$，$O(\log n)$ |
| `X query(int l, int r)` | 返回 $\text{op}(a_l, \dots, a_{r-1})$，$O(\log n)$ |

## 注解

除 `Abel::inv` 外还使用 `Abel::pow`，其指数取 $[-n, n]$ 内的整数。

## 示例

```cpp
FenwickRangeAdd<AddMono<i64>> f(5);
f.add(0, 3, 2);
i64 s = f.query(4);
i64 t = f.query(1, 4);

FenwickRangeAdd<AddMono<i64>> g(vector<i64>{1, 2, 3});
i64 u = g.query(2, 3);
```
