---
documentation_of: //data_structure/pb_ds/red_black_tree.hpp
---

# OrderedMap

在头文件 `red_black_tree.hpp` 中定义

```cpp
template <typename K, typename V, typename Comp = less<K>>
using OrderedMap = __gnu_pbds::tree<
    K, V, Comp,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = less<K>>
using OrderedSet = OrderedMap<K, __gnu_pbds::null_type, Comp>;
```

平衡二叉搜索树，支持按排名查找与查询排名，各操作 $O(\log n)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `K` | 键类型 |
| `V` | 值类型，`OrderedSet` 中为 `__gnu_pbds::null_type` |
| `Comp` | 比较器，默认为 `less<K>` |

## 成员函数

**容量**

| 成员函数 | 说明 |
| --- | --- |
| `size_t size() const` | 元素个数 |
| `bool empty() const` | 是否为空 |
| `void clear()` | 清空 |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `auto insert(const pair<K, V>& p)` | 返回 `pair<iterator, bool>` |
| `size_t erase(const K& k)` | 删除 `k`，返回删除个数 |
| `void erase(iterator it)` | 删除 `it` 指向的元素 |

**查找**

| 成员函数 | 说明 |
| --- | --- |
| `auto find(const K& k)` | 返回指向 `k` 的迭代器，不存在则为 `end()` |
| `auto lower_bound(const K& k)` | 返回首个不小于 `k` 的元素的迭代器 |
| `auto upper_bound(const K& k)` | 返回首个大于 `k` 的元素的迭代器 |

**排名**

| 成员函数 | 说明 |
| --- | --- |
| `auto find_by_order(size_t k)` | 返回第 $k$ 小元素的迭代器，$k$ 从 $0$ 起 |
| `size_t order_of_key(const K& k)` | 返回严格小于 `k` 的元素个数 |

## 示例

```cpp
OrderedMap<int, i64> mp;
mp.insert({3, 10});
mp[4] = 20;
mp[5] = 30;

auto it = mp.find(3);
auto lo = mp.lower_bound(2);
auto hi = mp.upper_bound(3);
auto kth = mp.find_by_order(1);
size_t rank = mp.order_of_key(4);

mp.erase(5);
mp.erase(it);
mp.clear();

OrderedSet<i64> st;
st.insert(7);
st.insert(2);
size_t sz = st.size();
bool e = st.empty();
```
