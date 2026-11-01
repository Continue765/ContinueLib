---
documentation_of: //data_structure/sparse_table.hpp
---

# SparseTable

定义于头文件 `sparse_table.hpp`

```cpp
template <typename Mono>
struct SparseTable;
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
| `SparseTable(const vector<X>& a)` | 以 `a` 建表，$O(n \log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int l, int r)` | 返回 `op(a_l, …, a_{r-1})`，$0 \le l < r \le n$，$O(1)$ |

## 注解

`op` 须幂等。

## 示例

```cpp
SparseTable<MinMono<int>> st(vector<int>{3, 1, 4, 1, 5});
int mn = st.query(1, 4);
SparseTable<GcdMono<int>> g(vector<int>{6, 4, 8});
int d = g.query(0, 3);
```
