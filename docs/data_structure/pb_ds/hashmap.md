---
documentation_of: //data_structure/pb_ds/hashmap.hpp
---

# HashMap

在头文件 `hashmap.hpp` 中定义

```cpp
struct splitmix64Hash;

template <typename K, typename V, typename Hash = splitmix64Hash>
using HashMap = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64Hash>
using HashSet = HashMap<K, __gnu_pbds::null_type, Hash>;
```

哈希映射与哈希集合，单次操作期望 $O(1)$，默认哈希带固定随机偏移。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `K` | 键类型 |
| `V` | 值类型，`HashSet` 中为 `__gnu_pbds::null_type` |
| `Hash` | 哈希函数类型，可对 `u64` 调用并返回 `size_t`，默认为 `splitmix64Hash` |

## 成员函数

**容量**

| 成员函数 | 说明 |
| --- | --- |
| `size_t size() const` | 元素个数 |
| `bool empty() const` | 是否为空 |
| `void clear()` | 清空 |

**映射操作（`HashMap`）**

| 成员函数 | 说明 |
| --- | --- |
| `V& operator[](const K& k)` | 返回 `k` 对应的值，`k` 不存在时插入默认值 |
| `auto insert(const pair<K, V>& p)` | 返回 `pair<iterator, bool>` |
| `size_t erase(const K& k)` | 删除 `k`，返回删除个数 |
| `auto find(const K& k)` | 返回指向 `k` 的迭代器，不存在则为 `end()` |

**集合操作（`HashSet`）**

| 成员函数 | 说明 |
| --- | --- |
| `auto insert(const K& k)` | 返回 `pair<iterator, bool>` |
| `auto find(const K& k)` | 返回指向 `k` 的迭代器，不存在则为 `end()` |
| `size_t erase(const K& k)` | 删除 `k`，返回删除个数 |

## splitmix64Hash

| 成员函数 | 说明 |
| --- | --- |
| `size_t operator()(u64 x) const` | 返回 `splitmix64(x + 随机偏移)` |

## 示例

```cpp
HashMap<int, i64> cnt;
cnt[3] += 1;
if (cnt.find(4) == cnt.end()) {
    cnt.insert({4, 0});
}
cnt.erase(3);
size_t sz = cnt.size();
bool e = cnt.empty();

HashSet<i64> vis;
vis.insert(5);
bool has = vis.find(5) != vis.end();
vis.erase(5);
vis.clear();
```
