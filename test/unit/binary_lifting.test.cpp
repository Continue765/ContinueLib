#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "data_structure/binary_lifting.hpp"

int main() {
    BinaryLifting<AddMono<long long>> lift(8);
    vector<int> nxt{1, 2, 3, -1, 5, 6, 4, 7};
    vector<long long> cost{3, -2, 8, 0, 5, 1, -4, 7};
    for (int u = 0; u < 8; ++u) lift.add(u, nxt[u], cost[u]);
    lift.build();
    for (int start = 0; start < 8; ++start) {
        for (int step = 0; step < 16; ++step) {
            int u = start;
            long long sum = 0;
            for (int i = 0; i < step && u != -1; ++i) {
                sum += cost[u];
                u = nxt[u];
            }
            assert(lift.jump(start, step) == u);
            assert(((lift.query(start, step) == pair<int, long long>(u, sum))));
        }
    }
    assert(((lift.query(0, 0) == pair<int, long long>(0, 0))));

    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
