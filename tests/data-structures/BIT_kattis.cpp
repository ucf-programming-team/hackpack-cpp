#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/data-structures/BIT.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  BIT<ll> bit(n);

  while (q--) {
    string t;
    int i;
    cin >> t >> i;

    if (t == "+") {
      int delta;
      cin >> delta;
      bit.update(i, delta);
    } else
      cout << (i ? bit.query(i - 1) : 0) << '\n';
  }
}
