#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "algebra/monoid.hpp"
#include "graph/tree/lca.hpp"
#include "graph/tree/hld.hpp"
#include "graph/tree/tree_lifting.hpp"
#include "graph/tree/virtual_tree.hpp"

void checkTree(Graph<int, false>& g, int root) {
    // 各套算法独立使用 Tree。
    Tree tree(g, root), hldTree(g, root);
    LCA lca(tree);
    FastLCA fast(tree);
    HLD hld(hldTree);
    TreeLifting<AddMono<i64>, int> lift(tree);
    int n = g.n;
    vector<int> par(n, -1), dep(n), siz(n, 1), order{root};
    vector<i64> dist(n);
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (auto [v, id] : g.adj[u]) if (v != par[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            dist[v] = dist[u] + g.edges[id].w;
            order.push_back(v);
        }
    }
    for (int i = n - 1; i > 0; --i) siz[par[order[i]]] += siz[order[i]];
    assert(tree.fa == par && tree.dep == dep && tree.siz == siz);
    for (int u = 0; u < n; ++u) {
        assert(tree.dist[u] == dist[u]);
        assert(tree.seq[tree.in[u]] == u && tree.out[u] - tree.in[u] == siz[u]);
        if (u == root) assert(tree.pe[u] == -1);
        else {
            auto e = g.edges[tree.pe[u]];
            assert((e.u == u && e.v == par[u]) || (e.v == u && e.u == par[u]));
        }
        int p = u;
        for (int k = 0; k <= dep[u] + 1; ++k) {
            assert(hld.jump(u, k) == p);
            if (p != -1) p = par[p];
        }
    }
    auto naiveLca = [&](int u, int v) {
        while (dep[u] > dep[v]) u = par[u];
        while (dep[v] > dep[u]) v = par[v];
        while (u != v) { u = par[u]; v = par[v]; }
        return u;
    };
    for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
        int p = naiveLca(u, v);
        assert(lca.get(u, v) == p && fast.query(u, v) == p && hld.lca(u, v) == p);
        int d = dep[u] + dep[v] - 2 * dep[p];
        assert(lca.dist(u, v) == d && fast.dist(u, v) == d && hld.dist(u, v) == d);
        assert(lift.lca(u, v) == p && lift.query(u, v).second == dist[u] + dist[v] - 2 * dist[p]);
        assert(hld.isAncester(u, v) == (p == u));
        vector<int> path, tail;
        for (int x = u; x != p; x = par[x]) path.push_back(x);
        path.push_back(p);
        for (int x = v; x != p; x = par[x]) tail.push_back(x);
        reverse(tail.begin(), tail.end());
        path.insert(path.end(), tail.begin(), tail.end());
        for (int k = 0; k <= int(path.size()); ++k) {
            assert(hld.jump(u, v, k) == (k == int(path.size()) ? -1 : path[k]));
        }
        for (bool edge : {false, true}) {
            vector<int> got;
            hld.forPath(u, v, edge, [&](int l, int r, bool rev) {
                if (rev) for (int i = r - 1; i >= l; --i) got.push_back(hldTree.seq[i]);
                else for (int i = l; i < r; ++i) got.push_back(hldTree.seq[i]);
            });
            auto expected = path;
            if (edge) expected.erase(find(expected.begin(), expected.end(), p));
            assert(got == expected);
        }
    }
    for (int rt = 0; rt < n; ++rt) {
        Tree rerooted(g, rt);
        LCA rooted(rerooted);
        for (int u = 0; u < n; ++u) {
            assert(hld.rootedParent(rt, u) == (rt == u ? u : rerooted.fa[u]));
            assert(hld.rootedSize(rt, u) == rerooted.siz[u]);
            for (int v = 0; v < n; ++v) assert(hld.rootedLca(rt, u, v) == rooted.get(u, v));
        }
    }
}

int main() {
    Graph<int, false> g(7);
    g.add(0, 1, 2); g.add(0, 2, 5); g.add(1, 3, 3);
    g.add(1, 4, 7); g.add(2, 5, 11); g.add(5, 6, 13);
    for (int root = 0; root < 7; ++root) checkTree(g, root);
    mt19937 rng(765);
    for (int it = 0; it < 30; ++it) {
        int n = 1 + rng() % 15;
        Graph<int, false> random(n);
        for (int v = 1; v < n; ++v) random.add(v, rng() % v, int(rng() % 21) - 10);
        checkTree(random, rng() % n);
    }

    Tree tree(g);
    for (int root = 0; root < g.n; root++) {
        tree.build(root);
        Tree rebuilt(g, root);
        assert(tree.root == root && tree.fa == rebuilt.fa && tree.dep == rebuilt.dep);
        assert(tree.siz == rebuilt.siz && tree.seq == rebuilt.seq && tree.dist == rebuilt.dist);
    }
    tree.build();
    TreeLifting<AddMono<i64>, int> lift(tree);
    VirtualTree<int> vt(lift);
    vector<int> h{6, 3, 4, 3};
    auto original = h;
    auto [nodes, adj] = vt.build(h);
    assert(h == original && nodes.size() == 5 && adj.size() == 5);
    vector<tuple<int, int, int>> edges;
    for (int u = 0; u < int(nodes.size()); ++u) {
        for (auto [v, w] : adj[u]) if (nodes[u] < nodes[v]) edges.emplace_back(nodes[u], nodes[v], w);
    }
    sort(edges.begin(), edges.end());
    // 虚树边权为原树上的边数。
    assert((edges == vector<tuple<int, int, int>>{{0, 1, 1}, {0, 6, 3}, {1, 3, 1}, {1, 4, 1}}));
    vector<int> single{6};
    auto [nodes2, adj2] = vt.build(single);
    assert(nodes2 == single && adj2.size() == 1 && adj2[0].empty());
    int a, b;
    if (cin >> a >> b) cout << a + b << '\n';
}
