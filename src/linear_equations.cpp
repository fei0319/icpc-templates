template <typename T>
int solve_linear_equations(std::vector<std::vector<T>> &a, auto abs,
                           auto zero) {
    const int n = a.size(), m = a[0].size() - 1;
    int rk = 0;
    for (int now = 0; now < m; ++now) {
        int p = rk;
        for (int j = p + 1; j < n; ++j)
            if (abs(a[p][now]) < abs(a[j][now])) p = j;
        std::swap(a[p], a[rk]);
        if (zero(a[rk][now])) continue;
        T f = 1 / a[rk][now];
        for (int i = now; i <= m; ++i)
            a[rk][i] *= f;
        for (int i = 0; i < n; ++i) {
            if (i == rk || zero(a[i][now])) continue;
            T f = a[i][now];
            for (int j = now; j <= m; ++j)
                a[i][j] -= f * a[rk][j];
        }
        ++rk;
    }
    for (int i = rk; i < n; ++i)
        if (!zero(a[i][m])) return -1;

    return rk;
};
