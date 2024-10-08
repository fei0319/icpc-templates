template <int m>
class ModInt {
    int raw;
    using mint = ModInt;
    using i64 = int64_t;

public:
    ModInt() : raw(0) {}
    ModInt(const auto &v) : raw((v % m + m) % m) {}
    int value() const {
        return raw;
    }

    mint &operator+=(const mint &rhs) {
        raw += rhs.raw;
        if (raw >= m) {
            raw -= m;
        }
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        raw -= rhs.raw;
        if (raw < 0) {
            raw += m;
        }
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        raw = (i64)raw * rhs.raw % m;
        return *this;
    }
    mint &operator/=(const mint &rhs) {
        return *this *= qpow(rhs, m - 2);
    }

    friend mint operator+(const mint &lhs, const mint &rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint &lhs, const mint &rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint &lhs, const mint &rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint &lhs, const mint &rhs) {
        return mint(lhs) /= rhs;
    }

    static constexpr int mod() {
        return m;
    }

    static mint qpow(mint a, i64 b) {
        mint res = 1;
        while (b) {
            if (b & 1) {
                res *= a;
            }
            a *= a, b >>= 1;
        }
        return res;
    }
};
