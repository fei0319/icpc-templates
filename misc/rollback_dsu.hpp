struct RollbackDSU {
    std::vector<int> p;
    std::vector<std::pair<int, int>> log;
    RollbackDSU(int n) : p(n, -1) {}
    bool share(int a, int b) {
        return find(a) == find(b);
    }
    int sz(int u) {
        return -p[find(u)];
    }
    int find(int u) {
        return p[u] < 0 ? u : find(p[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (p[u] > p[v]) std::swap(u, v);
        log.emplace_back(v, p[v]);
        p[u] += p[v], p[v] = u;
        return true;
    }
    int time() {
        return log.size();
    }
    void rollback(int t) {
        while ((int)log.size() > t) {
            auto [v, pv] = log.back();
            log.pop_back();
            p[p[v]] -= pv, p[v] = pv;
        }
    }
};
