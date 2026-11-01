---
documentation_of: //graph/difference_constraints.hpp
---

# DifferenceConstraints

定义于头文件 `difference_constraints.hpp`

```cpp
template <typename T>
struct DifferenceConstraints;
```

维护 $n$ 个变量 $x_0, \dots, x_{n-1}$ 上的差分约束，并求出一组可行解。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 边权与变量取值类型，满足有符号整数要求 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `DifferenceConstraints(int n)` | 构造 $n$ 个无约束变量的系统，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void constraint(int u, int v, T w)` | 加入 $x_v - x_u \le w$，$O(1)$ |
| `void lowerBound(int u, int v, T w)` | 加入 $x_v - x_u \ge w$，$O(1)$ |
| `void equality(int u, int v, T w)` | 加入 $x_v - x_u = w$，$O(1)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `pair<bool, vector<T>> solve()` | 求一组可行解，$O(nm)$ |

## 返回值

`solve()` 返回 `{ok, x}`：`ok` 为系统是否可满足，`x[i]` 为 $x_i$ 的一组取值，`ok` 为 `false` 时 `x` 为空。

## 复杂度

$n$ 为变量数，$m$ 为 `constraint` / `lowerBound` 调用产生的约束条数。

## 示例

```cpp
DifferenceConstraints<int> dc(n);
dc.constraint(0, 1, 5);
dc.lowerBound(0, 1, -2);
dc.equality(1, 2, 3);
auto [ok, x] = dc.solve();
```
