#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/sum_of_multiplicative_function

#include "../combinatorics/modint.hpp"

using mint = ModInt<469762049>;
using i64 = int64_t;

template <typename T>
T power_sum(i64 n, int k) {
    return 0;
}
template <>
mint power_sum(i64 n, int k) {
    static const mint HALF = mint{1} / 2;
    if (k == 0) return n;
    if (k == 1) return mint{n} * (n + 1) * HALF;
    return 0;
}

#include "../number_theory/min25.hpp"

void solve() {
    i64 n;
    int a, b;
    std::cin >> n >> a >> b;

    std::array<mint, 2> arr{a, b};
    auto f = [&](int p, int e) -> mint {
        return (i64)a * e + (i64)b * p;
    };
    Min25<mint, 2, decltype(f)> s{arr, f};

    std::cout << s(n)() << '\n';
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
