---
documentation_of: //data_structure/fenwick/fenwick_2d.hpp
---

# Fenwick2D

定义于头文件 `fenwick_2d.hpp`

```cpp
template <typename Mono>
struct Fenwick2D;
```

维护 $h \times w$ 的矩阵 $a$，支持单点聚合与矩形前缀聚合查询，各操作 $O(\log h \log w)$。

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
| `Fenwick2D(int h, int w)` | 构造 $h \times w$ 个 `e()` 的矩阵，$O(hw)$ |
| `Fenwick2D(const vector<vector<X>>& init)` | 以 `init` 构造，$O(hw)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void add(int x, int y, const X& v)` | $a_{x,y} \leftarrow \text{op}(a_{x,y}, v)$，$O(\log h \log w)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `X query(int x, int y)` | 返回 $[0, x) \times [0, y)$ 的聚合，$O(\log h \log w)$ |
| `X query(int x1, int x2, int y1, int y2)` | 返回 $[x_1, x_2) \times [y_1, y_2)$ 的聚合，$O(\log h \log w)$ |

## 注解

四参数 `query` 需 `Mono::inv`。

## 示例

```cpp
Fenwick2D<AddMono<i64>> f(3, 4);
f.add(1, 2, 5);
i64 s = f.query(3, 4);
i64 r = f.query(0, 2, 1, 3);

Fenwick2D<AddMono<i64>> g(vector<vector<i64>>{ {1, 2}, {3, 4} });
i64 t = g.query(1, 2);
```
