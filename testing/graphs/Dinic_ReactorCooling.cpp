// tested on ASC 1: Reactor Cooling
// https://codeforces.com/gym/100199
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
using ll = long long;

#include "../../content/graphs/Dinic.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  freopen("cooling.in", "r", stdin);
  freopen("cooling.out", "w", stdout);

  int n, m;
  cin >> n >> m;

  Dinic g(n);
  vector<int> ids;

  for (int i = 0; i < m; i++) {
    int u, v, d, c;
    cin >> u >> v >> d >> c;
    u--, v--;

    ids.push_back(g.add(u, v, c, d));
  }

  if (!g.circulation()) {
    cout << "NO\n";
    return 0;
  }

  cout << "YES\n";
  for (int id : ids) cout << g.get(id).flow() << '\n';

  return 0;
}
