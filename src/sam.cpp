template <int SIGMA>
struct SuffixAutomaton {
    std::vector<int> len, link;
    std::vector<std::array<int, SIGMA>> next;
    int tot;
    explicit SuffixAutomaton(int size)
        : len(size), link(size), next(size), tot(1) {}
    int extend(int p, int c) {
        int cur = ++tot;
        len[cur] = len[p] + 1;
        for (; p && !next[p][c]; p = link[p])
            next[p][c] = cur;
        int q = next[p][c];
        if (!p) {
            link[cur] = 1;
        } else if (len[q] == len[p] + 1) {
            link[cur] = q;
        } else {
            int r = ++tot;
            len[r] = len[p] + 1;
            link[r] = link[q];
            next[r] = next[q];
            link[q] = link[cur] = r;
            for (; next[p][c] == q; p = link[p])
                next[p][c] = r;
        }
        return cur;
    }
};
