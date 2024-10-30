struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for (int to : adj[x]) {
            if (dfn[to] == -1) {
                dfs(to);
                low[x] = std::min(low[x], low[to]);
            } else if (bel[to] == -1) {
                low[x] = std::min(low[x], dfn[to]);
            }
        }
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            ++cnt;
        }
    }

public:
    explicit SCC(int n)
        : n(n), adj(n), dfn(n, -1), low(n), bel(n, -1), cur(0), cnt(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
    std::vector<int> operator()() {
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1) dfs(i);
        return bel;
    }
};
