#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/directedmst

#include "../misc/rollback_dsu.hpp"
// Order matters
#include "../graph/directed_mst.hpp"

struct Edge {
    int u, v, w;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, s;
    std::cin >> n >> m >> s;

    std::vector<Edge> edge(m);
    for (auto &[u, v, w] : edge) std::cin >> u >> v >> w;

    auto [cost, p] = dmst<int64_t, Edge>(edge, n, s);

    std::cout << cost << '\n';
    for (int i : p) std::cout << (i == -1 ? s : i) << ' ';
    return 0;
}
