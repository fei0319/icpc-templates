template <typename T>
int solve_linear_equations(std::vector<std::vector<T>> &a, auto abs,
                           auto zero) {
    const int n = a.size(), m = a[0].size() - 1;
    int rk = 0;
    for (int i = 0; i < m && rk < n; ++i) {
        int p = rk;
        for (int j = p + 1; j < n; ++j)
            if (abs(a[p][i]) < abs(a[j][i])) p = j;
        std::swap(a[p], a[rk]);
        if (zero(a[rk][i])) continue;

        T f = 1 / a[rk][i];
        for (int k = i; k <= m; ++k)
            a[rk][k] *= f;
        for (int j = 0; j < n; ++j) {
            if (j == rk || zero(a[j][i])) continue;
            T f = a[j][i];
            for (int k = i; k <= m; ++k)
                a[j][k] -= f * a[rk][k];
        }
        ++rk;
    }
    for (int j = rk; j < n; ++j)
        if (!zero(a[j][m])) return -1;

    return rk;
};
