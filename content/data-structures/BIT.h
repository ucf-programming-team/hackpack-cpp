/**
 * Description: Query [l, r] sums, and point updates.
 * kth() returns the smallest index i s.t. query(0, i) >= k
 * Time: $O(\log n)$ for all ops.
 * Status: Tested
 */

template <typename T>
struct BIT {
  vector<T> s;
  int n;
  BIT(int n): s(n + 1), n(n) {}
  void update(int i, T v) {
    for (i++; i <= n; i += i & -i) s[i] += v;
  }
  T query(int i) {
    T ans = 0;
    for (i++; i; i -= i & -i) ans += s[i];
    return ans;
  }
  T query(int l, int r) { return query(r) - query(l - 1); }
  int kth(T k) { // returns n if k > sum of tree
    if (k <= 0) return -1;
    int i = 0;
    for (int pw = 1 << __lg(n); pw; pw >>= 1)
      if (i + pw <= n && s[i + pw] < k) k -= s[i += pw];
    return i;
  }
};
