---
documentation_of: //graph/shortest_path/restore_path.hpp
---

# restorePath

定义于头文件 `restore_path.hpp`

```cpp
vector<int> restorePath(vector<int>& pre, int t);
```

由前驱数组 `pre` 还原从源点到 `t` 的一条路径，返回按源点到 `t` 顺序排列的点序列。

## 参数

| 参数 | 说明 |
| --- | --- |
| `pre` | 前驱数组，`pre[v] = -1` 表示 `v` 没有前驱 |
| `t` | 路径终点 |

## 返回值

返回从源点到 `t` 的路径，首元素为源点、末元素为 `t`；`t` 不可达时为 `{t}`。

## 复杂度

$O(k)$，$k$ 为路径长度。

## 示例

```cpp
vector<int> pre(n, -1);
pre[1] = 0;
pre[2] = 1;
vector<int> path = restorePath(pre, 2);
```
