//TEST=https://judge.yosupo.jp/problem/lca
#include "testing/tester.h"
#include "content/graphs/TreeLifting.h"

void test() {
  int n, q;
  cin >> n >> q;

  vector<vi> adj(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    adj[p].push_back(i);
    adj[i].push_back(p);
  }

  lift t(adj);

  for (int i = 0; i < q; i++) {
    int u, v;
    cin >> u >> v;
    cout << t.lca(u, v) << "\n";
  }
}
