#include <bits/stdc++.h>

// https://loj.ac/p/101
// https://www.luogu.com.cn/problem/P3376

#include "../graph/flow.hpp"

using i64 = int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s, --t;

    Flow<i64> f(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        --u, --v;
        f.add_edge(u, v, c);
    }

    std::cout << f(s, t, 1e18) << '\n';
}
