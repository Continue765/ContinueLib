---
documentation_of: //graph/range_graph.hpp
---

# RangeGraph

在头文件 `range_graph.hpp` 中定义

```cpp
template <typename T>
struct RangeGraph;
```

用线段树结点表示区间，构造点与区间之间带有向边的图。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 边权类型 |

## 数据成员

| 成员 | 说明 |
| --- | --- |
| `int n` | 原图点数，编号 $0, \dots, n-1$ |
| `int tot` | 当前生成的图的总点数 |

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `RangeGraph(int n)` | 构造 $n$ 个点及线段树内部边，$O(n)$ |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `int add(int u, int v, T w = 1)` | 加入边 $u \to v$，返回边编号，$O(1)$ |
| `void toRange(int u, int l, int r, T w = 1)` | 加入边 $u \to v$，对每个 $v \in [l, r)$，$O(\log n)$ |
| `void fromRange(int l, int r, int v, T w = 1)` | 加入边 $u \to v$，对每个 $u \in [l, r)$，$O(\log n)$ |
| `void RangeToRange(int l1, int r1, int l2, int r2, T w = 1)` | 加入边 $u \to v$（权 `w`），对每个 $u \in [l_1, r_1)$、$v \in [l_2, r_2)$，$O(\log n)$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int out(int i)` | 点 `i` 在出边一侧的编号，$O(1)$ |
| `int in(int i)` | 点 `i` 在入边一侧的编号，$O(1)$ |
| `Digraph<T> build()` | 生成含 `tot` 个点的有向图，$O(n + |E|)$ |

## 注解

原图点 `i` 在 `build()` 结果中对应 `out(i)` 与 `in(i)` 两个编号；从点出发的边用 `out(i)`，连向点的边用 `in(i)`。`add`、`toRange`、`fromRange` 的端点使用这些编号，已有边在 `build()` 时统一复制。

## 示例

```cpp
RangeGraph<int> rg(n);
rg.add(rg.out(0), rg.out(1), 2);
rg.toRange(rg.out(0), 2, n, 1);
rg.fromRange(0, n, rg.in(5), 1);
rg.RangeToRange(0, n / 2, n / 2, n, 3);
auto g = rg.build();
```
