#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define rep(a, b, c) for (int a = b; a < c; a++)
#define sz(x) (int)x.size()

using namespace std;
using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;

// template<int N>
struct Dinic {
	// disable scaling when max flow/capacity is small, or
	// sometimes on random data
	const static bool SCALING = false; // lol unit edges
	struct Edge {
		int v, dual;
		ll cap, res;
		constexpr ll flow() { return max(cap - res, 0ll); }
	};
	int n, s, t;
	vector<int> lvl, q, blk, ptr;
	vector<vector<Edge>> adj;
	vector<pair<int, int>> edges;
	Dinic(int n): n(n + 2), s(n++), t(n++), adj(n), q(n) {}
	int add(int u, int v, ll cap, ll flow = 0) {
		adj[u].push_back({v, int(adj[v].size()), cap, cap - flow});
		adj[v].push_back({u, int(adj[u].size()) - 1, 0, 0});
		edges.emplace_back(u, adj[u].size() - 1);
		return edges.size() - 1; // this Edge's ID
	}
	ll dfs(int u, ll in) {
		if (u == t || !in) return in;
		ll flow = 0;
		// for (auto& e : adj[u]) {
		for (int& i = ptr[u]; i < adj[u].size(); i++) {
			auto& e = adj[u][i];
			if (e.res && lvl[e.v] == lvl[u] - 1)
				if (ll out = dfs(e.v, min(in, e.res))) {
					flow += out, in -= out, e.res -= out;
					adj[e.v][e.dual].res += out;
					if (!in) return flow;
					// return flow;
				}
		}
		// blk[u] = 1;
		return flow;
	}
	ll flow() {
		ll flow = 0;
		q[0] = t;
		for (int B = SCALING * 30; B >= 0; B--) do {
				lvl = ptr = vector<int>(n);
				int qi = 0, qe = lvl[t] = 1;
				while (qi < qe && !lvl[s]) {
					int u = q[qi++];
					for (auto& e : adj[u])
						if (!lvl[e.v] && adj[e.v][e.dual].res >> B)
							q[qe++] = e.v, lvl[e.v] = lvl[u] + 1;
				}
				if (lvl[s]) flow += dfs(s, LLONG_MAX);
				// while (ll f = dfs(s, LLONG_MAX)) flow += f;
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
			for (auto& e : adj[u]) if (e.cap) {
				d[u] += e.flow(), d[e.v] -= e.flow();
				if (e.res) circEdges.push_back(g.add(u, e.v, e.res));
			}
		int tylerEdge = g.add(t, s, LLONG_MAX, 0);
		ll flow = 0;
		for (int u = 0; u < n; u++)
			if (d[u] < 0)
				g.add(g.s, u, -d[u]);
			else if (d[u] > 0)
				g.add(u, g.t, d[u]), flow += d[u];
		if (flow != g.flow()) return false;
		int i = 0; // reconstruct the flow into this graph
		for (int u = 0; u < n; u++)
			for (auto& e : adj[u]) if (e.cap) {
				adj[e.v][e.dual].res -= e.flow();
				if (e.res) e.res -= g.get(circEdges[i++]).flow();
				adj[e.v][e.dual].res += e.flow();
			}
		return true;
	}

	pair<bool, ll> maxFlowWithDemands() {
		if (!circulation()) 
			return {false, 0};

		ll init = 0;
		for (auto& e : adj[s]) init += e.flow();

		return {true, init + flow()};
	}
};

void solve() {
	int n, m;
	cin >> n >> m;

	ll r, b;
	cin >> r >> b;

	map<ll, ll> xf, yf;
	map<ll, vector<ll>> adj;
	vector<pair<ll, ll>> pts;

	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;

		xf[x]++;
		yf[y]++;
		adj[x].push_back(y);
		pts.emplace_back(x, y);
	}

	map<ll, ll> xd, yd;

	for (auto [x, f] : xf) xd[x] = f;
	for (auto [y, f] : yf) yd[y] = f;

	for (int i = 0; i < m; i++) {
		ll t, l, d;
		cin >> t >> l >> d;

		if (t == 1 && xd.count(l)) 
			xd[l] = min(xd[l], d);
		if (t == 2 && yd.count(l))
			yd[l] = min(yd[l], d);
	}

	Dinic g(xf.size() + yf.size());
	map<ll, int> xID, yID;
	int curr = 0;

	for (auto [x, f] : xf) {
		ll d = xd[x];

		ll upper = (f + d) / 2;
		ll lower = (f - d + 1) / 2;

		xID[x] = curr++;

		if (lower > upper) {
			cout << -1 << '\n';
			return;
		}

		g.add(g.s, xID[x], upper, lower);
	}

	for (auto [y, f] : yf) {
		ll d = yd[y];

		ll upper = (f + d) / 2;
		ll lower = (f - d + 1) / 2;

		yID[y] = curr++;

		if (lower > upper) {
			cout << -1 << '\n';
			return;
		}

		g.add(yID[y], g.t, upper, lower);
	}

	vector<int> edges;
	for (auto [x, y] : pts)
		edges.push_back(g.add(xID[x], yID[y], 1));

	auto [able, flow] = g.maxFlowWithDemands();

	if (!able) {
		cout << -1 << '\n';
		return;
	}
	
	char rc = 'r', bc = 'b';
	if (r < b)
		swap(r, b), swap(rc, bc);

	cout << n * r - flow * (r - b) << '\n';

	for (int i : edges)
		cout << (g.get(i).flow() ? bc : rc);
	cout << '\n';
}


int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	// int t; cin >> t; while (t--)
	solve();

	return 0;
}
