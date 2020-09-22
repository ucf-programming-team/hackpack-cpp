// Tested on https://open.kattis.com/problems/shortestpath1

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/graphs/Dijkstra.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  while (true) {
    int n, m, q, s;
    cin >> n >> m >> q >> s;

    if ((n | m | q | s) == 0) break;

    vector<vector<pair<int, ll>>> adj(n);

    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;

      adj[u].emplace_back(v, w);
    }

    auto [reached, dist] = dijkstra(adj, s);

    for (int i = 0; i < q; i++) {
      int u;
      cin >> u;

      if (reached[u])
        cout << dist[u] << '\n';
      else
        cout << "Impossible\n";
    }

    cout << '\n';
  }
}
