#pragma once
#include <common.hpp>
#include <linear_algebra/matrix.hpp>
#include <linear_algebra/gauss.hpp>

template <typename T>
int matrixRank(Matrix<T> a) {
    auto [pivot, prod] = gauss(a);
    return pivot.size();
}