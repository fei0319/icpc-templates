#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/lca

#include "../graph/lca.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    LCA<20> t(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        t.add_edge(p, i);
    }
    t.init(0);

    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << t.lca(u, v) << '\n';
    }
}
