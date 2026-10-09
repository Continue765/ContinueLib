#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include <common.hpp>
#include "linear_algebra/gauss.hpp"

struct Fp {
    static constexpr int mod = 101;
    int v;
    Fp(long long x = 0) : v((x % mod + mod) % mod) {}
    Fp inverse() const {
        assert(v != 0);
        int a = v, b = mod, x = 1, y = 0;
        while (b) {
            int q = a / b;
            tie(a, b) = pair{b, a - q * b};
            tie(x, y) = pair{y, x - q * y};
        }
        return x;
    }
    Fp& operator+=(Fp b) { v = (v + b.v) % mod; return *this; }
    Fp& operator-=(Fp b) { v = (v - b.v + mod) % mod; return *this; }
    Fp& operator*=(Fp b) { v = v * b.v % mod; return *this; }
    Fp& operator/=(Fp b) { return *this *= b.inverse(); }
    Fp operator-() const { return Fp(-v); }
    friend Fp operator+(Fp a, Fp b) { return a += b; }
    friend Fp operator-(Fp a, Fp b) { return a -= b; }
    friend Fp operator*(Fp a, Fp b) { return a *= b; }
    friend Fp operator/(Fp a, Fp b) { return a /= b; }
    friend bool operator==(Fp a, Fp b) { return a.v == b.v; }
};

int main() {
    Matrix<Fp> a(3, 3);
    a[0] = {1, 2, 3};
    a[1] = {0, 1, 4};
    a[2] = {5, 6, 0};
    assert(determinant(a) == Fp(1));
    assert(matrixRank(a) == 3);
    auto [det, inv] = matrixInv(a);
    assert(det == Fp(1));
    Matrix<Fp> id = Matrix<Fp>::identity(3);
    auto left = a * inv;
    auto right = inv * a;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
        assert(left[i][j] == id[i][j]);
        assert(right[i][j] == id[i][j]);
    }

    Matrix<Fp> b(2, 3);
    b[0] = {1, 2, 3};
    b[1] = {2, 4, 6};
    assert(determinant(Matrix<Fp>(0, 0)) == Fp(1));
    assert(matrixRank(b) == 1);
    Matrix<Fp> singular(2, 2);
    singular[0] = {1, 2};
    singular[1] = {2, 4};
    auto [badDet, badInv] = matrixInv(singular);
    assert(badDet == Fp(0) && badInv.n == 0 && badInv.m == 0);

    Matrix<Fp> c(2, 3);
    c[0] = {1, 1, 0};
    c[1] = {0, 1, 1};
    vector<Fp> rhs{Fp(7), Fp(11)};
    auto solutions = solveLinear(c, rhs);
    assert(solutions.size() == 2);
    for (const auto& x : solutions) {
        assert(c[0][0] * x[0] + c[0][1] * x[1] + c[0][2] * x[2] == (x == solutions[0] ? rhs[0] : Fp(0)));
    }
    auto verifySolution = [&](const vector<Fp>& x) {
        for (int i = 0; i < c.n; ++i) {
            Fp sum = 0;
            for (int j = 0; j < c.m; ++j) sum += c[i][j] * x[j];
            assert(sum == rhs[i]);
        }
    };
    verifySolution(solutions[0]);
    vector<Fp> translated(3);
    for (int j = 0; j < 3; ++j) translated[j] = solutions[0][j] + solutions[1][j];
    verifySolution(translated);
    assert(solveLinear(singular, vector<Fp>{Fp(7), Fp(12)}).empty());

    Matrix<Fp> t(2, 3);
    t[0] = {1, 2, 3};
    t[1] = {4, 5, 6};
    auto tt = transpose(t);
    assert(tt.n == 3 && tt.m == 2 && tt[2][1] == Fp(6));
    assert(augment(t, Matrix<Fp>::identity(2)).m == 5);
    assert(augment(t, vector<Fp>{7, 8}).m == 4);

    Matrix<Fp> fib(2);
    fib[0] = {1, 1};
    fib[1] = {1, 0};
    auto fib10 = power(fib, 10);
    assert(fib10[0][0] == Fp(89) && fib10[0][1] == Fp(55));
    fib *= Matrix<Fp>::identity(2);
    assert(fib[1][0] == Fp(1));

    int x, y;
    if (cin >> x >> y) cout << x + y << '\n';
}
