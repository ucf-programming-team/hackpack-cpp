// tested on SPOJ FASTFLOW
// https://www.spoj.com/problems/FASTFLOW/
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
using ll = long long;

#include "../../content/graphs/Dinic.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  Dinic g(n);
  g.add(g.s, 0, LLONG_MAX / 4);
  g.add(n - 1, g.t, LLONG_MAX / 4);

  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;

    g.add(a, b, c);
    g.add(b, a, c);
  }

  cout << g.flow() << '\n';

  return 0;
}
