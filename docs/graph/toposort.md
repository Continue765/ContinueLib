---
documentation_of: //graph/toposort.hpp
---

# toposort

在头文件 `toposort.hpp` 中定义

```cpp
template <typename T>
vector<int> toposort(const Digraph<T>& g);
```

求有向图 `g` 的拓扑序，长度为 $n$；图中存在环时返回空序列。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向图 |

## 复杂度

$O(n + m)$，$n$ 为点数，$m$ 为边数。

## lexMinToposort

```cpp
template <typename T>
vector<int> lexMinToposort(const Digraph<T>& g);
```

求字典序最小的拓扑序，长度为 $n$；图中存在环时返回空序列。

$O((n + m) \log n)$。

## 示例

```cpp
Digraph<int> g(n);
g.add(0, 1);
g.add(1, 2);
vector<int> order = toposort(g);
vector<int> best = lexMinToposort(g);
```
