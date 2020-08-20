template<class T> pair<vector<bool>, vector<T>> 
	dijkstra(vector<vector<pair<int, T>>> &adj, int s) {
	using ST = pair<T, int>; // state type
	priority_queue<ST, vector<ST>, greater<ST>> q;
	vector<T> dist(adj.size()); 
	vector<bool> seen(adj.size()), reached = seen;
	q.emplace(0, s); seen[s] = 1;
	while (!q.empty()) {
		auto [d, u] = q.top(); q.pop();
		if (reached[u]) continue; 
		reached[u] = 1;
		for (auto [v, w] : adj[u])
			if (!seen[v] || d + w < dist[v])
				q.emplace(dist[v] = d + w, v), seen[v] = 1;
	}
	return {reached, dist};
}
