template <>
u64 hash<i64>(const i64 &x) {
    return static_cast<u64>(x + M0) * M1;
}

template <typename K, typename V, int B = 20>
class HashMap {
    static constexpr int N = 1 << B;
    K *key{new K[N]};
    V *val{new V[N]};
    bool *vist{new bool[N]};

    int idx(const K &x) const {
        int i = hash(x) >> (64 - B);
        while (vist[i] && key[i] != x) {
            i = (i + 1) & (N - 1);
        }
        return i;
    }

public:
    ~HashMap() {
        delete[] key;
        delete[] val;
        delete[] vist;
    }
    V &operator[](const K &x) {
        int i = idx(x);
        if (!vist[i]) {
            vist[i] = true;
            key[i] = x;
            val[i] = V{};
        }
        return val[i];
    }
    void erase(const K &x) {
        vist[idx(x)] = false;
    }
    bool contains(const K &x) const {
        return vist[idx(x)];
    }
};
