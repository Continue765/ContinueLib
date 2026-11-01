---
documentation_of: //data_structure/fenwick/dual_fenwick.hpp
---

# DualFenwick

在头文件 `dual_fenwick.hpp` 中定义

```cpp
template <typename Abel>
struct DualFenwick;
```

维护长度 $n$ 的序列 $a$，支持区间聚合与单点查询，各操作 $O(\log n)$。

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
| `DualFenwick(int n)` | 构造 $n$ 个 `e()` 的序列，$O(n)$ |
| `DualFenwick(const vector<X>& init)` | 以 `init` 构造，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void add(int l, int r, const X& v)` | 对 $i \in [l, r)$ 执行 $a_i \leftarrow \text{op}(a_i, v)$，$O(\log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int x)` | 返回 $a_x$，$O(\log n)$ |

## 示例

```cpp
DualFenwick<AddMono<i64>> df(5);
df.add(1, 4, 3);
i64 v = df.query(2);

DualFenwick<AddMono<i64>> init(vector<i64>{1, 2, 3});
i64 u = init.query(0);
```
