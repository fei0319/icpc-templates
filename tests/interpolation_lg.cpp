#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P5158

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
        int p, q;
        std::cin >> p >> q;
        x[i] = p, y[i] = q;
    }

    auto f = poly::interpolation(x, y);
    for (int i = 0; i < n; ++i) std::cout << f[i]() << ' ';
}
