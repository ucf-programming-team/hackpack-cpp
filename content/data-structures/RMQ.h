template<typename T, class Compare = less<T>>
struct RMQ {
    vector<vector<T>> t;
    Compare cmp;
    RMQ(vector<T> &a) : t(__lg(a.size()) + 1, a) {
        int n = a.size(), lg = __lg(n);
        for (int k = 1, len = 1; i <= lg; i++, len <<= 1)
            for (int i = 0; i <= n - 2 * len; i++)
                t[k][i] = min(t[k - 1][i], t[k - 1][i + len - 1], cmp)
    }
    T query(int a, int b) {
        int k = __lg(b - a + 1), len = 1 << k;
        return min(t[k][a], t[k][b - len + 1], cmp);
    }
};
