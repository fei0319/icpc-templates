#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P5488

#include "../combinatorics/modint.hpp"
#include "../combinatorics/poly.hpp"

using mint = ModInt<1004535809>;
using poly = Poly<mint, 702606812>;
using i64 = int64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, t;
    std::string s;
    std::cin >> n >> s >> t;

    mint k = 0;
    for (char c : s) {
        k = k * 10 + (c - '0');
    }

    poly a(n);
    for (auto &i : a) {
        int x;
        std::cin >> x;
        i = x;
    }

    if (n == 1) {
        std::cout << a[0]() << '\n';
        return 0;
    }

    poly f(n);
    f[0] = 1, f[1] = -1;
    if (t == 0) f = f.inv();

    f = exp(log(f) * k);
    a *= f;
    a.resize(n);
    for (auto i : a) {
        std::cout << i() << ' ';
    }
    std::cout << '\n';
}
