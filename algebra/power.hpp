i64 power(i64 a, i64 b) {
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % P;
        }
        a = (a * a) % P;
        b >>= 1;
    }
    return res % P;
}
