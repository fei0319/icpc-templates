#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/closest_pair

#include "../geometry/closest_points.hpp"

using i64 = int64_t;
struct Point {
    i64 x{}, y{};
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (auto &[x, y] : p) {
        std::cin >> x >> y;
    }

    auto [u, v] = closest_points<i64, Point>(p);
    std::cout << u << ' ' << v << '\n';
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
