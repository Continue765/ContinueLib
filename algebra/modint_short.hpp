template <u32 P>
struct Mint {
    u32 v;
    Mint(i64 v_ = 0) : v((v_ %= P) < 0 ? v_ + P : v_) {}
    Mint inv() const {
        i64 x, y;
        exgcd(v, P, x, y);
        return x;
    }
    Mint& operator+=(Mint rhs) & {
        v += rhs.v;
        if (v >= P) v -= P;
        return *this;
    }
    Mint& operator-=(Mint rhs) & {
        v -= rhs.v;
        if (v >= P) v += P;
        return *this;
    }
    Mint& operator*=(Mint rhs) & {
        v = u64(v) * rhs.v % P;
        return *this;
    }
    Mint& operator/=(Mint rhs) & {
        return *this *= rhs.inv();
    }
    friend Mint operator-(Mint rhs) { return rhs.v ? Mint(P - rhs.v) : rhs; }
    friend Mint operator+(Mint lhs, Mint rhs) { return lhs += rhs; }
    friend Mint operator-(Mint lhs, Mint rhs) { return lhs -= rhs; }
    friend Mint operator*(Mint lhs, Mint rhs) { return lhs *= rhs; }
    friend Mint operator/(Mint lhs, Mint rhs) { return lhs /= rhs; }
    friend bool operator==(Mint lhs, Mint rhs) { return lhs.v == rhs.v; }
    friend bool operator!=(Mint lhs, Mint rhs) { return lhs.v != rhs.v; }
    friend istream& operator>>(istream& is, Mint& v) { i64 x; is >> x; v = x; return is; }
    friend ostream& operator<<(ostream& os, const Mint& v) { return os << v.v; }
};

constexpr u32 P = 998244353;
using Fp = Mint<P>;