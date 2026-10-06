#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

using i128 = __int128_t;
using u128 = __uint128_t;

template <typename T>
constexpr T inf = numeric_limits<T>::max() / 2;
template <>
constexpr int inf<int> = 1e9;
template <>
constexpr i64 inf<i64> = 1e18;

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}