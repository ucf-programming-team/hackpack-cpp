struct SCC {
  int n, cnt, cmps, top;
  vector<vector<int>> adj;
  vector<int> pre, scc, low, stk;
  SCC() {}
  SCC(const int& n) : n(n), adj(n), 
    stk(n), low(n), scc(n), pre(n, -1) {
    cnt = cmps = top = 0;
  }
  void addEdge(const int &u, const int &v) {
    adj[u].pb(v);
  }
  void run() {
    for(int i = 0; i < n; i++)
      if(pre[i] == -1)
        dfs(i);
  }
  void dfs(const int& u) {
    pre[u] = low[u] = cnt++;
    stk[top++] = u;
    for(int v : adj[u]) {
      if(pre[v] == -1) dfs(v);
      low[u] = min(low[u], low[v]);
    }
    if(low[u] == pre[u]) {
      while(true) {
        int v = stk[--top];
        scc[v] = cmps;  low[v] = n;
        if(u == v) break;
      }
      cmps++;
    }
  }
};
