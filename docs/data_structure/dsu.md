---
documentation_of: //data_structure/dsu.hpp
---

# DSU

定义于头文件 `dsu.hpp`

```cpp
struct DSU;
```

维护 $n$ 个元素的并查集，支持合并、连通性判断与集合大小查询，单次操作均摊 $O(\log n)$。

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `DSU(int n)` | 构造 $n$ 个各自成集合的元素 |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `bool merge(int x, int y)` | 合并 `x` 与 `y` 所在集合，返回是否发生了合并 |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int find(int x)` | 返回 `x` 所在集合的代表元 |
| `bool same(int x, int y)` | 判断 `x` 与 `y` 是否同属一个集合 |
| `int size(int x)` | 返回 `x` 所在集合的大小 |

## 示例

```cpp
DSU dsu(n);
dsu.merge(0, 1);
bool ok = dsu.same(0, 1);
int s = dsu.size(1);
int r = dsu.find(0);
```
