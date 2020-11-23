// tested on https://open.kattis.com/problems/fenwick
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/data-structures/BIT.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  BIT<ll> bit(n + 1);

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    bit.update(x, 1);
  }

  while (q--) {
    int i;
    cin >> i;

    if (i > 0)
      bit.update(i, 1);
    else
      bit.update(bit.kth(-i), -1);
  }

  cout << (bit.query(n) ? bit.kth(1) : 0) << '\n';
}
