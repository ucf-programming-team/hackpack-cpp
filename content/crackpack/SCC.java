//Tarjan Strongly Connected Components O(V + E)
static class SCC {
  ArrayList<Integer>[] adj;
  ArrayList<Integer>[] comp;
  int n;
  int idx, cs;
  boolean[] u;
  int[] pre, low, map;
  ArrayDeque<Integer> s;
  public SCC(int nn) {
    adj = new ArrayList[n = nn];
    for (int curr = 0; curr < n; ++curr)
      adj[curr] = new ArrayList<>();
  }
  void add(int v1, int v2) {
    adj[v1].add(v2); 
  }
  int[] go() {
  comp = new ArrayList[n];
    idx = 1; cs = 0;
    pre = new int[n]; low = new int[n]; map = new int[n];
    u = new boolean[n];
    s = new ArrayDeque<Integer>();
    for (int i = 0; i < n; ++i)
      if (pre[i] == 0)
        dfs(i);
    return map;
  }

  void dfs(int v) {
    pre[v] = low[v] = idx++;
    s.push(v);
    u[v] = true;
    for (int to : adj[v]) {
      if (pre[to] == 0) {
        dfs(to);
        low[v] = Math.min(low[v], low[to]);
      } else if (u[to]) {
        low[v] = Math.min(low[v], pre[to]);
      }
    }
    if (low[v] == pre[v]) {
      int next;
      comp[cs] = new ArrayList<>();
      do {
        next = s.pop();
        u[next] = false;
        map[next] = cs;
        comp[cs].add(next);
      } while (next != v);
      cs++;
    }
  }

  //# Make sure to call go() before calling this function.
  // Function returns a new graph such that all SCCs are
  // compressed into one node and only the edges connecting
  // two components are in the new graph.
  // nodeMapping is an integer array that will store the mapping
  // for each node in the old graph into the new graph.//$
  ArrayList[] compressSCC() {
    ArrayList<Integer>[] g = new ArrayList[cs];
    for(int i = 0; i < cs; i++) g[i] = new ArrayList<Integer>();
    int[] added = new int[cs];
    Arrays.fill(added, -1);
    for(int i = 0; i < cs; i++) {
      for(int v : comp[i]) {
        for(int to : adj[v]) {
          int mapTo = map[to];
          if(mapTo != i && added[mapTo] != i) {
            g[i].add(mapTo);
            added[mapTo] = i;
          }
        }
      }
    }
    return g;
  }
}
