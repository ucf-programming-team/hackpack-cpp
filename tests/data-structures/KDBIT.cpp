// tested on https://www.spoj.com/problems/MATSUM/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/data-structures/KDBIT.h"

const int N = 1024;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int tests;
  cin >> tests;

  while (tests--) {
    int n;
    cin >> n;

    // this is too big for my stack locally
    BIT<ll, N, N> bit;

    while (true) {
      string t;
      cin >> t;

      if (t == "SET") {
        int x, y;
        ll d;
        cin >> x >> y >> d;

        ll old = bit.query(x, x, y, y);
        bit.update(x, y, d - old);
      }
      if (t == "SUM") {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << bit.query(x1, x2, y1, y2) << '\n';
      }
      if (t == "END") break;
    }
  }
}
