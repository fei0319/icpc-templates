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
            return atan2(u.b, -u.a) > atan2(v.b, -v.a);
        });
        {
            int j = -1;
            for (int i = 0; i < lines.size(); ++i) {
                if (j != -1 && lines[j].dir() * lines[i].dir() == 0) {
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
