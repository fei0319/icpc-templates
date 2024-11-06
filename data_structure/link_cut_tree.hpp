template <typename Mono, int N>
class LinkCutTree {
#define ls son[x][0]
#define rs son[x][1]
    int son[N][2], fa[N];
    Mono dp[N], val[N];
    bool tag[N];
    void push_up(int x) {
        dp[x] = val[x];
        if (ls) dp[x] = dp[ls] * dp[x];
        if (rs) dp[x] = dp[x] * dp[rs];
    }
    void push_down(int x) {
        if (tag[x]) {
            tag[x] = 0;
            std::swap(ls, rs);
            tag[ls] ^= 1, dp[ls].flip();
            tag[rs] ^= 1, dp[rs].flip();
        }
    }
    int get(int x) { return son[fa[x]][1] == x; }
    bool isroot(int x) { return son[fa[x]][0] != x && son[fa[x]][1] != x; }
    void rotate(int x) {
        int f = fa[x], ff = fa[f], t = get(x);
        if (!isroot(f)) son[ff][get(f)] = x;
        son[f][t] = son[x][t ^ 1], fa[son[x][t ^ 1]] = f, push_up(f);
        son[x][t ^ 1] = f, fa[f] = x, fa[x] = ff, push_up(x);
    }
    void update(int x) {
        if (!isroot(x)) update(fa[x]);
        push_down(x);
    }
    void splay(int x) {
        update(x);
        for (; !isroot(x); rotate(x))
            if (!isroot(fa[x])) rotate(get(x) == get(fa[x]) ? fa[x] : x);
    }
    int access(int x) {
        int p = 0;
        for (; x; p = x, x = fa[x]) splay(x), rs = p, push_up(x);
        return p;
    }
    int make_root(int x) { return x = access(x), tag[x] ^= 1, dp[x].flip(), x; }

public:
    void link(int x, int y) { fa[make_root(x)] = y; }
    void cut(int x, int y) {
        make_root(x), access(y), splay(x);
        if (son[x][1] == y && !son[y][0]) son[x][1] = fa[y] = 0, push_up(x);
    }
    void set(int x, const Mono &v) { splay(x), val[x] = v, push_up(x); }
    Mono query(int u, int v) { return make_root(u), dp[access(v)]; }
    int find(int x) {
        x = access(x);
        for (; ls; x = ls, push_down(x));
        splay(x);
        return x;
    }
#undef ls
#undef rs
};
