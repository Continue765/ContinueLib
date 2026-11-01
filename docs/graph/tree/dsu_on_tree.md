---
documentation_of: //graph/tree/dsu_on_tree.hpp
---

# dsuOnTree

定义于头文件 `dsu_on_tree.hpp`

```cpp
template <typename T, typename F1, typename F2, typename F3>
void dsuOnTree(const HLD<T>& hld, F1&& add, F2&& query, F3&& reset);
```

在 `hld` 上做树上启发式合并：按 HL 序的逆序枚举点 $u$，把 $u$ 与其所有轻儿子子树内的点加入维护结构后调用 `query(u)`，当 $u$ 为链顶时调用 `reset()`。共调用 `add` $O(n \log n)$ 次，`query` $n$ 次，`reset` $O(n)$ 次。

## 参数

| 参数 | 说明 |
| --- | --- |
| `hld` | 重链剖分 |
| `add` | 回调 `add(int u)`，将点 $u$ 加入维护结构 |
| `query` | 回调 `query(int u)`，此时维护结构中的点恰为以 $u$ 为根时 $u$ 的子树 |
| `reset` | 回调 `reset()`，清空维护结构 |

## 示例

```cpp
Undigraph<int> g(n);
Tree<int> tree(g);
HLD<int> hld(tree);

vector<int> col(n);
vector<int> cnt(n), best(n);
int cur = 0;
dsuOnTree(hld,
    [&](int u) { cur += (cnt[col[u]]++ == 0); },
    [&](int u) { best[u] = cur; },
    [&]() { fill(cnt.begin(), cnt.end(), 0); cur = 0; });
```
