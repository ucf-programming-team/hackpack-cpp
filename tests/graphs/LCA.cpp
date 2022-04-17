// tested on Library-Checker: Lowest Common Ancestor
// https://judge.yosupo.jp/problem/lca
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;

using ll = long long;

#include "../../content/graphs/LCA.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<vector<int>> adj(n);

  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    adj[p].push_back(i);
    adj[i].push_back(p); // check undirected case
  }

  LCA lca(adj);

  for (int i = 0; i < q; i++) {
    int u, v;
    cin >> u >> v;
    cout << lca.lca(u, v) << '\n';
  }
}
