`HashMap<K, V, Hash>` / `HashSet<K, Hash>`。

`insert({k, v})` / `insert(k)` 插入，返回 `(迭代器, 是否成功)`；`erase(k)` 删除并返回是否存在；`find(k)` 查找，未找到返回 `end()`；Map 的 `a[k]` 访问值，键不存在时插入默认值。

上述操作期望 $O(1)$（插入、删除为均摊），最坏 $O(n)$；`clear()` 为 $O(n)$。
