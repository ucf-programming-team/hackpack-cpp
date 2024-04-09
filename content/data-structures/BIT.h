/**
 * Description: Query [0, i) and [l, r) sums, and point updates.
 * kth() returns the smallest index i s.t. query(i) > k.
 * Right endpoint is exclusive.
 * Time: $O(\log n)$ for all ops.
 * Status: Tested
 */
template<class T> struct BIT {
  vector<T> s;
  int n;
  BIT(int n): s(n + 1), n(n) {}
  void update(int i, T v) {
    for (i++; i <= n; i += i & -i) s[i] += v; }
  T query(int i) { // EXCLUSIVE interval [0, i)
    T ans = 0;
    for (; i; i -= i & -i) ans += s[i];
    return ans; } // INCLUSIVE-EXCLUSIVE interval [l, r)
  // partial hash 2fe2e1
  T query(int l, int r) { return query(r) - query(l); }
  int kth(T k) { // 0-indexed, returns n if k > sum of tree
    if (k < 0) return -1;
    int i = 0;
    for (int pw = 1 << __lg(n); pw; pw >>= 1)
      if (i + pw <= n && s[i + pw] <= k) k -= s[i += pw];
    return i; } };
