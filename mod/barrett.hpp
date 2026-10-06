#pragma once
#include <common.hpp>

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
