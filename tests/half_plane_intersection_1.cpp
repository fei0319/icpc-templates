#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P4196

template <typename T>
struct Point {
    T x{}, y{};
    friend T operator*(const Point &lhs, const Point &rhs) {
        return lhs.x * rhs.y - rhs.x * lhs.y;
    }
};

#include "../geometry/half_plane_intersection.hpp"

using real = long double;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Line<real>> line;
    for (int i = 0; i < n; ++i) {
        int n;
        std::cin >> n;
        std::vector<Point<real>> a(n);
        for (auto &a : a) {
            int x, y;
            std::cin >> x >> y;
            a.x = x, a.y = y;
        }

        for (int i = 0; i < n; ++i) {
            auto [x0, y0] = a[i];
            auto [x1, y1] = a[(i + 1) % a.size()];
            line.push_back(
                Line<real>{y0 - y1, x1 - x0, (real)x0 * y1 - (real)x1 * y0});
        }
    }

    line.push_back(Line<real>{1, 0, 1e9});
    line.push_back(Line<real>{-1, 0, 1e9});
    line.push_back(Line<real>{0, 1, 1e9});
    line.push_back(Line<real>{0, -1, 1e9});

    auto p = half_plane_intersection<Point<real>, Line<real>>(line);
    real S = 0;
    for (int i = 0; i < p.size(); ++i) {
        S += p[i] * p[(i + 1) % p.size()];
    }
    S /= 2;

    std::cout << std::fixed << std::setprecision(3);
    std::cout << S << '\n';
}
