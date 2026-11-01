---
documentation_of: //data_structure/binary_trie.hpp
---

# BinaryTrie

在头文件 `binary_trie.hpp` 中定义

```cpp
struct BinaryTrie;
```

维护 $[0, 2^{31})$ 内整数的可重集，支持插入、删除与最大异或查询，单次操作 $O(\log V)$，$V = 2^{31}$。

## 成员函数

**构造**

| 成员函数 | 说明 |
| --- | --- |
| `BinaryTrie(int n = 0)` | 分配大小为 $n$ 的结点池，下标 $1$ 为根结点 |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void insert(int x)` | 插入一个 $x$ |
| `void erase(int x)` | 删除一个 $x$ |

**查询**

| 成员函数 | 说明 |
| --- | --- |
| `int query(int x)` | 返回集合中与 $x$ 异或的最大值 |

## 注解

结点池须容纳根结点 $1$ 与每次 `insert` 产生的至多 $31$ 个新结点。

## 示例

```cpp
BinaryTrie trie(n);
trie.insert(3);
trie.insert(5);
int mx = trie.query(4);
trie.erase(3);
```
