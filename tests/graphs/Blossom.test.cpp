#define PROBLEM https://judge.yosupo.jp/problem/general_matching
#include "../../tests/TestRunner.h"
#include "../../content/graphs/Blossom.h"

void test() {
  int n, m;
  cin >> n >> m;

  vector<vi> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  auto mate = Blossom(adj);
  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += mate[i] > i;

  cout << ans << "\n";
  for (int i = 0; i < n; i++)
    if (mate[i] > i)
      cout << i << " " << mate[i] << "\n";
}
