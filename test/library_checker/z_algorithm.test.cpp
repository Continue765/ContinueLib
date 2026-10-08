#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "string/z_algo.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    auto z = Z(s);
    for (int i = 0; i < (int)s.size(); ++i) std::cout << z[i] << (i + 1 == (int)s.size() ? '\n' : ' ');
}
