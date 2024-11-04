#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum

#include "../combinatorics/modint.hpp"
#include "../data_structure/link_cut_tree.hpp"

using i64 = int64_t;

struct IntAdd {
    i64 x;
    IntAdd operator*(const IntAdd &rhs) { return IntAdd{x + rhs.x}; }
};

LinkCutTree<IntAdd, static_cast<int>(2e5 + 1)> t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        t.set(i + 1, IntAdd{a[i]});
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        t.link(u + 1, v + 1);
    }

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            t.cut(u + 1, v + 1);
            t.link(w + 1, x + 1);
        } else if (op == 1) {
            int p, x;
            std::cin >> p >> x;
            t.set(p + 1, IntAdd{a[p] += x});
        } else {
            int u, v;
            std::cin >> u >> v;
            std::cout << t.query(u + 1, v + 1).x << '\n';
        }
    }
}
