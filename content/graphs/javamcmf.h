struct MinCostFlow4 {
	struct Edge {
		int u, v;  ll cap, cost;  Edge* rev;
		Edge(int s, int e, ll cap, ll c):
            u(s), v(e), cap(cap), cost(c), rev(nullptr) { }
	};
	
	struct Node {
		int id;  ll d;
		Node(int i, ll dd): id(i), d(dd) { }
		bool operator<(const Node& o) const { return d > o.d; }
	};

	ll INF1 = 1000000000;
	ll INF2 = 100000000;
	vector<vector<Edge*>> adj;
	int s, t, mS, mT;
	vector<Edge*> previous;
	vector<ll> w, pi;
	
	MinCostFlow4(){}
	MinCostFlow4(int n) {
		s = n++;  t = n++;  mS = n++;  mT = n++;
		adj.resize(n);
	}
	
	Edge* add(int a, int b, ll cap, ll c) {
		Edge* e1 = new Edge(a, b, cap, c);
		Edge* e2 = new Edge(b, a, 0, -c);
		e1->rev = e2;  e2->rev = e1;
		adj[a].pb(e1);  adj[b].pb(e2);
		return e1;
	}
	
	pll minCostMaxFlowNegCycles() {
		Edge* f = add(t, s, INF1, -INF2);
		ll c = minCostFlow();
		return {INF1 - f->cap, c + INF2 * (INF1 - f->cap)};
	}
	
	ll minCostFlow() {
		ll res = 0;
		vector<ll> val(sz(adj));
		for(int i = 0; i < sz(adj); i++) {
			for(Edge* e : adj[i]) {
				if(e->cap > 0 && e->cost < 0) {
					res += e->cap * e->cost;
					val[e->u] -= e->cap, val[e->v] += e->cap;
					e->rev->cap = e->cap;
					e->cap = 0;
				}
			}
		}
		for(int i = 0; i < sz(val); i++) {
			if(val[i] > 0) add(mS, i, val[i], 0);
			else if(val[i] < 0) add(i, mT, -val[i], 0);
		}
		// add(sink, source, INF1, 0);	// for min cost flow with source and sink
		s = mS;
		t = mT;
		return res + minCostMaxFlow().second;
	}
	
	pll minCostMaxFlow() {
		ll flow = 0, cost = 0;
		getPotential();
		while(findPath()) {
			flow += w[t];
			cost += update();
		}
		return {flow, cost};
	}
	
	void getPotential() {
		pi.assign(adj.size(), INF1); pi[s] = 0;
		for(int i = 0; i < sz(adj) - 1; i++) {
			bool upd = false;
			for(int j = 0; j < sz(adj); j++) {
				for(Edge* e : adj[j]) {
					if(e->cap > 0 && pi[e->u] + e->cost < pi[e->v]) {
						pi[e->v] = pi[e->u] + e->cost;
						upd = true;
					}
				}
			}
			if(!upd) break;
		}
	}
	
	bool findPath() {
		vector<ll> d(sz(adj), INF1); d[s] = 0;
		previous.assign(sz(adj), nullptr);
		w.assign(sz(adj), INF1);
		priority_queue<Node> pq; pq.emplace(s, 0);
		while(sz(pq)) {
			Node node = pq.top(); pq.pop();
			if(node.d == d[node.id]) {
				for(Edge* e : adj[node.id]) {
					ll nd = d[node.id] + e->cost + pi[e->u] - pi[e->v];
					if(e->cap > 0 && nd < d[e->v]) {
						d[e->v] = nd;
						previous[e->v] = e;
						w[e->v] = min(w[node.id], e->cap);
						pq.emplace(e->v, nd);
					}
				}
			}
		}
		for(int i = 0; i < sz(pi); i++)
			pi[i] += d[i];
		return d[t] < INF1;
	}
	
	ll update() {
		int v = t;
		ll cur = 0;
		while(previous[v] != nullptr) {
			previous[v]->cap -= w[t];
			previous[v]->rev->cap += w[t];
			cur += w[t] * previous[v]->cost;
			v = previous[v]->u;
		}
		return cur;
	}
};