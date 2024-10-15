i64 mul(i64 a, i64 b, i64 m) {
    return (i128)a * b % m;
}

i64 qpow(i64 a, i64 b, i64 m) {
    i64 res = 1 % m;
    while (b) {
        if (b & 1) {
            res = mul(res, a, m);
        }
        a = mul(a, a, m), b >>= 1;
    }
    return res;
}

bool isprime(i64 n) {
    if (n < 2) {
        return false;
    }
    static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int s = __builtin_ctzll(n - 1);
    i64 d = (n - 1) >> s;
    for (auto a : A) {
        if (a == n) {
            return true;
        }
        i64 x = qpow(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool ok = false;
        for (int i = 0; i < s - 1; ++i) {
            x = mul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            return false;
        }
    }
    return true;
}
