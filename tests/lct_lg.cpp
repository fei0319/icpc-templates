#include <bits/stdc++.h>

// https://www.luogu.com.cn/problem/P3690

#include "../data_structure/link_cut_tree.hpp"

struct Int {
    int v;
    Int operator*(const Int &rhs) { return Int{v ^ rhs.v}; }
    void flip() const {}
};

LinkCutTree<Int, static_cast<int>(1e5 + 1)> t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        t.set(i, Int{x});
    }

    while (m--) {
        int op, x, y;
        std::cin >> op >> x >> y;
        if (op == 0) {
            std::cout << t.query(x, y).v << '\n';
        } else if (op == 1) {
            if (t.find(x) != t.find(y)) t.link(x, y);
        } else if (op == 2) {
            if (t.find(x) == t.find(y)) t.cut(x, y);
        } else {
            t.set(x, Int{y});
        }
    }
}
