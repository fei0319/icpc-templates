template <typename Mono, typename F>
void monoid_product(const std::vector<Mono> &vec,
                    const std::vector<std::pair<int, int>> &query, F f) {
    const int n = vec.size();
    std::vector<std::vector<int>> buk(n);
    for (int id = 0; id < query.size(); ++id) {
        auto [l, r] = query[id];
        if (l == r) {
            continue;
        }
        int k = topbit(l ^ r);
        buk[r >> k << k].push_back(id);
    }

    std::vector<Mono> dp(n);
    for (int mid = 1; mid < n; ++mid) {
        int min = mid, max = mid;
        for (int id : buk[mid]) {
            auto [l, r] = query[id];
            min = std::min(min, l);
            max = std::max(max, r);
        }
        dp[mid - 1] = vec[mid - 1];
        for (int i = mid - 2; i >= min; --i) {
            dp[i] = vec[i] * dp[i + 1];
        }
        dp[mid] = vec[mid];
        for (int i = mid + 1; i <= max; ++i) {
            dp[i] = dp[i - 1] * vec[i];
        }
        for (int id : buk[mid]) {
            auto [l, r] = query[id];
            f(dp[l], dp[r], id);
        }
    }
}
