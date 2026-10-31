`OrderedSet<K, Comp>` / `OrderedMap<K, V, Comp>`：键唯一，默认升序；下述大小关系按 `Comp`。

`insert` 插入，`erase(k)` 删除，`find(k)` 查找；`lower_bound(k)` / `upper_bound(k)` 返回首个 $>= k$ / $> k$ 的迭代器；Map 的 `a[k]` 访问或插入默认值。均为 $O(log n)$。

`find_by_order(k)` 返回从 $0$ 计的第 `k` 个元素的迭代器，越界返回 `end()`；`order_of_key(k)` 返回严格排在 `k` 前的键数。均为 $O(log n)$。

`a.split(k, b)`：`a` 保留 $<= k$，$> k$ 移入 `b`，清空旧 `b`；$O(n + m)$，其中 $m$ 为旧 `b` 大小。

`a.join(b)`：合并并清空 `b`，要求一棵树的所有键均小于另一棵树的所有键；$O(log(n + m))$。
