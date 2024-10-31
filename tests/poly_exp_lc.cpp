#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/exp_of_formal_power_series

#include "../combinatorics/modint.hpp"
#include "../combinatorics/poly.hpp"

using mint = ModInt<998244353>;
using poly = Poly<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    poly f(n);
    for (auto &i : f) {
        int x;
        std::cin >> x;
        i = x;
    }

    f = exp(f);

    for (auto i : f) {
        std::cout << i() << ' ';
    }
}
