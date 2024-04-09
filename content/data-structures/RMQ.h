/**
 * Description: Constant time subarray min/max queries for a
 * fixed array. Queries are inclusive-exclusive.
 * Time: $O(n log n)$ initialization and $O(1)$ queries. 
 * Status: Tested
 */
template<class T, class C = less<T>> struct RMQ {
  vector<vector<T>> t;
  C cmp;
  RMQ(vector<T>& a, C cmp = C{}):
    t(__lg(sz(a)) + 1, a), cmp(cmp) {
    for (int k = 1, len = 1; k < sz(t); k++, len <<= 1)
      for (int i = 0; i + 2 * len - 1 < sz(a); i++)
        t[k][i] = min(t[k - 1][i], t[k - 1][i + len], cmp); }
  T query(int a, int b) { // inclusive-exclusive [a, b)
    int k = __lg(b - a), len = 1 << k;
    return min(t[k][a], t[k][b - len], cmp); } };
