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
                Z e = Z::qpow(G, 1 << (__builtin_ctz(Z::mod() - 1) - k - 1));
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

    // Newton
    Poly prefix(int len) const {
        Poly f(*this);
        f.resize(len);
        return f;
    }
    Poly inv() const {
        Poly f{Z{1} / this->operator[](0)};
        for (int i = 1; i < size(); i *= 2)
            f = (f * 2 - f * f * prefix(i * 2)).prefix(i * 2);
        f.resize(size());
        return f;
    }
    friend Poly log(const Poly &h) {
        Poly f(h);
        for (int i = 1; i < (int)f.size(); ++i) f[i - 1] = f[i] * i;
        f[f.size() - 1] = 0, f *= h.inv(), f.resize(h.size());
        for (int i = (int)f.size() - 1; i > 0; --i) f[i] = f[i - 1] / i;
        f[0] = 0;
        return f;
    }
    friend Poly exp(const Poly &h) {
        int N = 1;
        while (N < (int)(h.size() + h.size() - 1)) N *= 2;
        Poly f(N), g(N), d(h);
        f[0] = 1, d.resize(N);
        for (int w = 2; w < N; w <<= 1) {
            f.resize(w), g.resize(w);
            std::copy(d.begin(), d.begin() + w, g.begin());
            f *= (g + 1 - log(f)), f.resize(w);
        }
        f.resize(h.size());
        return f;
    }

    // Multipoint evaluation
    Poly &operator/=(const Poly &rhs) {
        if (size() < rhs.size()) return resize(0), *this;
        int n = size() - rhs.size() + 1;
        Poly gr(rhs.rbegin(), rhs.rend());
        std::reverse(this->begin(), this->end());
        gr.resize(n), resize(n);
        *this *= gr.inv(), resize(n);
        std::reverse(this->begin(), this->end());
        return *this;
    }
    friend Poly operator/(const Poly &lhs, const Poly &rhs) {
        return Poly(lhs) /= rhs;
    }
    friend Poly operator%(const Poly &lhs, const Poly &rhs) {
        if (lhs.size() < rhs.size()) return lhs;
        return lhs - lhs / rhs * rhs;
    }
    void rtz() { // remove trailing zeros
        while (!this->empty() && this->back()() == 0) this->pop_back();
    }
    std::vector<Z> operator()(const std::vector<Z> &p) const {
        int N = 1;
        while (N < p.size()) N *= 2;
        std::vector<Poly> prod(N * 2, Poly{Z{1}});
        for (int i = 0; i < p.size(); i++) prod[N + i] = Poly{0 - p[i], Z{1}};
        for (int i = N - 1; i >= 1; --i)
            prod[i] = prod[i * 2] * prod[i * 2 + 1];
        std::vector<Poly> remd(N * 2, Poly{Z{0}});
        remd[1] = *this % prod[1];
        for (int i = 2; i < N * 2; i++) {
            remd[i] = remd[i / 2] % prod[i];
            remd[i].rtz();
        }
        std::vector<Z> res(p.size());
        for (int i = 0; i < p.size(); i++) res[i] = remd[N + i][0];
        return res;
    }
    static Poly interpolation(const std::vector<Z> &x,
                              const std::vector<Z> &y) {
        int N = 1;
        while (N < x.size()) N *= 2;
        std::vector<Poly> prod(N * 2, Poly{Z(1)});
        for (int i = 0; i < x.size(); i++) prod[N + i] = Poly{0 - x[i], Z{1}};
        for (int i = N - 1; i >= 1; i--)
            prod[i] = prod[i * 2] * prod[i * 2 + 1];
        Poly g_d = prod[1];
        for (int i = 1; i < g_d.size(); ++i) g_d[i - 1] = g_d[i] * i;
        g_d.pop_back();
        std::vector<Z> p = g_d(x);
        std::vector<Poly> f(N * 2, Poly{Z(0)});
        for (int i = 0; i < x.size(); i++) f[N + i] = Poly{y[i] / p[i]};
        for (int i = N - 1; i >= 1; i--)
            f[i] = (f[i * 2] * prod[i * 2 + 1]) + (f[i * 2 + 1] * prod[i * 2]);
        return f[1].prefix(N);
    }
};

template <class Z, int G>
std::vector<int> Poly<Z, G>::rev;

template <class Z, int G>
std::vector<Z> Poly<Z, G>::w{0, 1};
