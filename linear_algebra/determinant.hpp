#pragma once
#include <linear_algebra/matrix.hpp>
#include <linear_algebra/gauss.hpp>

template <typename T>
T determinant(Matrix<T> a) {
    assert(a.n == a.m);
    auto [pivot, prod] = gauss(a);
    if (pivot.size() < a.n) {
        return T{0};
    }
    return prod;
}