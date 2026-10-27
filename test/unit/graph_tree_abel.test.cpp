#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <algebra/monoid.hpp>
#include <graph/tree/tree_abel.hpp>

template <bool edge>
void check(Undigraph<int>& g, int root, mt19937& rng) {
    Tree<int> tree(g, root);
    HLD<int> hld(tree);
    int n = g.n;
    vector<i64> a(n - edge);
    for (auto& x : a) x = int(rng() % 101) - 50;
    TreeAbel<int, AddMono<i64>, edge> ds(hld, a), zero(hld);
    auto value = [&](int u) -> i64 {
        if constexpr (edge) return u == root ? 0 : a[tree.vToE(u)];
        else return a[u];
    };
    for (int u = 0; u < n; u++) {
        i64 sum = 0;
        for (int v = u; v != -1; v = tree.fa[v]) sum += value(v);
        assert(ds.rootQuery(u) == sum && zero.rootQuery(u) == 0);
        for (int v = 0; v < n; v++) {
            int l = hld.lca(u, v);
            i64 expected = edge ? 0 : value(l);
            for (int x = u; x != l; x = tree.fa[x]) expected += value(x);
            for (int x = v; x != l; x = tree.fa[x]) expected += value(x);
            assert(ds.pathQuery(u, v) == expected);
            assert(zero.pathQuery(u, v) == 0);
        }
        for (int rt = 0; rt < n; rt++) {
            Tree<int> rooted(g, rt);
            i64 expected = 0;
            if constexpr (edge) {
                for (int i = 0; i < n - 1; i++) {
                    auto e = g.edges[i];
                    auto inside = [&](int v) { return rooted.in[u] <= rooted.in[v] && rooted.in[v] < rooted.out[u]; };
                    if (inside(e.u) && inside(e.v)) expected += a[i];
                }
            } else {
                for (int v : rooted.subtree(u)) expected += a[v];
            }
            assert(ds.subtreeQuery(u, rt) == expected);
            assert(zero.subtreeQuery(u, rt) == 0);
        }
    }
}

int main() {
    mt19937 rng(81251);
    for (int it = 0; it < 60; it++) {
        int n = 1 + rng() % 25;
        Undigraph<int> g(n);
        for (int u = 1; u < n; u++) g.add(u, rng() % u);
        int root = rng() % n;
        check<false>(g, root, rng);
        check<true>(g, root, rng);
    }
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
