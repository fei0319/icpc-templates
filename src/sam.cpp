template <int SIGMA>
struct SuffixAutomaton {
    struct Node {
        int len{};
        int link{};
        int next[SIGMA]{};
    };
    std::vector<Node> t;
    int tot;
    explicit SuffixAutomaton(int size) : t(size), tot(1) {
        std::fill(t[0].next, t[0].next + SIGMA, 1);
        t[0].len = -1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1)
                return q;
            int r = ++tot;
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            std::copy(t[q].next, t[q].next + SIGMA, t[r].next);
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = ++tot;
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
};
