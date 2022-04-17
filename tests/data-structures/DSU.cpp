// tested on https://open.kattis.com/problems/unionfind
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;

using ll = long long;

#include "../../content/data-structures/DSU.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  DSU dsu(n);

  while (q--) {
    string t;
    int a, b;
    cin >> t >> a >> b;

    if (t == "=")
      dsu.join(a, b);
    else
      cout << (dsu.same(a, b) ? "yes\n" : "no\n");
  }
}
