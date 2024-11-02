#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/scc

#include "../graph/scc.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    SCC g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    auto bel = g();
    std::vector<std::vector<int>> coms(
        *std::max_element(bel.begin(), bel.end()) + 1);
    for (int i = 0; i < n; ++i) {
        coms[bel[i]].push_back(i);
    }
    std::reverse(coms.begin(), coms.end());

    std::cout << coms.size() << '\n';
    for (auto com : coms) {
        std::cout << com.size() << ' ';
        for (int i : com) std::cout << i << ' ';
        std::cout << '\n';
    }
}
