#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P10557

template <typename T>
struct Point {
    T x{}, y{};
    T operator*(const Point &rhs) { return x * rhs.y - rhs.x * y; }
};

#include "../geometry/half_plane_intersection.hpp"

using real = long double;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int a[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) std::cin >> a[i][j];

    std::vector<Line<real>> line;
    for (int _ = 0; _ < n; ++_) {
        real p[3];
        for (int i = 0; i < 3; ++i) std::cin >> p[i];
        real v[3];
        for (int i = 0; i < 3; ++i) {
            v[i] = 0;
            for (int j = 0; j < 3; ++j) v[i] += a[i][j] * p[j];
        }
        line.push_back(Line<real>{v[0] - v[2], v[1] - v[2], v[2]});
    }
    line.push_back(Line<real>{1, 0, 0});
    line.push_back(Line<real>{0, 1, 0});
    line.push_back(Line<real>{-1, -1, 1});

    auto p = half_plane_intersection<Point<real>, Line<real>>(line);
    real S = 0;
    for (int i = 0; i < p.size(); ++i) S += p[i] * p[(i + 1) % p.size()];

    std::cout << std::fixed << std::setprecision(10);
    std::cout << S << '\n';
}
