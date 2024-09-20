struct BipartiteColoring {
    std::vector<std::pair<int, int>> edge;
    std::vector<std::vector<int>> adj;
    std::vector<int> color;
    BipartiteColoring(int n) : adj(n) {}
    int add_edge(int u, int v) {
        edge.emplace_back(u, v);
        return edge.size() - 1;
    }
    int operator()() {
        const int n = adj.size();
        std::vector<int> deg(n);

        for (auto [u, v] : edge) {
            ++deg[u];
            ++deg[v];
        }

        const int d = *std::max_element(deg.begin(), deg.end());
        adj.assign(n, std::vector<int>(d, -1));

        for (int i = 0; i < edge.size(); ++i) {
            int id = i;
            auto [x, y] = edge[id];
            int cx = 0, cy = 0;
            while (adj[x][cx] != -1) {
                ++cx;
            }
            while (adj[y][cy] != -1) {
                ++cy;
            }
            while (id != -1) {
                int n_id = adj[y][cx];
                if (n_id == -1) {
                    adj[x][cx] = adj[y][cx] = id;
                    break;
                }
                auto [n_x, n_y] = edge[n_id];
                if (n_x != y) {
                    std::swap(n_x, n_y);
                }
                adj[n_x][cx] = adj[n_y][cx] = -1;
                adj[x][cx] = adj[y][cx] = id;

                id = n_id;
                x = n_x, y = n_y;
                std::swap(cx, cy);
            }
        }

        color.resize(edge.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < d; ++j) {
                if (adj[i][j] != -1) {
                    color[adj[i][j]] = j;
                }
            }
        }
        return d;
    }
};
