template <typename P>
auto make_hull(std::vector<P> p) {
    std::sort(p.begin(), p.end(), [&](auto a, auto b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    std::vector<P> hi, lo;
    for (auto p : p) {
        while (hi.size() > 1 &&
               (hi.back() - hi[hi.size() - 2]) * (p - hi.back()) >= 0) {
            hi.pop_back();
        }
        while (!hi.empty() && hi.back().x == p.x) {
            hi.pop_back();
        }
        hi.push_back(p);
        while (lo.size() > 1 &&
               (lo.back() - lo[lo.size() - 2]) * (p - lo.back()) <= 0) {
            lo.pop_back();
        }
        if (lo.empty() || lo.back().x < p.x) {
            lo.push_back(p);
        }
    }
    return std::make_pair(hi, lo);
}
