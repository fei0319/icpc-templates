#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/division_of_polynomials

#include "../combinatorics/modint.hpp"
#include "../combinatorics/poly.hpp"

using mint = ModInt<998244353>;
using poly = Poly<mint>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    poly f(n), g(m);
    for (auto &i : f) {
        int x;
        std::cin >> x;
        i = x;
    }
    for (auto &i : g) {
        int x;
        std::cin >> x;
        i = x;
    }

    auto q = f / g, r = f % g;
    // To test % operator, r is not calculated by f - q * g
    while (!r.empty() && r.back()() == 0) r.pop_back();

    std::cout << q.size() << ' ' << r.size() << '\n';
    for (auto i : q) std::cout << i() << ' ';
    std::cout << '\n';
    for (auto i : r) std::cout << i() << ' ';
    std::cout << '\n';
}
