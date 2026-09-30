// ============ 子集和：F[mask] = sum_{sub ⊆ mask} f[sub] ============
for (int i = 0; i < m; i++) {
    for (int mask = 0; mask < (1 << m); mask++) {
        if (mask & (1 << i)) {
            f[mask] += f[mask ^ (1 << i)];
        }
    }
}
// 方向：小的 mask → 大的 mask（"吸收"不带的位）
// ============ 超集和：F[mask] = sum_{sup ⊇ mask} f[sup] ============
for (int i = 0; i < m; i++) {
    for (int mask = 0; mask < (1 << m); mask++) {
        if (mask & (1 << i)) {
            f[mask ^ (1 << i)] += f[mask];
        }
    }
}
// 方向：大的 mask → 小的 mask（"分发"给不带这一位的 mask）