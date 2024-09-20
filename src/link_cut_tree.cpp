template <typename Mono, int TREE_N>
class LinkCutTree {
#define ls son[x][0]
#define rs son[x][1]
    int son[TREE_N][2], fa[TREE_N];
    Mono dp[TREE_N], val[TREE_N];
    bool tag[TREE_N];
    void push_up(int x) {
        dp[x] = dp[ls] * val[x] * dp[rs];
    }
    void push_down(int x) {
        if (tag[x]) {
            tag[ls] ^= 1;
            tag[rs] ^= 1;
            tag[x] = 0;
            std::swap(ls, rs);
        }
    }
    int get(int x) {
        return son[fa[x]][1] == x;
    }
    bool isroot(int x) {
        return son[fa[x]][0] != x && son[fa[x]][1] != x;
    }
    void rotate(int x) {
        int f = fa[x], ff = fa[f], t = get(x);
        fa[x] = ff;
        if (!isroot(f))
            son[ff][get(f)] = x;

        son[f][t] = son[x][t ^ 1], fa[son[x][t ^ 1]] = f;
        push_up(f);

        son[x][t ^ 1] = f, fa[f] = x;
        push_up(x);
    }
    void update(int x) {
        if (!isroot(x))
            update(fa[x]);
        push_down(x);
    }
    void splay(int x) {
        update(x);
        while (!isroot(x)) {
            if (!isroot(fa[x]))
                rotate(get(x) == get(fa[x]) ? fa[x] : x);
            rotate(x);
        }
    }
    void access(int x) {
        for (int p = 0; x; p = x, x = fa[x])
            splay(x), rs = p, push_up(x);
    }
    void make_root(int x) {
        access(x), splay(x), tag[x] ^= 1;
    }

public:
    void link(int x, int y) {
        make_root(x), fa[x] = y;
    }
    void cut(int x, int y) {
        make_root(x), access(y), splay(x);
        if (son[x][1] == y && !son[y][0]) {
            son[x][1] = fa[y] = 0, push_up(x);
        }
    }
    void set(int x, const Mono &v) {
        val[x] = v;
        splay(x);
    }
    Mono query(int u, int v) {
        make_root(u), access(v), splay(v);
        return dp[v];
    }
    int find(int x) {
        access(x), splay(x);
        while (son[x][0]) {
            x = son[x][0];
            push_down(x);
        }
        splay(x);
        return x;
    }
#undef ls
#undef rs
};
