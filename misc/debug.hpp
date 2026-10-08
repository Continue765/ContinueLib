#pragma once
#include <bits/stdc++.h>
using namespace std;

#define dbg(...) { cerr << "[" << __LINE__ << "] "; pr(__VA_ARGS__); cerr << '\n'; }

void pr(bool b) { cerr << (b ? "T" : "F"); }
void pr(char c) { cerr << "'" << c << "'"; }
void pr(string s) { cerr << '"' << s << '"'; }
void pr(const char* s) { cerr << '"' << s << '"'; }

template <class T>
void pr(T&& x) {
    using U = remove_reference_t<T>;
    if constexpr (requires { begin(x); }) {
        bool br = requires { typename U::key_type; };
        cerr << (br ? '{' : '[');
        bool f = 0;
        for (auto&& e : x) {
            if (exchange(f, 1)) cerr << ",";
            if constexpr (requires { typename U::mapped_type; }) { pr(e.first); cerr << ":"; pr(e.second); }
            else pr(e);
        }
        cerr << (br ? '}' : ']');
    } else if constexpr (requires { x.first; x.second; }) {
        cerr << '('; pr(x.first); cerr << ","; pr(x.second); cerr << ')';
    } else if constexpr (requires { get<0>(x); }) {
        cerr << '(';
        bool f = 0;
        apply([&](auto... e) { ((cerr << (exchange(f, 1) ? "," : ""), pr(e)), ...); }, x);
        cerr << ')';
    } else if constexpr (requires { x.top(); }) {
        vector<typename U::value_type> v;
        while (!x.empty()) v.push_back(x.top()), x.pop();
        pr(v);
    } else if constexpr (requires { x.front(); }) {
        vector<typename U::value_type> v;
        while (!x.empty()) v.push_back(x.front()), x.pop();
        pr(v);
    } else {
        cerr << x;
    }
}

template <class A, class... B> requires (sizeof...(B) > 0)
void pr(A a, B... b) { pr(a); ((cerr << "  ", pr(b)), ...); }
