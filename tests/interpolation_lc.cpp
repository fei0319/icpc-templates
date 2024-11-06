#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/polynomial_interpolation

#include "../combinatorics/modint.hpp"
#include "../combinatorics/poly.hpp"

using mint = ModInt<998244353>;
using poly = Poly<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<mint> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        x[i] = t;
    }
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        y[i] = t;
    }

    auto f = poly::interpolation(x, y);
    for (int i = 0; i < n; ++i) std::cout << f[i]() << ' ';
}
