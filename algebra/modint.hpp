#pragma once
#include <common.hpp>

template <std::signed_integral T>
constexpr std::pair<T, T> exgcd(T a, T m) {
    assert(m > 0);
    a %= m;
    if (a < 0) {
        a += m;
    }

    T u = 0, v = 1;
    while (a != 0) {
        T q = m / a;
        m -= q * a, std::swap(a, m);
        u -= q * v, std::swap(u, v);
    }
    return {m, u};
}

template <typename T, std::integral U>
constexpr T power(T a, U b) {
    assert(b >= 0);
    T res{1};
    while (b) {
        if (b & 1) {
            res *= a;
        }
        b >>= 1;
        a *= a;
    }
    return res;
}

class Barrett {
public:
    constexpr Barrett(uint32_t Mod) : mod_(Mod), mu_(static_cast<uint64_t>(-1) / Mod + 1) {}

    constexpr uint32_t mod() const {
        return mod_;
    }

    constexpr uint32_t multiply(uint32_t a, uint32_t b) const {
        uint64_t z = static_cast<uint64_t>(a) * b;
        uint64_t q = static_cast<uint64_t>((static_cast<__uint128_t>(z) * mu_) >> 64);
        uint64_t y = q * mod_;
        return static_cast<uint32_t>(z - y + (z < y ? mod_ : 0));
    }

private:
    uint32_t mod_;
    uint64_t mu_;
};

template <std::unsigned_integral U, U Mod>
struct StaticMod {
    static constexpr U mod() {
        return Mod;
    }
    static constexpr U multiply(U a, U b) {
        if constexpr (sizeof(U) <= 4) {
            return static_cast<U>(static_cast<uint64_t>(a) * static_cast<uint64_t>(b) % mod());
        } else {
            return static_cast<U>(static_cast<__uint128_t>(a) * static_cast<__uint128_t>(b) % mod());
        }
    }
};

template <uint32_t Mod>
using StaticMod32 = StaticMod<uint32_t, Mod>;
template <uint64_t Mod>
using StaticMod64 = StaticMod<uint64_t, Mod>;

template <uint32_t Id>
class DynamicMod {
public:
    static uint32_t mod() {
        return barrett_.mod();
    }
    static uint32_t multiply(uint32_t a, uint32_t b) {
        return barrett_.multiply(a, b);
    }
    static void setMod(uint32_t m) {
        barrett_ = Barrett(m);
    }

private:
    static Barrett barrett_;
};

template <uint32_t Id>
Barrett DynamicMod<Id>::barrett_ = 998244353;

template <typename Policy>
class ModInt {
public:
    using Type = decltype(Policy::mod());

    static constexpr Type mod() {
        return Policy::mod();
    }

    template <std::unsigned_integral T>
    static constexpr Type normalize(const T& x) {
        return (x % mod());
    }
    template <std::signed_integral T>
    static constexpr Type normalize(const T& x) {
        using S = std::make_signed_t<Type>;
        S v = x % static_cast<S>(mod());
        if (v < 0) {
            v += mod();
        }
        return static_cast<Type>(v);
    }

    constexpr ModInt() : value_(0) {}
    template <std::integral T>
    constexpr ModInt(const T& x) : value_(normalize(x)) {}

    constexpr Type value() const {
        return value_;
    }

    template <std::integral T>
    constexpr explicit operator T() const {
        return static_cast<T>(value());
    }

    constexpr ModInt inverse() const {
        assert(value_ != 0);
        auto [g, x] = exgcd<std::make_signed_t<Type>>(value_, mod());
        assert(g == 1);
        return normalize(x);
    }

    constexpr ModInt operator-() const {
        return normalize(value_ ? mod() - value_ : 0);
    }
    constexpr ModInt operator+() const {
        return *this;
    }

    constexpr ModInt& operator++() {
        value_++;
        if (value_ == mod()) {
            value_ = 0;
        }
        return *this;
    }
    constexpr ModInt& operator--() {
        if (value_ == 0) {
            value_ = mod();
        }
        value_--;
        return *this;
    }
    constexpr ModInt operator++(int) {
        ModInt result = *this;
        ++*this;
        return result;
    }
    constexpr ModInt operator--(int) {
        ModInt result = *this;
        --*this;
        return result;
    }

    constexpr ModInt& operator+=(const ModInt& other) & {
        value_ += other.value();
        if (value_ >= mod()) {
            value_ -= mod();
        }
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt& other) & {
        value_ -= other.value();
        if (value_ >= mod()) {
            value_ += mod();
        }
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt& other) & {
        value_ = Policy::multiply(value_, other.value());
        return *this;
    }
    constexpr ModInt& operator/=(const ModInt& other) & {
        return *this *= other.inverse();
    }

    constexpr friend ModInt operator+(ModInt lhs, const ModInt& rhs) {
        return lhs += rhs;
    }
    constexpr friend ModInt operator-(ModInt lhs, const ModInt& rhs) {
        return lhs -= rhs;
    }
    constexpr friend ModInt operator*(ModInt lhs, const ModInt& rhs) {
        return lhs *= rhs;
    }
    constexpr friend ModInt operator/(ModInt lhs, const ModInt& rhs) {
        return lhs /= rhs;
    }

    constexpr friend bool operator==(const ModInt& lhs, const ModInt& rhs) {
        return lhs.value() == rhs.value();
    }
    constexpr friend std::strong_ordering operator<=>(const ModInt& lhs, const ModInt& rhs) {
        return lhs.value() <=> rhs.value();
    }

    template <typename Stream>
    friend Stream& operator>>(Stream& stream, ModInt& number) {
        std::common_type_t<Type, int64_t> x;
        stream >> x;
        number.value_ = normalize(x);
        return stream;
    }

    template <typename Stream>
    friend Stream& operator<<(Stream& stream, const ModInt& number) {
        return stream << number.value();
    }

private:
    Type value_;
};

using ModInt998244353 = ModInt<StaticMod32<998244353>>;
using ModInt100000007 = ModInt<StaticMod32<100000007>>;