static class MinCostFlow4 {
	public final long INF1 = 1000000000;
	public final long INF2 = 100000000;
	public ArrayList<Edge>[] adj;
	public int s, t, mS, mT;
	public Edge[] prev;
	public long[] w, pi;
	
	public MinCostFlow4(int n) {
		s = n++;  t = n++;  mS = n++;  mT = n++;
		adj = new ArrayList[n];
		for(int i = 0; i < adj.length; i++)
			adj[i] = new ArrayList<>();
	}
	
	public Edge add(int a, int b, long cap, long c) {
		Edge e1 = new Edge(a, b, cap, c);
		Edge e2 = new Edge(b, a, 0, -c);
		e1.rev = e2;  e2.rev = e1;
		adj[a].add(e1);  adj[b].add(e2);
		return e1;
	}
	
	public long[] minCostMaxFlowNegCycles() {
		Edge f = add(t, s, INF1, -INF2);
		long c = minCostFlow();
		return new long[] {INF1 - f.cap, c + INF2 * (INF1 - f.cap)};
	}
	
	public long minCostFlow() {
		long res = 0;
		long[] val = new long[adj.length];
		for(int i = 0; i < adj.length; i++) {
			for(Edge e : adj[i]) {
				if(e.cap > 0 && e.cost < 0) {
					res += e.cap * e.cost;
					val[e.u] -= e.cap;
					val[e.v] += e.cap;
					e.rev.cap = e.cap;
					e.cap = 0;
				}
			}
		}
		for(int i = 0; i < val.length; i++) {
			if(val[i] > 0)
				add(mS, i, val[i], 0);
			else if(val[i] < 0)
				add(i, mT, -val[i], 0);
		}
		// add(sink, source, INF1, 0);	// for min cost flow with source and sink
		s = mS;
		t = mT;
		return res + minCostMaxFlow()[1];
	}
	
	public long[] minCostMaxFlow() {
		long flow = 0;
		long cost = 0;
		getPotential();
		while(findPath()) {
			flow += w[t];
			cost += update();
		}
		return new long[] {flow, cost};
	}
	
	public void getPotential() {
		pi = new long[adj.length];
		Arrays.fill(pi, INF1);
		pi[s] = 0;
		for(int i = 0; i < adj.length - 1; i++) {
			boolean upd = false;
			for(int j = 0; j < adj.length; j++) {
				for(Edge e : adj[j]) {
					if(e.cap > 0 && pi[e.u] + e.cost < pi[e.v]) {
						pi[e.v] = pi[e.u] + e.cost;
						upd = true;
					}
				}
			}
			if(!upd) break;
		}
	}
	
	public boolean findPath() {
		long[] d = new long[adj.length];
		Arrays.fill(d, INF1);
		d[s] = 0;
		prev = new Edge[adj.length];
		w = new long[adj.length];
		Arrays.fill(w, INF1);
		PriorityQueue<Node> pq = new PriorityQueue<>();
		pq.add(new Node(s, 0));
		while(pq.size() > 0) {
			Node node = pq.poll();
			if(node.d == d[node.id]) {
				for(Edge e : adj[node.id]) {
					long nd = d[node.id] + e.cost + pi[e.u] - pi[e.v];
					if(e.cap > 0 && nd < d[e.v]) {
						d[e.v] = nd;
						prev[e.v] = e;
						w[e.v] = Math.min(w[node.id], e.cap);
						pq.add(new Node(e.v, nd));
					}
				}
			}
		}
		for(int i = 0; i < pi.length; i++)
			pi[i] += d[i];
		return d[t] < INF1;
	}
	
	public long update() {
		int v = t;
		long cur = 0;
		while(prev[v] != null) {
			prev[v].cap -= w[t];
			prev[v].rev.cap += w[t];
			cur += w[t] * prev[v].cost;
			v = prev[v].u;
		}
		return cur;
	}
	
	class Edge {
		int u, v;  long cap, cost;  Edge rev;
		public Edge(int s, int e, long capp, long c) {
			u = s;  v = e;  cap = capp;  cost = c;
		}
	}
	
	class Node implements Comparable<Node> {
		int id;  long d;
		public Node(int i, long dd) {
			id = i;  d = dd;
		}
		public int compareTo(Node o) {
			return Long.compare(d, o.d);
		}
	}
}
