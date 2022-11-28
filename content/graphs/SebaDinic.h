/**
 * Description: Max flow algorithm. Can find a valid
 * circulation given vertex and/or edge demands. Time:
 * $O(VE\log{U})$
 */
// disable scaling when max flow/capacity is small, or
// sometimes on random data
template<bool SCALING = true> struct Dinic {
	struct Edge {
		int v, dual;
		ll cap, res;
		constexpr ll flow() { return max(cap - res, 0LL); }
	};
	int n, s, t;
	vi lvl, q, ptr;
	vector<vector<Edge>> adj;
	vector<pii> edges;
	Dinic(int n): n(n + 2), s(n++), t(n++), q(n), adj(n) {}
	int add(int u, int v, ll cap, ll flow = 0) {
		adj[u].push_back({v, sz(adj[v]), cap, cap - flow});
		adj[v].push_back({u, sz(adj[u]) - 1, 0, 0});
		edges.emplace_back(u, adj[u].size() - 1);
		return edges.size() - 1; // this Edge's ID
	}
	ll dfs(int u, ll in) {
		if (u == t || !in) return in;
		ll flow = 0;
		for (int& i = ptr[u]; i < sz(adj[u]); i++) {
			auto& e = adj[u][i];
			if (e.res && lvl[e.v] == lvl[u] - 1)
				if (ll out = dfs(e.v, min(in, e.res))) {
					flow += out, in -= out, e.res -= out;
					adj[e.v][e.dual].res += out;
					if (!in) return flow;
				}
		}
		return flow;
	}
	ll flow() {
		ll flow = 0;
		q[0] = t;
		for (int B = SCALING * 30; B >= 0; B--) do {
				lvl = ptr = vi(n);
				int qi = 0, qe = lvl[t] = 1;
				while (qi < qe && !lvl[s]) {
					int u = q[qi++];
					for (auto& e : adj[u])
						if (!lvl[e.v] && adj[e.v][e.dual].res >> B)
							q[qe++] = e.v, lvl[e.v] = lvl[u] + 1;
				}
				if (lvl[s]) flow += dfs(s, LLONG_MAX);
			} while (lvl[s]);
		return flow;
	}
	Edge& get(int id) { // get Edge object from its ID
		return adj[edges[id].first][edges[id].second];
	}
	void clear() {
		for (auto& it : adj)
			for (auto& e : it) e.res = e.cap;
	}
	bool leftOfMinCut(int u) { return lvl[u] == 0; }
	// d is a list of vertex demands, d[u] = flow in - flow out
	// negative if u is a source, positive if u is a sink
	bool circulation(vector<ll> d = {}) {
		d.resize(n);
		vector<int> circEdges;
		Dinic g(n);
		for (int u = 0; u < n; u++)
			for (auto& e : adj[u]) {
				d[u] += e.flow(), d[e.v] -= e.flow();
				if (e.res) circEdges.push_back(g.add(u, e.v, e.res));
			}
		int tylerEdge = g.add(t, s, LLONG_MAX, 0);
		ll flow = 0;
		for (int u = 0; u < n; u++)
			if (d[u] < 0) g.add(g.s, u, -d[u]);
			else if (d[u] > 0) g.add(u, g.t, d[u]), flow += d[u];
		if (flow != g.flow()) return false;
		int i = 0; // reconstruct the flow into this graph
		for (int u = 0; u < n; u++)
			for (auto& e : adj[u])
				if (e.res) e.res -= g.get(circEdges[i++]).flow();
		return true;
	}
};
