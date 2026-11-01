---
documentation_of: //data_structure/disjoint_spase_table.hpp
---

# DisjointSparseTable

在头文件 `disjoint_spase_table.hpp` 中定义

```cpp
template <typename Mono>
struct DisjointSparseTable;
```

维护长度 $n$ 的序列，支持任意区间聚合查询。建表 $O(n \log n)$ 时间与空间，查询 $O(1)$。

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
| `DisjointSparseTable(const vector<X>& a)` | 以 `a` 建表，$O(n \log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int l, int r)` | 返回 `op(a_l, …, a_{r-1})`，$0 \le l < r \le n$，$O(1)$ |

## 示例

```cpp
DisjointSparseTable<AddMono<i64>> dst(vector<i64>{1, 2, 3, 4, 5});
i64 s = dst.query(1, 4);
```
