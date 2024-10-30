template <typename T, typename P = Point<T>>
struct Line {
    T a, b, c;
    P dir() const {
        return P{b, -a};
    }
    bool operator()(const P &p) {
        return a * p.x + b * p.y + c >= 0;
    }
    bool contains(const Line &other) const {
        if (a * a > b * b) return c * fabsl(other.a) > other.c * fabsl(a);
        return c * fabsl(other.b) > other.c * fabsl(b);
    }
    friend P intersection(const Line &u, const Line &v) {
        T denominator = u.a * v.b - v.a * u.b;
        T x = -(u.c * v.b - v.c * u.b) / denominator;
        T y = (u.c * v.a - v.c * u.a) / denominator;
        return P{x, y};
    }
};

template <typename P, typename L>
std::vector<P> half_plane_intersection(std::vector<L> lines) {
    std::sort(lines.begin(), lines.end(), [](const L &u, const L &v) {
        return atan2(u.b, -u.a) > atan2(v.b, -v.a);
    });
    int j = -1;
    for (int i = 0; i < lines.size(); ++i)
        if (j != -1 && lines[j].dir() * lines[i].dir() == 0) {
            if (lines[j].contains(lines[i])) lines[j] = lines[i];
        } else {
            lines[++j] = lines[i];
        }
    lines.resize(j + 1);

    std::vector<L> q(lines.size());
    std::vector<P> c(lines.size());
    int l = 0, r = 0;
    q[0] = lines[0];
    for (int i = 1; i < lines.size(); ++i) {
        while (l < r && !lines[i](c[r])) --r;
        while (l < r && !lines[i](c[l + 1])) ++l;
        q[++r] = lines[i];
        if (l < r) c[r] = intersection(q[r], q[r - 1]);
    }
    while (l < r && !q[l](c[r])) --r;
    c[l] = intersection(q[l], q[r]);
    return std::vector<P>{c.begin() + l, c.begin() + r + 1};
}
