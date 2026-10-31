`PairingHeap<T, Comp>`：默认大根堆，`greater<T>` 为小根堆。

`push(x)` 插入并返回句柄；`top()` 取堆顶；`pop()` 删除堆顶；`modify(it, x)` 修改句柄对应元素；`erase(it)` 删除元素。修改不使句柄失效，删除使其失效。

`a.join(b)` 合并并清空 `b`；`a.split(pred, b)` 将满足 `pred` 的元素移入 `b`，清空旧 `b`；`erase_if(pred)` 删除满足 `pred` 的元素并返回数量。

`top`、`push`、`join`：$O(1)$；`pop`、`modify`、`erase`：均摊 $O(log n)$；`erase_if`、`clear`：$O(n)$；`split`：$O(n + m)$，$m$ 为旧 `b` 大小。
