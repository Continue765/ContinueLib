---
documentation_of: //data_structure/binary_lifting.hpp
---

# BinaryLifting

定义于头文件 `binary_lifting.hpp`

```cpp
template <typename Mono>
struct BinaryLifting;
```

维护 $n$ 个点的后继链，支持定长跳转与跳转路径上的信息聚合。建表 $O(n \log n)$，单次操作 $O(\log n)$。

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
| `BinaryLifting(int n)` | 构造 $n$ 个点、后继均为 $-1$、信息均为 `e()` 的结构 |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void add(int u, int v, const X& x)` | $u$ 的后继置为 $v$，该步信息置为 $x$ |
| `void build()` | 预处理倍增表，$O(n \log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `pair<int, X> query(int u, i64 step)` | 返回自 $u$ 走 `step` 步到达的点与途经信息的聚合，$O(\log n)$ |
| `int jump(int u, i64 step)` | 返回自 $u$ 走 `step` 步到达的点，$O(\log n)$ |

## 注解

`v` 取 $-1$ 表示无后继；`add` 须在 `build` 前调用，`step` 取 $0 \le \text{step} < 2^{\lfloor \log_2 n \rfloor + 1}$。

## 示例

```cpp
BinaryLifting<MaxMono<int>> up(n);
up.add(0, 1, 5);
up.add(1, 2, 7);
up.add(2, -1, 0);
up.build();

auto [v, mx] = up.query(0, 2);
int w = up.jump(0, 1);
```
