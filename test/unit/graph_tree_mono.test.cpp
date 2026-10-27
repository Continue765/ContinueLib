#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <graph/tree/tree_mono.hpp>
struct Strings {
    using Type = string;
    static Type e() { return ""; }
    static Type op(const Type& a, const Type& b) { return a + b; }
};

template <bool edge>
void check(Undigraph<int>& g, int root, mt19937& rng) {
    Tree<int> tree(g, root);
    HLD<int> hld(tree);
    int n = tree.n;
    vector<string> a(n - edge);
    for (int i = 0; i < int(a.size()); i++) a[i] = char('a' + i % 26);
    TreeMono<int, Strings, edge> ds(hld, a);
    TreeMono<int, Strings, edge> empty(hld);
    assert(empty.allQuery().empty());
    for (int it = 0; it < 100; it++) {
        if (!a.empty()) {
            int i = rng() % a.size();
            string x(1, char('a' + rng() % 26));
            if (rng() % 2) { ds.modify(i, x); a[i] = x; }
            else { ds.apply(i, x); a[i] += x; }
        }
        string all;
        for (int w : tree.seq) if (!edge || w != root) all += a[edge ? tree.pe[w] : w];
        assert(ds.allQuery() == all);
        int u = rng() % n, v = rng() % n;
        vector<int> path{u};
        int d = hld.dist(u, v);
        for (int k = 1; k <= d; k++) path.push_back(hld.jump(u, v, k));
        string expected;
        vector<string> prefixes;
        if constexpr (!edge) expected = a[u];
        prefixes.push_back(expected);
        for (int k = 1; k <= d; k++) {
            int x = path[k-1], y = path[k];
            expected += a[edge ? tree.pe[tree.dep[x] > tree.dep[y] ? x : y] : y];
            prefixes.push_back(expected);
        }
        assert(ds.pathQuery(u, v) == expected);
        for (int limit = 0; limit <= int(expected.size()) + 1; limit++) {
            int last = -1;
            for (int k = 0; k <= d; k++) if (int(prefixes[k].size()) <= limit) last = path[k];
            auto pred = [&](const string& s) { return int(s.size()) <= limit && expected.starts_with(s); };
            assert(ds.maxPath(pred, u, v) == last);
        }
        int rt = edge ? root : int(rng() % n);
        Tree<int> rooted(g, rt);
        string sub;
        for (int w : tree.seq) {
            if (edge) {
                if (w != u && hld.isAncester(u, w)) sub += a[tree.pe[w]];
            } else if (rooted.in[u] <= rooted.in[w] && rooted.in[w] < rooted.out[u]) sub += a[w];
        }
        assert(ds.subtreeQuery(u, rt) == sub);
    }
}
int main() {
    mt19937 rng(41278);
    for (int it = 0; it < 100; it++) {
        int n = 1 + rng() % 30;
        Undigraph<int> g(n);
        for (int v = 1; v < n; v++) g.add(v, rng() % v);
        int root = rng() % n;
        check<false>(g, root, rng);
        check<true>(g, root, rng);
    }
    int a, b;
    if (cin >> a >> b) {
        cout << a + b << '\n';
    }
}
