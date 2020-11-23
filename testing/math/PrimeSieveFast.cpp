// tested on https://open.kattis.com/problems/primesieve
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/math/PrimeSieveFast.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<int> allPrimes = primeSieve();
  int cnt = 0;
  for (int i : allPrimes)
    if (i <= n) cnt++;

  cout << cnt << '\n';

  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    cout << isPrime[x] << '\n';
  }
}
