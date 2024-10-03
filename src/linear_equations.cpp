template <typename T>
int solve_linear_equations(std::vector<std::vector<T>> &a, auto abs,
                           auto is_zero) {
    const int n = a.size();
    for (int i = 0; i < n; ++i) {
        int p = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(a[j][i]) > abs(a[p][i])) {
                p = j;
            }
        }
        if (i != p) {
            std::swap(a[i], a[p]);
        }
        if (is_zero(a[i][i])) {
            return -1;
        }
        T f = 1 / a[i][i];
        for (int k = i; k <= n; ++k) {
            a[i][k] *= f;
        }
        for (int j = i + 1; j < n; ++j) {
            T f = a[j][i];
            for (int k = i; k <= n; ++k) {
                a[j][k] -= a[i][k] * f;
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            a[j][n] -= a[j][i] * a[i][n];
            a[j][i] = 0;
        }
    }
    return 0;
}
