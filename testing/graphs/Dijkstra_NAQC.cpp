// Tested on https://open.kattis.com/problems/bigtruck

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/graphs/Dijkstra.h"

struct Weight {
  ll d, it;
  Weight(ll d = 0, ll it = 0): d(d), it(it) {}
  Weight operator+(const Weight& o) const {
    return {d + o.d, it + o.it};
  }
  bool operator<(const Weight& o) const {
    return d < o.d || (d == o.d && it > o.it);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> items(n);
  vector<vector<pair<int, Weight>>> adj(n);

  for (int& x : items) cin >> x;

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;

    adj[u].emplace_back(v, Weight(w, items[v]));
    adj[v].emplace_back(u, Weight(w, items[u]));
  }

  auto [reached, dist] = dijkstra(adj, 0);

  if (!reached[n - 1])
    cout << "impossible\n";
  else
    cout << dist[n - 1].d << " " << dist[n - 1].it + items[0]
         << "\n";
}
