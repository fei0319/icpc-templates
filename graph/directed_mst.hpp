template <typename T, typename E>
std::pair<T, std::vector<int>> dmst(const std::vector<E> &edge, int n, int rt) {
    struct Node {
        E key;
        Node *l, *r;
        T delta;
        void prop() {
            key.w += delta;
            if (l) l->delta += delta;
            if (r) r->delta += delta;
            delta = 0;
        }
        E top() {
            prop();
            return key;
        }
    };
    std::function<Node *(Node *, Node *)> merge = [&](Node *a, Node *b) {
        if (!a || !b) return a ?: b;
        a->prop(), b->prop();
        if (a->key.w > b->key.w) std::swap(a, b);
        std::swap(a->l, (a->r = merge(b, a->r)));
        return a;
    };
    auto pop = [&](Node *&a) {
        a->prop(), a = merge(a->l, a->r);
    };
    T cost = {};
    std::vector<int> pv(n);
    RollbackDSU dsu(n);
    std::vector<Node *> heap(n);
    for (const auto &e : edge) heap[e.v] = merge(heap[e.v], new Node{e});
    std::vector<int> seen(n, -1), path(n);
    seen[rt] = rt;
    std::vector<E> Q(n), in(n, {-1, -1}), comp;
    std::deque<std::tuple<int, int, std::vector<E>>> cycs;
    for (int s = 0; s < n; ++s) {
        int u = s, qi = 0, w;
        while (seen[u] < 0) {
            if (!heap[u]) return {0, {}};
            E e = heap[u]->top();
            heap[u]->delta -= e.w, pop(heap[u]);
            Q[qi] = e, path[qi++] = u, seen[u] = s;
            cost += e.w, u = dsu.find(e.u);
            if (seen[u] == s) {
                Node *cyc = 0;
                int end = qi, time = dsu.time();
                do cyc = merge(cyc, heap[w = path[--qi]]);
                while (dsu.merge(u, w));
                u = dsu.find(u), heap[u] = cyc, seen[u] = -1;
                cycs.push_front({u, time, {&Q[qi], &Q[end]}});
            }
        }
        for (int i = 0; i < qi; ++i) in[dsu.find(Q[i].v)] = Q[i];
    }
    for (auto &[u, t, comp] : cycs) {
        dsu.rollback(t);
        E ine = in[u];
        for (auto &e : comp) in[dsu.find(e.v)] = e;
        in[dsu.find(ine.v)] = ine;
    }
    for (int i = 0; i < n; ++i) pv[i] = in[i].u;
    return {cost, pv};
}
