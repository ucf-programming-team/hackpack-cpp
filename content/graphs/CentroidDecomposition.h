/**
 * Time: $O(n \log{n})$
 */
struct CD {
  vector<vector<int>> adj;
  vector<bool> r;  vector<int> size;
  CD(vector<vector<int>>& adj):
    adj(adj), size((int) adj.size()), r((int) adj.size()) {}
  int dfsSize(int u, int p) {
    size[u] = 1;
    for(int v : adj[u])
      if(v != p && !r[v])
        size[u] += dfsSize(v, u);
    return size[u];
  }
  int findCentroid(int u, int p, int cmpSize) {
    for(int v : adj[u])
      if(v != p && !r[v])
        if(size[v] * 2 > cmpSize)
          return findCentroid(v, u, cmpSize);
    return u;
  }
  void run(int u = 0) {
    int c = findCentroid(u, u, dfsSize(u, u));
    // implementation here
    r[c] = true;
    for(int v : adj[c])
      if(!r[v])
        run(v);
  }
};
