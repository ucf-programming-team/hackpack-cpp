// tested on Library-Checker: Lowest Common Ancestor
// https://judge.yosupo.jp/problem/lca
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;

using ll = long long;

// #include "../../content/graphs/LCA.h"

using ull = long long;
using uint = unsigned int;

template <uint MD>
struct ModInt {
  using M = ModInt;
  const static M G;
  uint v;
  ModInt(ll _v = 0) { set_v(_v % MD + MD); }
  M& set_v(uint _v) {
    v = (_v < MD) ? _v : _v - MD;
    return *this;
  }
  explicit operator bool() const { return v != 0; }
  M operator-() const { return M() - *this; }
  M operator+(const M& r) const { return M().set_v(v + r.v); }
  M operator-(const M& r) const {
    return M().set_v(v + MD - r.v);
  }
  M operator*(const M& r) const {
    return M().set_v(ull(v) * r.v % MD);
  }
  M operator/(const M& r) const { return *this * r.inv(); }
  M& operator+=(const M& r) { return *this = *this + r; }
  M& operator-=(const M& r) { return *this = *this - r; }
  M& operator*=(const M& r) { return *this = *this * r; }
  M& operator/=(const M& r) { return *this = *this / r; }
  bool operator==(const M& r) const { return v == r.v; }
  M pow(ll n) const {
    M x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  M inv() const { return pow(MD - 2); }
  friend ostream& operator<<(ostream& os, const M& r) {
    return os << r.v;
  }
};
using Mint = ModInt<998244353>;

template <class T, int N, int M = N>
struct Matrix {
  array<array<T, M>, N> a;
  const array<T, M>& operator[](int i) const { return a[i]; }
  array<T, M>& operator[](int i) { return a[i]; }
  template <int X>
  Matrix operator*(const Matrix<T, M, X>& B) const {
    Matrix<T, N, X> ret;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < X; j++)
        for (int k = 0; k < M; k++)
          ret[i][j] += a[i][k] * B[k][j];
    return ret;
  }
  array<T, N> operator*(const array<T, M>& v) const {
    array<T, N> ret;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) ret[i] += a[i][j] * v[j];
    return ret;
  }
  Matrix operator^(ll n) const {
    assert(N == M), assert(n >= 0);
    Matrix A = *this, ret;
    for (int i = 0; i < N; i++) ret[i][i] = 1;
    while (n) {
      if (n & 1) ret = ret * A;
      A = A * A;
      n >>= 1;
    }
    return ret;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  Matrix<Mint, 2> A = {{{{1, 1}, {1, 0}}}};
  Mint two = 2;

  array<Mint, 2> init = {1, 0};
  auto ans = (A ^ (n - 1)) * init;

  cout << ans[0] * (two.inv().pow(n)) << '\n';

  return 0;
}
