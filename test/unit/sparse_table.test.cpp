#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/sparse_table.hpp"

int main() {
    vector<long long> a{8, -2, 6, 6, 0, -9, 4, 3, -1};
    SparseTable<MinMono<long long>> st(a);
    for (int l = 0; l < (int)a.size(); ++l) {
        for (int r = l + 1; r <= (int)a.size(); ++r) {
            assert(st.query(l, r) == *min_element(a.begin() + l, a.begin() + r));
        }
    }
    st.init(vector<long long>{7});
    assert(st.query(0, 1) == 7);

    int x, y;
    if (cin >> x >> y) cout << x + y << '\n';
}
