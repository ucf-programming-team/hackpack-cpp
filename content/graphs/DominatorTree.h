struct DomTree {
  int curId, n;
  vector<vector<int>> adj, radj;
  vector<int> id, sdom, idom, label, p, dsu, rev;
  vector<bool> vis;
  DomTree() {}
  DomTree(int n)
      : n(n), curId(0), adj(n), radj(n), id(n), sdom(n),
        idom(n), label(n), p(n), dsu(n), rev(n), vis(n) {}
  void add(int u, int v) { adj[u].push_back(v); }
  void dfsOrder(int u, int par) {
    rev[curId] = u;
    id[u] = curId++;
    p[id[u]] = id[par];
    vis[u] = true;
    for (int v : adj[u]) {
      if (!vis[v])
        dfsOrder(v, u);
      radj[id[v]].push_back(id[u]);
    }
  }
  int find(int u, int x) {
    if (u == dsu[u])
      return x != 0 ? -1 : u;
    int v = find(dsu[u], x + 1);
    if (v < 0)
      return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]])
      label[u] = label[dsu[u]];
    dsu[u] = v;
    return x != 0 ? v : label[u];
  }
  void run(int s) {
    dfsOrder(s, s);
    vector<vector<int>> bucket(n);
    for (int i = 0; i < n; i++)
      label[i] = dsu[i] = sdom[i] = i;
    for (int i = n - 1; i >= 0; i--) {
      for (int u : radj[i])
        sdom[i] = min(sdom[i], sdom[find(u, 0)]);
      if (i > 0)
        bucket[sdom[i]].push_back(i);
      for (int u : bucket[i]) {
        int f = find(u, 0);
        idom[u] = sdom[f] == sdom[u] ? sdom[u] : f;
      }
      if (i > 0)
        dsu[i] = p[i];
    }
    for (int i = 1; i < n; i++)
      if (idom[i] != sdom[i])
        idom[i] = idom[idom[i]];
    vector<int> nidom(n), nsdom(n);
    for (int i = 0; i < n; i++) {
      nidom[i] = rev[idom[id[i]]];
      nsdom[i] = rev[sdom[id[i]]];
    }
    tie(idom, sdom) = tie(nidom, nsdom);
  }
};
