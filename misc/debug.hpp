#pragma once
#include <common.hpp>

#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <string>
#include <utility>
#include <tuple>
#include <algorithm>

#define dbg(...) \
    do { \
        std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "; \
        dbg::print(__VA_ARGS__); \
        std::cerr << std::endl; \
    } while(0)

namespace dbg {

// 基本类型打印
template<typename T>
void print(const T& value) {
    std::cerr << value;
}

// 字符特殊处理
inline void print(char c) {
    if (c >= 32 && c <= 126)
        std::cerr << "'" << c << "'";
    else
        std::cerr << "'\\x" << std::hex << (int)c << "'";
}

// 字符串
inline void print(const std::string& s) {
    std::cerr << "\"" << s << "\"";
}
inline void print(const char* s) {
    std::cerr << "\"" << s << "\"";
}

// 多重参数
template<typename First, typename... Rest>
void print(const First& first, const Rest&... rest) {
    print(first);
    if (sizeof...(rest) > 0) {
        std::cerr << "  ";
        print(rest...);
    }
}

// vector
template<typename T>
void print(const std::vector<T>& v) {
    std::cerr << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cerr << ", ";
        print(v[i]);
    }
    std::cerr << "]";
}

// map
template<typename K, typename V>
void print(const std::map<K, V>& m) {
    std::cerr << "{";
    size_t i = 0;
    for (const auto& p : m) {
        if (i++ > 0) std::cerr << ", ";
        print(p.first);
        std::cerr << ": ";
        print(p.second);
    }
    std::cerr << "}";
}

// pair
template<typename T1, typename T2>
void print(const std::pair<T1, T2>& p) {
    std::cerr << "(";
    print(p.first);
    std::cerr << ", ";
    print(p.second);
    std::cerr << ")";
}

// deque
template<typename T>
void print(const std::deque<T>& dq) {
    std::cerr << "[";
    for (size_t i = 0; i < dq.size(); ++i) {
        if (i > 0) std::cerr << ", ";
        print(dq[i]);
    }
    std::cerr << "]";
}

// set
template<typename T>
void print(const std::set<T>& s) {
    std::cerr << "{";
    size_t i = 0;
    for (const auto& x : s) {
        if (i++ > 0) std::cerr << ", ";
        print(x);
    }
    std::cerr << "}";
}

// multiset
template<typename T>
void print(const std::multiset<T>& ms) {
    std::cerr << "{";
    size_t i = 0;
    for (const auto& x : ms) {
        if (i++ > 0) std::cerr << ", ";
        print(x);
    }
    std::cerr << "}";
}


// queue
template<typename T>
void print(std::queue<T> q) {
    std::cerr << "[";
    bool first = true;
    while (!q.empty()) {
        if (!first) std::cerr << ", ";
        first = false;
        print(q.front());
        q.pop();
    }
    std::cerr << "]";
}

// stack
template<typename T>
void print(std::stack<T> s) {
    std::vector<T> temp;
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }
    std::reverse(temp.begin(), temp.end());
    print(temp);
}

// priority_queue
template<typename T>
void print(std::priority_queue<T> pq) {
    std::vector<T> temp;
    while (!pq.empty()) {
        temp.push_back(pq.top());
        pq.pop();
    }
    print(temp);
}

}
#endif
