// tested on https://open.kattis.com/problems/primesieve
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/math/PrimeSieve.h"
// change MAX_PR to
// const int MAX_PR = 100'000'000;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<int> primes = primeSieve(n + 1);
  cout << primes.size() << '\n';

  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    cout << isprime[x] << '\n';
  }
}
