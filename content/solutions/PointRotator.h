#include <bits/stdc++.h>
usingnamespace std;
#define sz(x) int(size(x))
#define all(x) begin(x), end(x)
using ll = long long;
using vi = vector<int>;
template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T> struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0): x(x), y(y) {}
  bool
  operator<(P p) const { return tie(y, x) < tie(p.y, p.x); }
  bool
  operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const {
    return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a),
             x * sin(a) + y * cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; } };
using P = Point<ll>;
struct Angle {
  int x, y;
  int t;
  Angle(int x, int y, int t = 0): x(x), y(y), t(t) {}
  Angle
  operator-(Angle b) const { return {x - b.x, y - b.y, t}; }
  int half() const {
    assert(x || y);
    return y < 0 || (y == 0 && x < 0); }
  Angle t90() const {
    return {-y, x, t + (half() && x >= 0)}; }
  Angle t180() const { return {-x, -y, t + half()}; }
  Angle t360() const { return {x, y, t + 1}; } };
bool operator<(Angle a, Angle b) {
// add a.dist2() and b.dist2() to also compare distances
  return make_tuple(a.t, a.half(),
                    a.y * (ll)b.x) < make_tuple(b.t, b.half(),
                                                a.x * (ll)b.y);
}
using bs = bitset<2000 + 5>;
void solve() {
  int n;
  cin >> n;
  vector<P> pts(n);
  for (int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y;
  assert(n % 2 == 0);
  vi order(n), inv(n);
  iota(all(order), 0);
  sort(all(order),
       [&](int i, int j) { return pts[i] < pts[j]; });
  bs curr;
  bs curr2;
  for (int i = 0; i < n; i++) {
    inv[order[i]] = i;
    if (i < n / 2) curr[order[i]] = 1;
    else curr2[order[i]] = 1; }
  auto doSwap = [&](int i, int j) {
    if (i == j) return;
    int pi = inv[i], pj = inv[j];
    bool temp = curr[i];
    curr[i] = curr[j];
    curr[j] = temp;
    temp = curr2[i];
    curr2[i] = curr2[j];
    curr2[j] = temp;
    swap(order[pi], order[pj]);
    swap(inv[i], inv[j]); };
  // vector<tuple<Angle, int, int>> swaps;
  map<Angle, map<ll, vi>> swaps;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      P v = pts[j] - pts[i];
      if (v.y < 0 || (v.y == 0 && v.x < 0)) v = v * -1;
      ll g = __gcd(abs(v.x), abs(v.y));
      assert(g != 0);
      v = v / g;
      Angle a(v.x, v.y);
      swaps[a][v.cross(pts[j])].push_back(i);
      swaps[a][v.cross(pts[j])].push_back(j); }
  auto orig = order;
  unordered_set<bs> grps;
  grps.insert(curr);
  grps.insert(curr2);
  // cout << "base:\n" << curr << "\n" << curr2 << "\n";
  for (auto& [_, under] : swaps) {
    for (auto& [val, idxs] : under) {
      sort(all(idxs));
      idxs.erase(unique(all(idxs)), end(idxs));
      sort(all(idxs), [&](int i, int j) {
             return inv[i] < inv[j]; }); // cout << "rev: ";
      // for (int i : idxs) cout << pts[i] << " ";
      // cout << "\n";
      int i = 0, j = sz(idxs) - 1;
      while (i < j) doSwap(idxs[i++], idxs[j--]); }
    grps.insert(curr);
    grps.insert(curr2); // cout << "have!: ";
    // for (int i : order) cout << pts[i] << " ";
    // cout << "\n";
    // cout << "then:\n" << curr << "\n" << curr2 << "\n";
  }
  grps.insert(curr);
  // cout << "last:\n" << curr << "\n" << curr2 << "\n";
  cout << sz(grps) << "\n"; }
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  solve() ;
  return 0; }
