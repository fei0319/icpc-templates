#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/static_convex_hull

#include "../geometry/convex_hull.hpp"

using i64 = int64_t;
struct Point {
    int x, y;
    friend i64 operator*(const Point &lhs, const Point &rhs) {
        return (i64)lhs.x * rhs.y - (i64)rhs.x * lhs.y;
    }
    friend Point operator-(const Point &lhs, const Point &rhs) {
        return Point{lhs.x - rhs.x, lhs.y - rhs.y};
    }
    friend bool operator==(const Point &lhs, const Point &rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (auto &[x, y] : p) {
        std::cin >> x >> y;
    }

    auto [hi, lo] = make_hull(p);
    if (n) {
        std::reverse(hi.begin(), hi.end());
        if (hi.back() == lo.front()) {
            hi.pop_back();
        }
        for (auto p : hi) {
            if (p == lo.back()) continue;
            lo.push_back(p);
        }
    }

    std::cout << lo.size() << '\n';
    for (auto [x, y] : lo) {
        std::cout << x << ' ' << y << '\n';
    }
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
