---
documentation_of: //data_structure/fenwick/fenwick.hpp
---

# Fenwick

在头文件 `fenwick.hpp` 中定义

```cpp
template <typename Mono>
struct Fenwick;
```

维护长度 $n$ 的序列 $a$，支持单点聚合与前缀聚合查询，各操作 $O(\log n)$。

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
| `Fenwick(int n)` | 构造 $n$ 个 `e()` 的序列，$O(n)$ |
| `Fenwick(const vector<X>& init)` | 以 `init` 构造，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void add(int x, const X& v)` | $a_x \leftarrow \text{op}(a_x, v)$，$O(\log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int x)` | 返回 $\text{op}(a_0, \dots, a_{x-1})$，$O(\log n)$ |
| `X query(int l, int r)` | 返回 $\text{op}(a_l, \dots, a_{r-1})$，$O(\log n)$ |
| `int kth(X k)` | 返回最大的 $x$ 使 $\text{op}(a_0, \dots, a_{x-1}) \le k$，$O(\log n)$ |

## 注解

`query(l, r)` 需 `Mono::inv`。`kth` 要求前缀聚合关于下标单调不减。

## 示例

```cpp
Fenwick<AddMono<i64>> fen(5);
fen.add(0, 3);
fen.add(2, 4);
i64 s = fen.query(3);
i64 t = fen.query(1, 4);
int p = fen.kth(4);

Fenwick<GcdMono<i64>> g(vector<i64>{6, 10, 15});
i64 d = g.query(3);
```
