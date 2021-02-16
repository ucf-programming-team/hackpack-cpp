/**
 * Description: Constant time subarray min/max queries for a
 * fixed array Time: $O(n log n)$ initialization and $O(1)$
 * queries. Status: Tested
 */

template <typename T, class C = less<T>>
struct RMQ {
  vector<vector<T>> t;
  C cmp;
  RMQ(vector<T>& a, C cmp = C{}):
    t(__lg(a.size()) + 1, a), cmp(cmp) {
    int n = a.size(), lg = __lg(n);
    for (int k = 1, len = 1; k <= lg; k++, len <<= 1)
      for (int i = 0; i + 2 * len - 1 < n; i++)
        t[k][i] = min(t[k - 1][i], t[k - 1][i + len], cmp);
  }
  T query(int a, int b) {
    int k = __lg(b - a + 1), len = 1 << k;
    return min(t[k][a], t[k][b - len + 1], cmp);
  }
};
