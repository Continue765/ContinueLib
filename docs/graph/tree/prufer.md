---
documentation_of: //graph/tree/prufer.hpp
---

# toPrufer

在头文件 `prufer.hpp` 中定义

```cpp
template <typename T>
vector<int> toPrufer(const Undigraph<T>& tree);
```

返回树 `tree` 的 Prüfer 序列，与 `fromPrufer` 互逆。

## 参数

| 参数 | 说明 |
| --- | --- |
| `tree` | $n$ 个点、$n - 1$ 条边的树 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `vector<int>` | 长度为 $n - 1$ 的 Prüfer 序列 |

## 复杂度

$O(n)$。

## 示例

```cpp
Undigraph<int> g(3);
g.add(0, 1);
g.add(1, 2);

vector<int> prufer = toPrufer(g);
```

# fromPrufer

在头文件 `prufer.hpp` 中定义

```cpp
Undigraph<int> fromPrufer(const vector<int>& prufer);
```

由 Prüfer 序列 `prufer` 还原 $n = \text{prufer.size()} + 1$ 个点的树。

## 参数

| 参数 | 说明 |
| --- | --- |
| `prufer` | Prüfer 序列，元素取 $[0, n)$ |

## 返回值

| 值 | 说明 |
| --- | --- |
| `Undigraph<int>` | 还原出的树，边权均为 $1$ |

## 复杂度

$O(n)$。

## 示例

```cpp
vector<int> prufer{1, 0};

Undigraph<int> tree = fromPrufer(prufer);
int n = tree.n;
```
