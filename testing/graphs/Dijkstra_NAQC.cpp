#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

struct Weight {
	ll d, it;
	Weight(ll d = 0, ll it = 0): d(d), it(it) { }
	Weight operator+(const Weight &o) const { return {d + o.d, it + o.it}; }
	bool operator<(const Weight &o) const { 
		if (d != o.d) return d < o.d;
		return it > o.it;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int n; cin >> n;

	vector<int> items(n);
	vector<vector<pair<int, Weight>>> adj(n);

	for (int &x : items) cin >> x;

	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;

		adj[u].emplace_back(v, Weight(w, items[v]));
		adj[v].emplace_back(u, Weight(w, items[u]));
	}

	auto [reached, dist] = dijkstra(adj, 0);

	if (!reached[n-1]) cout << "impossible\n";
	else cout << dist[n-1].d << " " << dist[n-1].it + items[0] << "\n";
}
