#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P5050

#include "../combinatorics/modint.hpp"
#include "../combinatorics/poly.hpp"

using mint = ModInt<998244353>;
using poly = Poly<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    poly f(n + 1);
    std::vector<mint> p(m);

    for (int i = 0; i <= n; ++i) {
        int x;
        std::cin >> x;
        f[i] = x;
    }
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        p[i] = x;
    }

    auto res = f(p);
    for (auto i : res) std::cout << i() << '\n';
}
