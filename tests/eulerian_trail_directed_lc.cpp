#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/eulerian_trail_directed

#include "../graph/eulerian_trail.hpp"

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> din(n), dout(n);
    std::vector<std::pair<int, int>> edge(m);
    EulerianTrail g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v, true);
        ++dout[u];
        ++din[v];
        edge[i] = {u, v};
    }

    int s = 0;
    for (int i = 0; i < n; ++i) {
        if (dout[i] + din[i]) s = i;
    }
    for (int i = 0; i < n; ++i) {
        if (dout[i] > din[i]) s = i;
    }

    auto [v, e] = g(s);
    if (e.size() != m) {
        std::cout << "No\n";
        return;
    }
    for (int i = 0; i < e.size(); ++i) {
        if (edge[e[i]].first != v[i]) {
            std::swap(edge[e[i]].first, edge[e[i]].second);
        }
        if (edge[e[i]].first != v[i] || edge[e[i]].second != v[i + 1]) {
            std::cout << "No\n";
            return;
        }
    }

    std::cout << "Yes\n";
    for (int i : v) std::cout << i << ' ';
    std::cout << '\n';
    for (int i : e) std::cout << i << ' ';
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
