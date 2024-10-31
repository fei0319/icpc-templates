#include <bits/stdc++.h>

template <typename T>
struct Point {
    T x{}, y{};
    friend T operator*(const Point &lhs, const Point &rhs) {
        return lhs.x * rhs.y - rhs.x * lhs.y;
    }
};

#include "../geometry/half_plane_intersection.hpp"

using real = long double;

Line<real> operator-(const Line<real> &lhs, const Line<real> &rhs) {
    return Line<real>{lhs.a - rhs.a, lhs.b - rhs.b, lhs.c - rhs.c};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Point<real>> p(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        p[i].x = x;
        p[i].y = y;
    }

    std::vector<Line<real>> lines(n);
    for (int i = 0; i < n; ++i) {
        auto [x0, y0] = p[i];
        auto [x1, y1] = p[(i + 1) % n];
        lines[i] = Line<real>{y0 - y1, x1 - x0, x0 * y1 - x1 * y0};
    }

    auto area = [](const std::vector<Point<real>> &p) -> real {
        real res = 0;
        for (int i = 0; i < p.size(); ++i) {
            auto [x0, y0] = p[i];
            auto [x1, y1] = p[(i + 1) % p.size()];
            res += x0 * y1 - x1 * y0;
        }
        return res / 2;
    };

    real S = area(half_plane_intersection<Point<real>, Line<real>>(lines));
    for (int i = 1; i < n; ++i) {
        lines.push_back(lines[i] - lines[0]);
    }
    real T = area(half_plane_intersection<Point<real>, Line<real>>(lines));

    std::cout << std::fixed << std::setprecision(4);
    std::cout << T / S << '\n';
}
