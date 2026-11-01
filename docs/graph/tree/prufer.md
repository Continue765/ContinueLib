---
documentation_of: //graph/tree/prufer.hpp
---

# prufer

定义于头文件 `prufer.hpp`

```cpp
template <typename T>
vector<int> toPrufer(const Undigraph<T>& tree);  // (1)

Undigraph<int> fromPrufer(const vector<int>& prufer);  // (2)
```

`toPrufer` 返回树 `tree` 的 Prüfer 序列，长度为 $n - 1$；`fromPrufer` 还原 $n = \text{prufer.size()} + 1$ 个点的树，边权为 $1$。

## 参数

| 参数 | 说明 |
| --- | --- |
| `tree` | $n$ 个点、$n - 1$ 条边的树 |
| `prufer` | Prüfer 序列，元素取 $[0, n)$ |

## 复杂度

$O(n)$。

## 示例

```cpp
Undigraph<int> tree(3);
tree.add(0, 1);
tree.add(1, 2);

vector<int> prufer = toPrufer(tree);
Undigraph<int> back = fromPrufer(prufer);
```
