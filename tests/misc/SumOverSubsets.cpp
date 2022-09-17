// Tested on https://judge.yosupo.jp/problem/subset_convolution
// https://judge.yosupo.jp/submission/80235

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MOD = 998244353;

#include "../../content/math/ModInt.h"
#include "../../content/misc/SumOverSubsets.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<mi> a(1 << n), b(1 << n);

  for (auto& x : a) cin >> x.v;
  for (auto& x : b) cin >> x.v;

  auto c = conv(a, b);

  for (auto& x : c) cout << int(x) << " ";
  cout << "\n";
  
  return 0;
}
