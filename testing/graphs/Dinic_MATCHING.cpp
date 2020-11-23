// tested on SPOJ MATCHING
// https://www.spoj.com/problems/MATCHING/
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
using ll = long long;

#include "../../content/graphs/Dinic.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n1, n2, m;
  cin >> n1 >> n2 >> m;

  Dinic g(n1 + n2);

  for (int i = 0; i < n1; i++) g.add(g.s, i, 1);

  for (int i = 0; i < n2; i++) g.add(n1 + i, g.t, 1);

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    g.add(u, n1 + v, 1);
  }

  cout << g.flow() << '\n';

  return 0;
}
