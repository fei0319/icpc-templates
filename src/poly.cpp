template <class Z, int G = 31>
class Poly : public std::vector<Z> {
    static std::vector<int> rev;
    static std::vector<Z> w;
    static void dft(auto f, int n) {
        if (rev.size() != n) {
            rev.resize(n);
            for (int i = 0; i < n; i++)
                rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
        }
        if (w.size() < n) {
            int k = __builtin_ctz(w.size());
            w.resize(n);
            while ((1 << k) < n) {
                auto e = Z::qpow(G, 1 << (__builtin_ctz(Z::mod() - 1) - k - 1));
                for (int i = 1 << (k - 1); i < (1 << k); ++i)
                    w[i * 2] = w[i], w[i * 2 + 1] = w[i] * e;
                ++k;
            }
        }
        for (int i = 0; i < n; ++i)
            if (i < rev[i]) std::swap(f[i], f[rev[i]]);
        for (int i = 1; i < n; i *= 2)
            for (int j = 0; j < n; j += i * 2) {
                auto g = f + j, h = f + j + i;
                for (int k = 0; k < i; ++k) {
                    const Z p = g[k], q = h[k] * w[i + k];
                    g[k] = p + q, h[k] = p - q;
                }
            }
    }
    static void idft(auto f, int n) {
        std::reverse(f + 1, f + n), dft(f, n);
        const Z inv = (1 - Z::mod()) / n;
        for (int i = 0; i < n; ++i) f[i] *= inv;
    }

public:
    using std::vector<Z>::vector;
    using std::vector<Z>::size;
    using std::vector<Z>::resize;
    using std::vector<Z>::empty;

    // Convolution
    Poly &operator*=(const Poly &rhs) {
        int N = 1, n = size() + rhs.size() - 1;
        while (N < n) N *= 2;
        Poly &f(*this), g(N);
        f.resize(N), std::copy(rhs.begin(), rhs.end(), g.begin());
        dft(f.begin(), N), dft(g.begin(), N);
        for (int i = 0; i < N; ++i) f[i] *= g[i];
        idft(f.begin(), N), f.resize(n);
        return f;
    }

    // Linear operations
    Poly &operator+=(const Poly &rhs) {
        if (rhs.size() > size()) resize(rhs.size());
        for (int i = 0; i < rhs.size(); ++i) this->operator[](i) += rhs[i];
        return *this;
    }
    Poly &operator+=(const Z &rhs) {
        if (size() == 0) resize(1);
        this->operator[](0) += rhs;
        return *this;
    }
    Poly &operator-=(const Poly &rhs) {
        if (rhs.size() > size()) resize(rhs.size());
        for (int i = 0; i < rhs.size(); ++i) this->operator[](i) -= rhs[i];
        return *this;
    }
    Poly &operator-=(const Z &rhs) {
        if (size() == 0) resize(1);
        this->operator[](0) -= rhs;
        return *this;
    }
    Poly &operator*=(const Z &rhs) {
        for (Z &i : *this) i *= rhs;
        return *this;
    }

    // DeCompound
    friend Poly operator+(const Poly &lhs, const auto &rhs) {
        return Poly(lhs) += rhs;
    }
    friend Poly operator-(const Poly &lhs, const auto &rhs) {
        return Poly(lhs) -= rhs;
    }
    friend Poly operator*(const Poly &lhs, const auto &rhs) {
        return Poly(lhs) *= rhs;
    }

    Poly prefix(int len) const {
        Poly f(*this);
        f.resize(len);
        return f;
    }
    Poly inv() const {
        Poly f{Z(1) / this->operator[](0)};
        for (int i = 1; i < size(); i *= 2)
            f = (f * 2 - f * f * prefix(i * 2)).prefix(i * 2);
        f.resize(size());
        return f;
    }
    friend Poly log(const Poly &h) {
        Poly f(h);
        for (int i = 1; i < (int)f.size(); ++i) f[i - 1] = f[i] * i;
        f[f.size() - 1] = 0, f *= h.inv(), f.resize(h.size());
        for (int i = (int)f.size() - 1; i > 0; --i)
            f[i] = f[i - 1] * Z::qpow(i, Z::mod() - 2);
        f[0] = 0;
        return f;
    }
    friend Poly exp(const Poly &h) {
        int N = 1;
        while (N < (int)(h.size() + h.size() - 1)) N <<= 1;
        Poly f(N), g(N), d(h);
        f[0] = 1, d.resize(N);
        for (int w = 2; w < N; w <<= 1) {
            f.resize(w), g.resize(w);
            for (int i = 0; i < w; ++i) g[i] = d[i];
            f *= (g + 1 - log(f)), f.resize(w);
        }
        f.resize(h.size());
        return f;
    }
};

template <class Z, int G>
std::vector<int> Poly<Z, G>::rev;

template <class Z, int G>
std::vector<Z> Poly<Z, G>::w{0, 1};
