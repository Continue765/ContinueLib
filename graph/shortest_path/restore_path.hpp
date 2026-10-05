#pragma once
#include <common.hpp>

vector<int> restorePath(vector<int>& pre, int t) {
    vector<int> path = {t};
    while (pre[path.back()] != -1) {
        path.push_back(pre[path.back()]);
    }
    reverse(path.begin(), path.end());
    return path;
}
