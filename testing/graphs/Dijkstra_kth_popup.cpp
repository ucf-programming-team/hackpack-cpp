#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T>
pair<vector<bool>, vector<T>> dijkstra(
 vector<vector<pair<int, T>>>& adj, int s) {
  using ST = pair<T, int>; // state type
  priority_queue<ST, vector<ST>, greater<ST>> q;
  vector<T> dist(adj.size());
  vector<bool> seen(adj.size()), reached = seen;
  q.emplace(0, s);
  seen[s] = 1;
  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();
    if (reached[u]) continue;
    reached[u] = 1;
    for (auto [v, w] : adj[u])
      if (!seen[v] || d + w < dist[v])
        q.emplace(dist[v] = d + w, v), seen[v] = 1;
  }
  return {reached, dist};
}

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
