#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include "../../tests/TestRunner.h"

const int MOD = 998244353;

#include "../../content/number-theory/ModInt.h"
#include "../../content/numerical/SumOverSubsets.h"

void test() {
  int n;
  cin >> n;

  vector<mi> a(1 << n), b(1 << n);

  for (auto& x : a) cin >> x.v;
  for (auto& x : b) cin >> x.v;

  auto c = conv(a, b);

  for (auto& x : c) cout << int(x) << " ";
  cout << "\n";  
}
