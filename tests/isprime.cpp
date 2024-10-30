#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/primality_test

using i64 = int64_t;
using i128 = __int128_t;

#include "../number_theory/isprime.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    int64_t n;
    std::cin >> q;

    while (q--) {
        std::cin >> n;
        std::cout << (isprime(n) ? "Yes\n" : "No\n");
    }
}
