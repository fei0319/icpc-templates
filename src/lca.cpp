template <int B>
class LCA {
    std::vector<std::vector<int>> adj;
    std::vector<int> dfn;
    std::array<std::vector<int>, B> st;
    int tot;

    void dfs(int x, int fa) {
        st[0][tot] = fa, dfn[x] = ++tot;
        for (int to : adj[x])
            if (to != fa) dfs(to, x);
    }
    int min(int x, int y) const {
        return dfn[x] < dfn[y] ? x : y;
    }

public:
    explicit LCA(int n) : adj(n), dfn(n), tot(0) {
        for (auto &v : st) {
            v.resize(n);
        }
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init(int rt) {
        const int n = adj.size();
        dfs(rt, -1);
        for (int i = 1; i < B; ++i)
            for (int j = 1; j + (1 << i) - 1 < n; ++j)
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
    }
    int lca(int x, int y) const {
        if (x == y) return x;
        if (dfn[x] > dfn[y]) std::swap(x, y);
        const int lg = std::__lg(dfn[y] - dfn[x]);
        return min(st[lg][dfn[x]], st[lg][dfn[y] - (1 << lg)]);
    }
};
