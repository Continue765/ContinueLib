---
documentation_of: //data_structure/pb_ds/pairing_heap.hpp
---

# PairingHeap

定义于头文件 `pairing_heap.hpp`

```cpp
template <typename T, typename Comp = less<T>>
using PairingHeap = __gnu_pbds::priority_queue<T, Comp, __gnu_pbds::pairing_heap_tag>;
```

可合并的优先队列，各操作均摊 $O(\log n)$，`join` 均摊 $O(1)$。

## 模板参数

| 参数 | 说明 |
| --- | --- |
| `T` | 元素类型 |
| `Comp` | 比较器，默认为 `less<T>` |

## 成员函数

**容量**

| 成员函数 | 说明 |
| --- | --- |
| `void push(const T& x)` | 插入 `x` |
| `void pop()` | 弹出堆顶 |
| `const T& top() const` | 返回堆顶 |
| `size_t size() const` | 元素个数 |
| `bool empty() const` | 是否为空 |
| `void clear()` | 清空 |

**修改**

| 成员函数 | 说明 |
| --- | --- |
| `void modify(iterator it, const T& x)` | 把 `it` 指向的元素改为 `x` |
| `void erase(iterator it)` | 删除 `it` 指向的元素 |
| `void join(PairingHeap& other)` | 把 `other` 的元素并入并清空 `other` |

**迭代**

| 成员函数 | 说明 |
| --- | --- |
| `iterator begin()` | 指向堆顶 |
| `iterator end()` | 尾后迭代器 |

## 示例

```cpp
PairingHeap<int> pq;
pq.push(3);
pq.push(1);
int mx = pq.top();
pq.pop();
size_t sz = pq.size();
bool e = pq.empty();

PairingHeap<int> other;
other.push(5);
pq.join(other);

auto it = pq.begin();
pq.modify(it, 9);
pq.erase(it);
pq.clear();
```
