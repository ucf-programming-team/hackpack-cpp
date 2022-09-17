static class TwoEdgeCCs {
	int n;
	graph g;
	int preCount, metaN, stkSize;
	int[] pre, low, map, stk;
	// returns forest meta graph
	graph getMeta(graph gg) {
		g = gg;
		n = g.n;
		// do lowlink
		preCount = -1;
		metaN = 0;
		pre = new int[n];
		Arrays.fill(pre, -1);
		low = new int[n];
		map = new int[n]; // maps each node in original graph g to new node index in meta
		stk = new int[n];
		stkSize = 0;
		for(int i = 0; i < n; ++i) {
			if(pre[i] == -1) dfs(i, -1);
		}
		graph meta = new graph(metaN);
		for(int u = 0; u < n; ++u) {
			for(edge e : g.edges[u]) {
				// avoid adding edges twice
				if(u < e.v && map[u] != map[e.v]) meta.addEdge(map[u], map[e.v], e.w);
			}
		}
		return meta;
	}
	void dfs(int idx, int par) {
		low[idx] = pre[idx] = ++preCount;
		stk[stkSize++] = idx;
		for(edge e : g.edges[idx]) {
			if(e.v == par) continue;
			// back edge
			if(pre[e.v] != -1) {
				if(pre[e.v] < low[idx]) low[idx] = pre[e.v];
				continue;
			}
			dfs(e.v, idx);
			if(low[e.v] < low[idx]) low[idx] = low[e.v];
			// bridge
			if(low[e.v] == pre[e.v]) pop(e.v);
		}
		if(par == -1 && stkSize > 0) pop(idx);
	}
	void pop(int stop) {
		while(stkSize > 0) {
			int curr = stk[--stkSize];
			map[curr] = metaN;
			if(curr == stop) break;
		}
		++metaN;
	}
}
static class graph {
	int n;
	ArrayDeque<edge>[] edges;
	graph(int nn){
		edges = new ArrayDeque[n = nn];
		for(int i = 0; i < n; ++i) edges[i] = new ArrayDeque<>();
	}
	void addEdge(int a, int b) {
		addEdge(a, b, 1);
	}
	void addEdge(int a, int b, int w) {
		edges[a].add(new edge(b, w));
		edges[b].add(new edge(a, w));
	}
}
static class edge{
	int v, w;
	edge(int vv, int ww){
		v = vv;
		w = ww;
	}
}
