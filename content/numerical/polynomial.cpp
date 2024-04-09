#include <bits/stdc++.h>
usingnamespace std;
const int inf = 1e9;
const int magic = 500;
// threshold for sizes to run the naive algo
template<typename T> struct poly {
  vector<T> a;
  void normalize() { // get rid of leading zeroes
    while (!a.empty() && a.back() == T(0)) a.pop_back(); }
  poly() {}
  poly(T a0): a{a0} { normalize() ; }
  poly(vector<T> t): a(t) { normalize() ; }
  poly operator+=(const poly& t) {
    a.resize(max(a.size(), t.a.size()));
    for (size_t i = 0; i < t.a.size(); i++) a[i] += t.a[i];
    normalize() ;
    return *this; }
  poly operator-=(const poly& t) {
    a.resize(max(a.size(), t.a.size()));
    for (size_t i = 0; i < t.a.size(); i++) a[i] -= t.a[i];
    normalize() ;
    return *this; }
  poly operator+(const poly& t) const {
    return poly(*this) += t; }
  poly operator-(const poly& t) const {
    return poly(*this) -= t; }
  poly mod_xk(size_t k) const { // get same polynomial mod x^k
    k = min(k, a.size());
    return vector<T>(begin(a), begin(a) + k); }
  poly mul_xk(size_t k) const { // multiply by x^k
    poly res(*this);
    res.a.insert(begin(res.a), k, 0);
    return res; }
  poly div_xk(size_t k) const {
  // divide by x^k, dropping coefficients
    k = min(k, a.size());
    return vector<T>(begin(a) + k, end(a)); }
  poly substr(size_t l, size_t r) const {
  // return mod_xk(r).div_xk(l)
    l = min(l, a.size());
    r = min(r, a.size());
    return vector<T>(begin(a) + l, begin(a) + r); }
  poly inv(size_t n) const { // get inverse series mod x^n
    assert(!is_zero());
    poly ans = a[0].inv();
    size_t a = 1;
    while (a < n) {
      poly C = (ans * mod_xk(2 * a)).substr(a, 2 * a);
      ans -= (ans * C).mod_xk(a).mul_xk(a);
      a *= 2; }
    return ans.mod_xk(n); }
  poly operator*=(const poly& t) {
    fft::mul(a, t.a);
    normalize() ;
    return *this; }
  poly operator*(const poly& t) const {
    return poly(*this) *= t; }
  poly reverse(size_t n, bool rev = 0) const {
  // reverses and leaves only n terms
    poly res(*this);
    if (rev) // If rev = 1 then tail goes to head
      res.a.resize(max(n, res.a.size()));
    std::reverse(res.a.begin(), res.a.end());
    return res.mod_xk(n); }
  pair<poly, poly> divmod_slow(const poly& b) const {
  // when divisor or quotient is small
    vector<T> A(a);
    vector<T> res;
    while (A.size() >= b.a.size()) {
      res.push_back(A.back() / b.a.back());
      if (res.back() != T(0)) {
        for (size_t i = 0; i < b.a.size(); i++) {
          A[A.size() - i - 1] -= res.back() * b.a[b.a.size() - i - 1];
        } }
      A.pop_back(); }
    std::reverse(begin(res), end(res));
    return {res, A}; }
  pair<poly, poly> divmod(const poly& b) const {
  // returns quotiend and remainder of a mod b
    if (deg() < b.deg()) return {poly{0}, *this};
    int d = deg() - b.deg();
    if (min(d, b.deg()) < magic) return divmod_slow(b);
    poly D = (reverse(d + 1) * b.reverse(d + 1).inv(d + 1)).mod_xk(d + 1).reverse(d + 1,
                                                                                  1);
    return {D, *this - D * b}; }
  poly
  operator/(const poly& t) const { return divmod(t).first; }
  poly
  operator%(const poly& t) const { return divmod(t).second; }
  poly operator/=(const poly& t) {
    return *this = divmod(t).first; }
  poly operator%=(const poly& t) {
    return *this = divmod(t).second; }
  poly operator*=(const T& x) {
    for (auto& it : a) it *= x;
    normalize() ;
    return *this; }
  poly operator/=(const T& x) {
    for (auto& it : a) it /= x;
    normalize() ;
    return *this; }
  poly
  operator*(const T& x) const { return poly(*this) *= x; }
  poly
  operator/(const T& x) const { return poly(*this) /= x; }
  void print() const {
    for (auto it : a) cout << it << ' ';
    cout << endl; }
  T eval(T x) const { // evaluates in single point x
    T res(0);
    for (int i = int(a.size()) - 1; i >= 0; i--) {
      res *= x;
      res += a[i]; }
    return res; }
  T& lead() { // leading coefficient
    return a.back(); }
  int deg() const { // degree
    return a.empty() ? -inf : a.size() - 1; }
  bool is_zero() const { // is polynomial zero
    return a.empty(); }
  T operator[](int idx) const {
    return idx >= (int)a.size() || idx < 0 ? T(0) : a[idx]; }
  T& coef(size_t idx) { // mutable reference at coefficient
    return a[idx]; }
  bool operator==(const poly& t) const { return a == t.a; }
  bool operator!=(const poly& t) const { return a != t.a; }
  poly deriv() { // calculate derivative
    vector<T> res;
    for (int i = 1; i <= deg(); i++)
      res.push_back(T(i) * a[i]);
    return res; }
  poly integr() { // calculate integral with C = 0
    vector<T> res = {0};
    for (int i = 0; i <= deg(); i++)
      res.push_back(a[i] / T(i + 1));
    return res; }
  size_t leading_xk() const {
  // Let p(x) = x^k * t(x), return k
    if (is_zero()) return inf;
    int res = 0;
    while (a[res] == T(0)) res++;
    return res; }
  poly log(size_t n) { // calculate log p(x) mod x^n
    assert(a[0] == T(1));
    return (deriv().mod_xk(n) * inv(n)).integr().mod_xk(n); }
  poly exp(size_t n) { // calculate exp p(x) mod x^n
    if (is_zero()) return T(1);
    assert(a[0] == T(0));
    poly ans = T(1);
    size_t a = 1;
    while (a < n) {
      poly C = ans.log(2 * a).div_xk(a) - substr(a, 2 * a);
      ans -= (ans * C).mod_xk(a).mul_xk(a);
      a *= 2; }
    return ans.mod_xk(n); }
  poly pow_slow(size_t k, size_t n) { // if k is small
    return k ? k % 2
               ? (*this * pow_slow(k - 1, n)).mod_xk(n)
               : (*this * *this).mod_xk(n).pow_slow(k / 2, n)
             : T(1); }
  poly pow(size_t k, size_t n) { // calculate p^k(n) mod x^n
    if (is_zero()) return *this;
    if (k < magic) return pow_slow(k, n);
    int i = leading_xk();
    T j = a[i];
    poly t = div_xk(i) / j;
    return bpow(j,
                k) * (t.log(n) * T(k)).exp(n).mul_xk(i * k).mod_xk(n);
  }
  poly mulx(T x) { // component-wise multiplication with x^k
    T cur = 1;
    poly res(*this);
    for (int i = 0; i <= deg(); i++) {
      res.coef(i) *= cur;
      cur *= x; }
    return res; }
  poly mulx_sq(T x) {
  // component-wise multiplication with x^{k^2}
    T cur = x;
    T total = 1;
    T xx = x * x;
    poly res(*this);
    for (int i = 0; i <= deg(); i++) {
      res.coef(i) *= total;
      total *= cur;
      cur *= xx; }
    return res; }
  vector<T> chirpz_even(T z, int n) {
  // P(1), P(z^2), P(z^4), ..., P(z^2(n-1))
    int m = deg();
    if (is_zero()) return vector<T>(n, 0);
    vector<T> vv(m + n);
    T zi = z.inv();
    T zz = zi * zi;
    T cur = zi;
    T total = 1;
    for (int i = 0; i <= max(n - 1, m); i++) {
      if (i <= m) vv[m - i] = total;
      if (i < n) vv[m + i] = total;
      total *= cur;
      cur *= zz; }
    poly w = (mulx_sq(z) * vv).substr(m, m + n).mulx_sq(z);
    vector<T> res(n);
    for (int i = 0; i < n; i++) res[i] = w[i];
    return res; }
  vector<T> chirpz(T z, int n) {
  // P(1), P(z), P(z^2), ..., P(z^(n-1))
    auto even = chirpz_even(z, (n + 1) / 2);
    auto odd = mulx(z).chirpz_even(z, n / 2);
    vector<T> ans(n);
    for (int i = 0; i < n / 2; i++) {
      ans[2 * i] = even[i];
      ans[2 * i + 1] = odd[i]; }
    if (n % 2 == 1) ans[n - 1] = even.back();
    return ans; }
  template<typename iter>
  vector<T> eval(vector<poly>& tree, int v, iter l, iter r) {
  // auxiliary evaluation function
    if (r - l == 1) { return {eval(*l)}; }
    else {
      auto m = l + (r - l) / 2;
      auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, m);
      auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1,
                                              m, r);
      A.insert(end(A), begin(B), end(B));
      return A; } }
  vector<T> eval(vector<T> x) {
  // evaluate polynomial in (x1, ..., xn)
    int n = x.size();
    if (is_zero()) return vector<T>(n, T(0));
    vector<poly> tree(4 * n);
    build(tree, 1, begin(x), end(x));
    return eval(tree, 1, begin(x), end(x)); }
  template<typename iter>
  poly inter(vector<poly>& tree, int v, iter l, iter r,
             iter ly, iter ry) {
  // auxiliary interpolation function
    if (r - l == 1) { return {*ly / a[0]}; }
    else {
      auto m = l + (r - l) / 2;
      auto my = ly + (ry - ly) / 2;
      auto A = (*this % tree[2 * v]).inter(tree, 2 * v, l, m,
                                           ly, my);
      auto B = (*this % tree[2 * v + 1]).inter(tree,
                                               2 * v + 1, m,
                                               r, my, ry);
      return A * tree[2 * v + 1] + B * tree[2 * v]; } } };
template<typename T> T resultant(poly<T > a, poly < T> b) {
// computes resultant of a and b
  if (b.is_zero()) { return 0; }
  else if (b.deg() == 0) { return bpow(b.lead(), a.deg()); }
  else {
    int pw = a.deg();
    a %= b;
    pw -= a.deg();
    T mul = bpow(b.lead(),
                 pw) * T((b.deg() & a.deg() & 1) ? -1 : 1);
    T ans = resultant(b, a);
    return ans * mul; } }
template<typename T>
poly<T> inter(vector<T > x, vector < T> y) {
// interpolates minimum polynomial from (xi, yi) pairs
  int n = x.size();
  vector<poly<T>> tree(4 * n);
  return build(tree, 1, begin(x),
               end(x)).deriv().inter(tree, 1, begin(x),
                                     end(x), begin(y),
                                     end(y)); }
