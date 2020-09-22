template <class T>
pair<vector<bool>, vector<T>> dijkstra(
 const vector<vector<pair<int, T>>>& adj, int s) {
  using ST = pair<T, int>; /// state type
  priority_queue<ST, vector<ST>, greater<ST>> q;
  vector<T> dist(adj.size());
  vector<bool> seen(adj.size());
  q.emplace(T{}, s);
  seen[s] = 1;
  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();
    if (dist[u] < d) continue;
    for (auto [v, w] : adj[u])
      if (!seen[v] || d + w < dist[v]) {
        q.emplace(dist[v] = d + w, v);
        seen[v] = 1;
      }
  }
  return {seen, dist};
}
