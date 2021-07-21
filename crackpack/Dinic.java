static class Dinic {
	static class Edge {  int v1, v2, cap, flow; Edge rev;
		Edge(int V1, int V2, int Cap, int Flow) { v1 = V1; v2 = V2; cap = Cap; flow = Flow; }
	}

	ArrayDeque<Integer> q;  ArrayList<Edge>[] adj;
	int n, s, t, mS, mT, oo = (int)1E9;
	boolean[] blocked;  int[] dist;
	public Dinic (int N) {
		n = N; s = n++; t = n++; mS = n++; mT = n++; blocked = new boolean[n];
		dist = new int[n];  q = new ArrayDeque<Integer>();
		adj = new ArrayList[n];  for(int i = 0; i < n; ++i)  adj[i] = new ArrayList<Edge>();
	}
	// Specifying flow can represent minimum flow for circulation.
	Edge add(int v1, int v2, int cap, int flow) {
		Edge e = new Edge(v1, v2, cap, flow);  Edge rev = new Edge(v2, v1, 0, 0);
		adj[v1].add(rev.rev = e);  adj[v2].add(e.rev = rev);
		return e;
	}

	//#
	// Only needed if you need remove function
	void remove(int v1, int v2) {
		Edge e;
		for(int i = 0; i < adj[v1].size(); i++) {
			e = adj[v1].get(i);
			if(e.v2 == v2 && e.cap != 0)  adj[v1].remove(i--);
		}

		for(int i = 0; i < adj[v2].size(); i++) {
			e = adj[v2].get(i);
			if(e.v2 == v1 && e.cap == 0)  adj[v2].remove(i--);
		}
	}
	//$

	boolean bfs() {
		q.clear();  Arrays.fill(dist, -1);  dist[t] = 0;  q.add(t);

		while(!q.isEmpty()) {
			int node = q.poll();
			if(node == s)   return true;
			for(Edge e : adj[node]) {
				if(e.rev.cap > e.rev.flow && dist[e.v2] == -1) {
					dist[e.v2] = dist[node] + 1;  q.add(e.v2);
				}
			}
		}
		return dist[s] != -1;
	}

	int dfs(int pos, int min) {
		if(pos == t)  return min;
		int flow = 0;
		for(Edge e : adj[pos]) {
			int cur = 0;
			if(!blocked[e.v2] && dist[e.v2] == dist[pos]-1 && e.cap - e.flow > 0) {
				cur = dfs(e.v2, Math.min(min-flow, e.cap - e.flow));
				e.flow += cur;  e.rev.flow = -e.flow;  flow += cur;
			}
			if(flow == min)  return flow;
		}
		blocked[pos] = flow != min;
		return flow;
	}
	int flow() {
		clear();  int ret = 0;
		while(bfs()) {  Arrays.fill(blocked, false);  ret += dfs(s, oo);  }
		return ret;
	}
	void clear() {  for(ArrayList<Edge> edges : adj)  for(Edge e : edges)  e.flow = 0;  }
	// Convert the given graph into a graph to test for circulation
	boolean circulation() {
		int[] delta = new int[n];
		Dinic d = new Dinic(n);
		for(int node = 0; node < n; ++node) {
			for(Edge e : adj[node]) {
				if(e.cap > 0 && e.flow >= 0) {
					d.add(e.v1, e.v2, e.cap-e.flow, 0);
					delta[e.v1] -= e.flow;  delta[e.v2] += e.flow;
				}
			}
		}
		ArrayList<Edge> satEdges = new ArrayList<Edge>();
		for(int i = 0; i < n; ++i) {
			if(delta[i] > 0)  satEdges.add(d.add(d.s, i, delta[i], 0));
			else if(delta[i] < 0)  d.add(i, d.t, -delta[i], 0);	
		}
		Edge tylerEdge = d.add(t,s,oo,0);
		int flow = d.flow();
		boolean isSat = true;
		for(Edge e : satEdges) isSat&=(e.cap==e.flow); 				
		return isSat;
	}

	int maxFlowWithMinCap() {
		Edge e = add(t,s,oo,0);
		int lo = 0, hi = oo;
		while(lo < hi) {
			int mid = (lo+hi+1)/2;
			e.flow = mid;
			if(circulation()) lo = mid;
			else hi = mid-1;
		}
		return lo;
	}
	int minFlowWithMinCap() {
		Edge e1 = add(mS, s, 1, 0);
		Edge e2 = add(t, mT, oo, 0);
		add(s, t, oo, 0);
		s = mS; t = mT;
		int lo = 0, hi = oo;
		while(lo < hi) {
			int mid = (lo+hi)/2;
			e1.cap = mid;
			e2.flow = mid;
			if(circulation()) hi = mid;
			else lo = mid+1;
		}
		return lo;
	}
	/* Vertex cover on bipartite graph (L, R):
	Find nodes in S side of S/T min cut (bfs(); dist[i] == -1)
	L1 = L & S, L2 = L - S, R1 = R & S, R2 = R - S
	Let B be the set of vertices in R2 that have neighbors in L1
	C = L2 | R1 | B
	Maximum independent set is the complement nodes 
	To get all nodes that can be in max independent set, get vertexCover()
	then swap source/sink and bfs on saturated edges, then get next vc()
	Nodes that DONT appear in BOTH can be part of max independent set*/
	ArrayList<Integer> vertexCover() {
		BitSet leftNodes = new BitSet();
		BitSet rightNodes = new BitSet();
		BitSet minCut = new BitSet();
		for(Edge e : adj[s])
			if(e.v1 == s)
				leftNodes.set(e.v2);
		for(Edge e : adj[t])
			if(e.v1 == t)
				rightNodes.set(e.v2);
		bfs();
		for(int i = 0; i < s; ++i)
			if(dist[i] == -1)
				minCut.set(i);

		BitSet l1 = new BitSet(); l1.or(leftNodes); l1.and(minCut);
		BitSet l2 = new BitSet(); l2.or(leftNodes); l2.andNot(minCut);
		BitSet r1 = new BitSet(); r1.or(rightNodes); r1.and(minCut);
		BitSet r2 = new BitSet(); r2.or(rightNodes); r2.andNot(minCut);

		BitSet b = new BitSet();
		for(int bit = r2.nextSetBit(0); bit >= 0; bit = r2.nextSetBit(bit+1)) {
			for(Edge e : adj[bit]) {
				if(e.v1 == bit && l1.get(e.v2)) {
					b.set(bit);
					break;
				}
			}
		}

		BitSet c = new BitSet(); c.or(l2); c.or(r1); c.or(b);
		ArrayList<Integer> ret = new ArrayList<Integer>();
		for(int bit = c.nextSetBit(0); bit >= 0; bit = c.nextSetBit(bit+1)) 
			ret.add(bit);
		return ret;
	}
	/* Project selection: s->v with cap p if p > 0. v->t with -p if p < 0
	if w is preReq of v, then v->w with cap INF. Revenue is sum of positive
	revenues minus max flow. Projects taken is bfs() with dist[i] == -1
	Image seg: s->i with cap = value of being on source side. i->t with value
	of being on sink side. i<->j with penalty of i and j in separate groups
	if s->i saturated, then i is on sink side and vice versa
	bfs() with dist[i] == -1 means 'i' is on source side. Total value
	is sum of values of both sides minus max flow
	*/
}
