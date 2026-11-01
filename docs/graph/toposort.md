---
documentation_of: //graph/toposort.hpp
---

# toposort

定义于头文件 `toposort.hpp`

```cpp
template <typename T>
vector<int> toposort(const Digraph<T>& g);  // (1)

template <typename T>
vector<int> lexMinToposort(const Digraph<T>& g);  // (2)
```

返回 `g` 的拓扑序，长度为 $n$；存在环时返回空序列。`lexMinToposort` 返回字典序最小的拓扑序。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向图 |

## 复杂度

`toposort` 为 $O(n + m)$，`lexMinToposort` 为 $O((n + m) \log n)$。

## 示例

```cpp
Digraph<int> g(n);
g.add(0, 1);
g.add(1, 2);
vector<int> order = toposort(g);
vector<int> best = lexMinToposort(g);
```
