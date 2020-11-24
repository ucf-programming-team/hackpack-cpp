// tested on Library-Checker: Persistent UnionFind
// https://judge.yosupo.jp/problem/persistent_unionfind
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;

using ll = long long;

#include "../../content/data-structures/DSURestorable.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<int> a(q + 1), b(q + 1), ans(q + 1, -1);
  vector<vector<int>> adj(q + 1);
  vector<vector<int>> qs(q + 1);

  for (int i = 1; i <= q; i++) {
    int t, k;
    cin >> t >> k >> a[i] >> b[i];
    k++;

    if (t)
      qs[k].push_back(i);
    else
      adj[k].push_back(i);
  }

  RestorableDSU dsu(n);

  auto dfs = [&](int u, auto&& self) -> void {
    for (int i : qs[u]) ans[i] = dsu.same(a[i], b[i]);

    for (int v : adj[u]) {
      int t = dsu.time();
      dsu.join(a[v], b[v]);
      self(v, self);
      dsu.revert(t);
    }
  };

  dfs(0, dfs);

  for (int i : ans)
    if (i != -1) cout << i << '\n';
}
