template <class Z>
Z primitive_root() {
    Z i = 2;
    int k = __builtin_ctz(Z::mod() - 1);
    while (true) {
        if (Z::qpow(i, (Z::mod() - 1) / 2).value() != 1) {
            break;
        }
        i += 1;
    }
    return Z::qpow(i, (Z::mod() - 1) >> k);
}
