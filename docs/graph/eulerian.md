---
documentation_of: //graph/eulerian.hpp
---

# eulerian

定义于头文件 `eulerian.hpp`

```cpp
template <typename T, bool dir>
int isEulerian(const Graph<T, dir>& g, int s = -1);  // (1)

template <typename T, bool dir>
bool isEulerianPath(const Graph<T, dir>& g, int s = -1);  // (2)

template <typename T, bool dir>
bool isEulerianCircuit(const Graph<T, dir>& g, int s = -1);  // (3)

template <typename T, bool dir>
pair<vector<int>, vector<int>> findEulerian(const Graph<T, dir>& g, int s = -1);  // (4)
```

`isEulerian` 返回 `0`（不存在欧拉路径）、`1`（存在欧拉路径）或 `2`（存在欧拉回路）；`s != -1` 时要求存在以 `s` 为起点的对应路径。`isEulerianPath` 与 `isEulerianCircuit` 分别等价于 `isEulerian(g, s) >= 1` 与 `== 2`。`findEulerian` 返回 `{vs, es}`，`es[i]` 为连接 `vs[i]` 与 `vs[i+1]` 的边编号，不存在时返回 `{ {}, {} }`，`s == -1` 时自动选起点。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图 |
| `s` | 起点，`-1` 表示不指定 |

## 复杂度

$O(n + m)$。

## 示例

```cpp
Digraph<int> g(n);
g.add(0, 1);
g.add(1, 2);
int type = isEulerian(g);
bool hasCircuit = isEulerianCircuit(g);
auto [vs, es] = findEulerian(g);
```
