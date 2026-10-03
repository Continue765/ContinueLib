static mt19937_64 rng(static_cast<u32>(chrono::steady_clock::now().time_since_epoch().count()));

i64 rho(i64 n, i64 c) {
    auto f = [&](i64 x) {
        return static_cast<i64>((static_cast<i128>(x) * x + c) % n);
    };
    i64 x = 1, y = 2, z = 1, q = 1;
    i64 g = 1;
    constexpr i64 m = 127;
    for (i64 r = 1; g == 1; r <<= 1) {
        x = y;
        for (i64 i = 0; i < r; i++) {
            y = f(y);
        }
        for (i64 k = 0; k < r && g == 1; k += m) {
            z = y;
            for (i64 i = 0; i < min(m, r - k); i++) {
                y = f(y);
                q = mul(q, abs(x - y), n);
            }
            g = gcd(q, n);
        }
    }
    if (g == n) {
        do {
            z = f(z);
            g = gcd(abs(x - z), n);
        } while (g == 1);
    }
    return g;
}

i64 primeFactor(i64 n) {
    assert(n >= 2);
    if (n % 2 == 0) {
        return 2;
    }
    while (!isPrime(n)) {
        uniform_int_distribution<i64> pick(1, n - 1);
        n = rho(n, pick(rng));
    }
    return n;
}

vector<pair<i64, int>> factorize(i64 n) {
    vector<pair<i64, int>> pf;
    for (int p = 2; p < 100; p++) {
        if (p * p > n) {
            break;
        }
        if (n % p == 0) {
            int e = 0;
            do {
                n /= p;
                e++;
            } while (n % p == 0);
            pf.emplace_back(p, e);
        }
    }
    while (n > 1) {
        i64 p = primeFactor(n);
        int e = 0;
        do {
            n /= p;
            e++;
        } while (n % p == 0);
        pf.emplace_back(p, e);
    }
    sort(pf.begin(), pf.end());
    return pf;
}
