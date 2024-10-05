#include <bits/stdc++.h>

template <typename T>
class HalfPlaneIntersection {
    struct Point {
        T x{0}, y{0};
        friend T operator*(const Point &lhs, const Point &rhs) {
            return lhs.x * rhs.y - lhs.y * rhs.x;
        }
    };
    struct Line {
        T a, b, c;
        Point dir() const {
            return Point{b, -a};
        }
        bool operator()(const Point &p) {
            return a * p.x + b * p.y + c >= 0;
        }
        bool contains(const Line &other) const {
            if (a * a > b * b) {
                return c * fabsl(other.a) > other.c * fabsl(a);
            }
            return c * fabsl(other.b) > other.c * fabsl(b);
        }
    };
    Point intersection(const Line &u, const Line &v) {
        T denominator = u.a * v.b - v.a * u.b;
        T x = -(u.c * v.b - v.c * u.b) / denominator;
        T y = (u.c * v.a - v.c * u.a) / denominator;
        return Point{x, y};
    }

public:
    using line_t = Line;
    using point_t = Point;
    std::vector<Point> operator()(std::vector<Line> lines) {
        std::sort(lines.begin(), lines.end(), [](const Line &u, const Line &v) {
            return atan2(u.b, -u.a) < atan2(v.b, -v.a);
        });
        {
            int j = -1;
            for (int i = 0; i < lines.size(); ++i) {
                if (j != -1 && lines[j].dir() * lines[i].dir() == 0 &&
                    lines[j].a * lines[i].a + lines[j].b * lines[i].b > 0) {
                    if (lines[j].contains(lines[i])) {
                        lines[j] = lines[i];
                    }
                } else {
                    lines[++j] = lines[i];
                }
            }
            lines.resize(j + 1);
        }

        std::vector<Line> q(lines.size());
        std::vector<Point> c(lines.size());
        int l = 0, r = 0;
        q[0] = lines[0];
        for (int i = 1; i < lines.size(); ++i) {
            while (l < r && !lines[i](c[r])) {
                --r;
            }
            while (l < r && !lines[i](c[l + 1])) {
                ++l;
            }
            q[++r] = lines[i];
            if (l < r) {
                c[r] = intersection(q[r], q[r - 1]);
            }
        }
        while (l < r && !q[l](c[r])) {
            --r;
        }
        c[l] = intersection(q[l], q[r]);
        return std::vector<Point>{c.begin() + l, c.begin() + r + 1};
    }
};

using real = long double;
using hpi = HalfPlaneIntersection<real>;
using Line = hpi::line_t;
using Point = hpi::point_t;

int main() {
    int n;
    std::cin >> n;

    std::vector<Line> lines;
    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;

        std::vector<Point> b(m);
        for (int j = 0; j < m; ++j) {
            int x, y;
            std::cin >> x >> y;
            b[j].x = x;
            b[j].y = y;
        }

        for (int j = 0; j < m; ++j) {
            auto [x1, y1] = b[j];
            auto [x2, y2] = b[(j + 1) % m];
            real a = y1 - y2, b = x2 - x1, c = -(a * x1 + b * y1);
            lines.push_back(Line{a, b, c});
        }
    }
    lines.push_back(Line{0, 1, 1e3});
    lines.push_back(Line{0, -1, 1e3});
    lines.push_back(Line{1, 0, 1e3});
    lines.push_back(Line{-1, 0, 1e3});

    auto points = hpi()(lines);
    real ans = 0;

    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < points.size(); ++i) {
        auto [x1, y1] = points[i];
        auto [x2, y2] = points[(i + 1) % points.size()];
        ans += x1 * y2 - x2 * y1;
    }

    std::cout << fabsl(ans) / 2 << '\n';
}
