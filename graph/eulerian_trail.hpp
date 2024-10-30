class EulerianTrail {
    std::vector<int> edge, e, v;
    std::vector<std::vector<int>> adj;
    std::vector<uint8_t> vist;
    void dfs(int node) {
        while (!adj[node].empty()) {
            int id = adj[node].back();
            adj[node].pop_back();
            if (vist[id]) continue;
            vist[id] = true;
            dfs(edge[id] - node);
            v.push_back(edge[id] - node);
            e.push_back(id);
        }
    }

public:
    explicit EulerianTrail(int n) : adj(n) {}

    void add_edge(int u, int v, bool directed = false) {
        int id = edge.size();
        edge.push_back(u + v);
        if (directed) {
            adj[u].push_back(id);
        } else {
            adj[u].push_back(id);
            adj[v].push_back(id);
        }
    }
    std::pair<std::vector<int>, std::vector<int>> operator()(int s) {
        vist.assign(edge.size(), false);
        dfs(s);
        v.push_back(s);
        std::reverse(v.begin(), v.end());
        std::reverse(e.begin(), e.end());
        return {v, e};
    }
};
