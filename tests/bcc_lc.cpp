#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/biconnected_components

#include "../graph/bcc.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    BCC g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    auto coms = g();

    std::cout << coms.size() << '\n';
    for (auto com : coms) {
        std::cout << com.size() << ' ';
        for (int i : com) std::cout << i << ' ';
        std::cout << '\n';
    }
}
