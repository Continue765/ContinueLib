#pragma once
#include <random/base.hpp>

// f 越大越好，g(cur, t) 返回新状态，可用温度 t 控制扰动。
template <typename T, typename F, typename G>
T simulatedAnnealing(T cur, F&& f, G&& g, double t0, double t1, double sec) {
    assert(t0 > t1 && t1 > 0 && sec > 0);
    auto beg = chrono::steady_clock::now();
    T ans = cur;
    auto val = f(cur), res = val;
    while (true) {
        double p = chrono::duration<double>(chrono::steady_clock::now() - beg).count() / sec;
        if (p >= 1) {
            break;
        }
        double t = exp(lerp(log(t0), log(t1), p));
        T nxt = g(cur, t);
        auto v = f(nxt);
        double d = double(v) - double(val);
        if (d >= 0 || randReal(0, 1) < exp(d / t)) {
            cur = move(nxt);
            val = v;
        }
        if (val > res) {
            ans = cur;
            res = val;
        }
    }
    return ans;
}
