/**
 * Description: Maintains union of disjoint sets, and can
 * revert to previous states. Time: $O(\log{n})$ queries and
 * unions, $O(\delta time)$ for restoring.
 */

struct RestorableDSU {
  vector<int> s;
  stack<pair<int, int>> stk;
  RestorableDSU(int n) : s(n, -1) {}
  int find(int i) { return s[i] < 0 ? i : find(s[i]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (s[a] > s[b]) swap(a, b);
    stk.emplace(a, s[a]);
    stk.emplace(b, s[b]);
    s[a] += s[b], s[b] = a;
    return true;
  }
  int time() { return stk.size(); }
  void revert(int t) {
    while (stk.size() > t)
      s[stk.top().first] = stk.top().second, stk.pop();
  }
  int size(int i) { return -s[find(i)]; }
  bool same(int a, int b) { return find(a) == find(b); }
};
