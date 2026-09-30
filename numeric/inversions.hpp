i64 invCount(vector<i64>& a, int l, int r, vector<i64>& tmp) {
    if (r - l <= 1) return 0;

    i64 res = 0;
    int mid = (l + r) / 2;
    res += invCount(a, l, mid, tmp);
    res += invCount(a, mid, r, tmp);

    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            res += mid - i;
        }
    }
    while (i < mid) {
        tmp[k++] = a[i++];
    }
    while (j < r) {
        tmp[k++] = a[j++];
    }

    for (i = l; i < r; i++) {
        a[i] = tmp[i];
    }

    return res;
}