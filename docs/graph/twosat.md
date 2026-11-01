---
documentation_of: //graph/twosat.hpp
---

# TwoSat

定义于头文件 `twosat.hpp`

```cpp
struct TwoSat;
```

维护 $n$ 个布尔变量 $x_0, \dots, x_{n-1}$ 上的 2-SAT 子句，并求出一组可满足解。

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `TwoSat(int n)` | 构造 $n$ 个无约束变量，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void addClause(int u, bool f, int v, bool g)` | 加入子句 $(x_u = f) \lor (x_v = g)$，$O(1)$ |
| `void set(int u, bool f)` | 加入子句 $(x_u = f)$，$O(1)$ |
| `void implies(int u, bool f, int v, bool g)` | 加入蕴含 $(x_u = f) \Rightarrow (x_v = g)$，$O(1)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `pair<bool, vector<int>> satisfiable()` | 求一组赋值，$O(n + m)$ |

## 返回值

`satisfiable()` 返回 `{ok, ans}`：`ok` 为子句集是否可满足，`ans[i]` 为 $x_i$ 的取值（`1` 为真、`0` 为假），`ok` 为 `false` 时 `ans` 为空。

## 复杂度

$n$ 为变量数，$m$ 为加入的子句条数。

## 示例

```cpp
TwoSat ts(n);
ts.addClause(0, true, 1, false);
ts.set(2, true);
ts.implies(0, true, 1, true);
auto [ok, ans] = ts.satisfiable();
```
