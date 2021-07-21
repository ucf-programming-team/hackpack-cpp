class Graph {
	int n, d, depth[], lift[][];
	List<Integer>[] adj;
	public Graph(int nn) {
		adj = new ArrayList[n = nn];
		for(int i = 0 ; i < n ; i++)
			adj[i] = new ArrayList<>();
		depth = new int[n];
		d = Integer.numberOfTrailingZeros(Integer.highestOneBit(n)) + 2;
		lift = new int[d][n];
		for(int i = 0 ; i < d ; i++) Arrays.fill(lift[i], -1);
	}
	void add(int u, int v) { adj[u].add(v);  adj[v].add(u); }
	void build() {
		Deque<Integer> q = new ArrayDeque<>();
		q.add(0);
		while(!q.isEmpty()) {
			int u = q.pop();
			for(int v : adj[u]) {
				if(lift[0][u] != v) {
					lift[0][v] = u;
					depth[v] = depth[u] + 1;
					q.add(v);
				}
			}
		}
		for(int k = 0 ; k < d - 1 ; k++)
			for(int i = 0 ; i < n ; i++)
				if(lift[k][i] != -1)
					lift[k + 1][i] = lift[k][lift[k][i]];
	}
	int lca(int u, int v) {
		if(depth[v] > depth[u]) return lca(v, u);
		u = walk(u, depth[u] - depth[v]);
		if(u == v) return u;
		for(int k = d - 1 ; k >= 0 ; k--) {
			if(lift[k][u] != lift[k][v]) {
				u = lift[k][u];
				v = lift[k][v];
			}
		}
		return lift[0][u];
	}
	int walk(int u, int k) {
		for(int i = 0 ; i < d && u != -1 ; i++) if((k & (1 << i)) > 0) u = lift[i][u];
		return u;
	}
	int dist(int u, int v) { return depth[u] + depth[v] - (2 * depth[lca(u, v)]); }
}