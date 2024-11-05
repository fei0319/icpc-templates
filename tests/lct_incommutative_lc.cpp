#include <bits/stdc++.h>

// https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite

#include "../combinatorics/modint.hpp"
#include "../data_structure/link_cut_tree.hpp"

using mint = ModInt<998244353>;

struct Matrix {
    mint a[2][2]{};
    Matrix operator*(const Matrix &rhs) const {
        Matrix res;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    res.a[i][k] += a[i][j] * rhs.a[j][k];
                }
            }
        }
        return res;
    }
};

struct Info {
    Matrix x, y;
    Info operator*(const Info &rhs) {
        Info res;
        res.x = x * rhs.x;
        res.y = rhs.y * y;
        return res;
    }
    void flip() { std::swap(x, y); }
    static Info from_linear(int c, int d) {
        Info res;
        res.x.a[0][0] = c;
        res.x.a[1][0] = d;
        res.x.a[1][1] = 1;
        res.y = res.x;
        return res;
    }
};

LinkCutTree<Info, static_cast<int>(2e5 + 1)> t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        t.set(i + 1, Info::from_linear(a, b));
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        t.link(u + 1, v + 1);
    }

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            t.cut(u + 1, v + 1);
            t.link(w + 1, x + 1);
        } else if (op == 1) {
            int p, c, d;
            std::cin >> p >> c >> d;
            t.set(p + 1, Info::from_linear(c, d));
        } else {
            int u, v, x;
            std::cin >> u >> v >> x;
            Matrix res;
            res.a[0][0] = x, res.a[0][1] = 1;
            res = res * t.query(u + 1, v + 1).x;
            std::cout << res.a[0][0]() << '\n';
        }
    }
}
