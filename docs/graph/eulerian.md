---
documentation_of: //graph/eulerian.hpp
---

# isEulerian

在头文件 `eulerian.hpp` 中定义

```cpp
template <typename T, bool dir>
int isEulerian(const Graph<T, dir>& g, int s = -1);
```

判断图 `g` 的欧拉路径与欧拉回路存在性，返回 $0/1/2$。

## 参数

| 参数 | 说明 |
| --- | --- |
| `g` | 有向或无向图 |
| `s` | 指定的起点，`-1` 表示不指定 |

## 返回值

| 值 | 说明 |
| --- | --- |
| `0` | 不存在欧拉路径 |
| `1` | 存在欧拉路径，不存在欧拉回路 |
| `2` | 存在欧拉回路 |

`s != -1` 时，返回非零还要求存在以 `s` 为起点的对应路径。没有边时返回 `2`。

## 判定函数

| 函数 | 说明 |
| --- | --- |
| `bool isEulerianPath(const Graph<T, dir>& g, int s = -1)` | `isEulerian(g, s) >= 1` |
| `bool isEulerianCircuit(const Graph<T, dir>& g, int s = -1)` | `isEulerian(g, s) == 2` |

## 求欧拉路径

```cpp
template <typename T, bool dir>
pair<vector<int>, vector<int>> findEulerian(const Graph<T, dir>& g, int s = -1);
```

返回 `{vs, es}`：`vs` 为点序列，`es` 为边序列，`es[i]` 是连接 `vs[i]` 与 `vs[i+1]` 的边编号。`s` 为 `-1` 时自动选择起点。不存在时返回 `{ {}, {} }`；无边时返回 `{ {s}, {} }`。

## 复杂度

$O(n + m)$，$n$ 为点数，$m$ 为边数。

## 示例

```cpp
Graph<int, true> g(n);
g.add(0, 1);
g.add(1, 2);
int type = isEulerian(g);
bool hasCircuit = isEulerianCircuit(g);
auto [vs, es] = findEulerian(g);
```
