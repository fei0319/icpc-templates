template <typename T, typename P = Point<T>>
struct Line {
    T a, b, c;
    bool operator()(const P &p) { return a * p.x + b * p.y + c >= 0; }
};

template <typename P, typename L>
std::vector<P> half_plane_intersection(std::vector<L> lines,
                                       const double EPS = 1e-9) {
    auto contains = [](const auto &lhs, const auto &rhs) {
        return lhs.c * (std::abs(rhs.a) + std::abs(rhs.b)) >
               rhs.c * (std::abs(lhs.a) + std::abs(lhs.b));
    };
    auto its = [&](auto &dst, const auto &u, const auto &v) {
        auto denominator = u.a * v.b - v.a * u.b;
        if (std::abs(denominator) < EPS) return false;
        auto x = -(u.c * v.b - v.c * u.b) / denominator,
             y = (u.c * v.a - v.c * u.a) / denominator;
        dst = P{x, y};
        return true;
    };
    auto dir = [](auto &x) { return P{x.b, -x.a}; };

    std::sort(lines.begin(), lines.end(), [](const L &u, const L &v) {
        return atan2(u.b, -u.a) > atan2(v.b, -v.a);
    });
    int j = -1;
    for (int i = 0; i < lines.size(); ++i)
        if (j != -1 && std::abs(dir(lines[j]) * dir(lines[i])) < EPS) {
            if (contains(lines[j], lines[i])) lines[j] = lines[i];
        } else lines[++j] = lines[i];
    lines.resize(j + 1);

    std::vector<L> q(lines.size());
    std::vector<P> c(lines.size());
    int l = 0, r = 0;
    q[0] = lines[0];
    for (int i = 1; i < lines.size(); ++i) {
        while (l < r && !lines[i](c[r])) --r;
        while (l < r && !lines[i](c[l + 1])) ++l;
        q[++r] = lines[i];
        if (l < r)
            if (!its(c[r], q[r], q[r - 1])) return {};
    }
    while (l < r && !q[l](c[r])) --r;
    if (!its(c[l], q[l], q[r])) return {};
    return std::vector<P>{c.begin() + l, c.begin() + r + 1};
}
