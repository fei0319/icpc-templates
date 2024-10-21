struct BCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low;
    std::vector<std::vector<int>> coms;
    int cur, cnt;
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for (int to : adj[x]) {
            if (dfn[to] == -1) {
                dfs(to, x);
                low[x] = std::min(low[x], low[to]);
            } else {
                low[x] = std::min(low[x], dfn[to]);
            }
        }
        if (p == -1) {
            if (adj[x].empty()) coms.push_back({x});
        } else if (low[x] == dfn[p]) {
            std::vector<int> com{x, p};
            while (stk.back() != x) {
                com.push_back(stk.back());
                stk.pop_back();
            }
            stk.pop_back();
            coms.push_back(std::move(com));
        }
    }

public:
    explicit BCC(int n) : n(n), adj(n), dfn(n, -1), low(n), cur(0), cnt(0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    std::vector<std::vector<int>> operator()() {
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1) stk.clear(), dfs(i, -1);
        return coms;
    }
};
