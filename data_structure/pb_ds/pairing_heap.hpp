#pragma once
#include <common.hpp>
#include <ext/pb_ds/priority_queue.hpp>

template <typename T, typename Comp = less<T>>
using PairingHeap = __gnu_pbds::priority_queue<T, Comp, __gnu_pbds::pairing_heap_tag>;