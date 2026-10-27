#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <graph/tree/dsu_on_tree.hpp>

int main() {
    std::mt19937 rng(7654178);
    for (int it = 0; it < 2000; it++) {
        int n = 1 + rng() % 100;
        Undigraph<int> g(n);
        for (int v = 1; v < n; v++) {
            int u = it % 3 == 0 ? v - 1 : it % 3 == 1 ? 0 : int(rng() % v);
            g.add(u, v);
        }
        Tree tree(g, rng() % n);
        HLD hld(tree);
        std::vector<int> col(n), cnt(10);
        for (int& c : col) c = rng() % 10;
        dsuOnTree(hld, [&](int u) { cnt[col[u]]++; }, [&](int u) {
            std::vector<int> want(10);
            for (int v = 0; v < n; v++) {
                int p = v;
                while (p != -1 && p != u) p = tree.fa[p];
                if (p == u) want[col[v]]++;
            }
            assert(cnt == want);
        }, [&] { std::fill(cnt.begin(), cnt.end(), 0); });
    }
    int a, b;
    if (std::cin >> a >> b) std::cout << a + b << '\n';
}
