#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../../tests/TestRunner.h"
#include "../../content/graphs/TreeLifting.h"

void test() {
  int n, q;
  cin >> n >> q;

  vector<vi> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  lift t(adj);

  for (int i = 0; i < q; i++) {
    int u, v, k;
    cin >> u >> v >> k;
    int lca = t.lca(u, v);
    if (k < t.d[u] - t.d[lca] + 1)
      cout << t.kth(u, k) << "\n";
    else {
      k -= t.d[u] - t.d[lca] + 1;
      k = t.d[v] - t.d[lca] - 1 - k;

      if (k >= 0)
        cout << t.kth(v, k) << "\n";
      else
        cout << -1 << "\n";
    }
  }
}
