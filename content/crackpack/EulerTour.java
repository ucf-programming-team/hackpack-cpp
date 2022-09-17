class Edge {
	boolean dead = false;  int to;  Edge rev;
	public Edge(int t) { to = t; }
}
Deque<Edge>[] adj; // use ArrayDeque for ease
Deque<Integer> tour;
void eulerCircuit(int u) {
	while(!adj[u].isEmpty()) {
		Edge e = adj[u].pop();
		if(e.dead) continue;
		e.rev.dead = true;
		eulerCircuit(e.to);
	}
	tour.addFirst(u);
}