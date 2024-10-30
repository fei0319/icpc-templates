std::vector<int> fa(n, -1), size(n), son(n, -1);
std::vector<i64> dep(n);
auto dfs1 = [&](auto &self, int node) -> void {
    size[node] = 1;
    for (auto [to, c] : adj[node]) {
        if (to == fa[node]) {
            continue;
        }
        fa[to] = node;
        dep[to] = dep[node] + c;
        self(self, to);
        size[node] += size[to];
        if (son[node] == -1 || size[to] > size[son[node]]) {
            son[node] = to;
        }
    }
};
dfs1(dfs1, 0);

std::vector<int> top(n, -1);
auto dfs2 = [&](auto &self, int node) -> void {
    if (son[node] != -1) {
        top[son[node]] = top[node];
        self(self, son[node]);
    }
    for (auto [to, c] : adj[node]) {
        if (to == fa[node] || to == son[node]) {
            continue;
        }
        top[to] = to;
        self(self, to);
    }
};
top[0] = 0;
dfs2(dfs2, 0);

auto lca = [&](int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            std::swap(x, y);
        }
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
};

auto dist = [&](int x, int y) {
    return dep[x] + dep[y] - dep[lca(x, y)] * 2;
};
