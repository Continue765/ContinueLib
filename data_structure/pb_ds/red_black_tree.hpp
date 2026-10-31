#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <common.hpp>

template <typename K, typename V, typename Comp = less<K>>
using OrderedMap = __gnu_pbds::tree<
	K, V, Comp,
	__gnu_pbds::rb_tree_tag,
	__gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = less<K>>
using OrderedSet = OrderedMap<K, __gnu_pbds::null_type, Comp>;