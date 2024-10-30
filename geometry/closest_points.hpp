template <typename T, typename P>
std::pair<int, int> closest_points(std::vector<P> p) {
    std::vector<int> a(p.size());
    std::iota(a.begin(), a.end(), 0);
    std::sort(a.begin(), a.end(), [&](int i, int j) {
        return p[i].x < p[j].x;
    });

    auto dist = [&](int u, int v) -> T {
        T dx = p[u].x - p[v].x;
        T dy = p[u].y - p[v].y;
        return dx * dx + dy * dy;
    };

    std::set<std::pair<T, int>> s;
    std::pair<int, int> res{a[0], a[1]};
    T sqr_d = dist(a[0], a[1]);
    T d = sqrtl(sqr_d) + 0.1;
    s.emplace(p[a[0]].y, a[0]);
    s.emplace(p[a[1]].y, a[1]);

    for (int i = 2, j = 0; i < p.size(); ++i) {
        if (sqr_d == 0) {
            return res;
        }

        while (j < i && p[a[i]].x - p[a[j]].x > d) {
            s.erase(std::make_pair(p[a[j]].y, a[j]));
            ++j;
        }
        for (auto it = s.lower_bound(std::make_pair(p[a[i]].y - d, 0));
             it != s.end(); ++it) {
            if (it->first > p[a[i]].y + d) {
                break;
            }
            if (dist(a[i], it->second) < sqr_d) {
                res = {a[i], it->second};
                sqr_d = dist(a[i], it->second);
                d = sqrtl(sqr_d) + 0.1;
            }
        }
        s.emplace(p[a[i]].y, a[i]);
    }

    return res;
}
