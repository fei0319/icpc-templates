template <typename P, typename T>
std::pair<P, T> smallest_circle(const std::vector<P> &p, const auto &EPS) {
    auto sqr = [](const T &x) {
        return x * x;
    };
    auto sqrdis = [&](const P &a, const P &b) {
        return sqr(a.x - b.x) + sqr(a.y - b.y);
    };
    auto geto = [&](const P &a, const P &b, const P &c) {
        T a1, a2, b1, b2, c1, c2;
        P ans;
        a1 = 2 * (b.x - a.x), b1 = 2 * (b.y - a.y);
        c1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
        a2 = 2 * (c.x - a.x), b2 = 2 * (c.y - a.y);
        c2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
        if (fabs(a1) < EPS) {
            ans.y = c1 / b1;
            ans.x = (c2 - ans.y * b2) / a2;
        } else if (fabs(b1) < EPS) {
            ans.x = c1 / a1;
            ans.y = (c2 - ans.x * a2) / b2;
        } else {
            ans.x = (c2 * b1 - c1 * b2) / (a2 * b1 - a1 * b2);
            ans.y = (c2 * a1 - c1 * a2) / (b2 * a1 - b1 * a2);
        }
        return ans;
    };

    P o = p[0];
    T sqr_r = 0;
    for (int i = 0; i < p.size(); ++i) {
        if (sqrdis(p[i], o) < sqr_r + EPS) continue;
        o.x = (p[i].x + p[0].x) / 2;
        o.y = (p[i].y + p[0].y) / 2;
        sqr_r = sqrdis(p[i], p[0]) / 4;
        for (int j = 1; j < i; ++j) {
            if (sqrdis(p[j], o) < sqr_r + EPS) continue;
            o.x = (p[i].x + p[j].x) / 2;
            o.y = (p[i].y + p[j].y) / 2;
            sqr_r = sqrdis(p[i], p[j]) / 4;
            for (int k = 0; k < j; ++k) {
                if (sqrdis(p[k], o) < sqr_r + EPS) continue;
                o = geto(p[i], p[j], p[k]);
                sqr_r = sqrdis(o, p[i]);
            }
        }
    }
    return std::make_pair(o, (T)sqrtl(sqr_r));
}
