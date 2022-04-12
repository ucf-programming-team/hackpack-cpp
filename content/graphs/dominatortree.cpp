struct DominatorTree {
  vector<vi> adj, ans; // input edges, edges of dominator tree (directed tree downwards from root)
  vector<vi> radj, child, sdomChild;
  vi label, rlabel, sdom, dom;
  vi par, bes;
  int co = 0;
  DominatorTree(int n) {
    n += n;
    adj = ans = radj = child = sdomChild = vector<vector<int>>(n);
    label = rlabel = sdom = dom = par = bes = vector<int>(n);
  }
  void add_edge(int a, int b) { adj[a].pb(b); }
  int get(int x) {
    if (par[x] != x) {
      int t = get(par[x]); par[x] = par[par[x]];
      if (sdom[t] < sdom[bes[x]]) bes[x] = t;
    }
    return bes[x];
  } 
  void dfs(int x) { // create DFS tree
    label[x] = ++co; rlabel[co] = x; 
    sdom[co] = par[co] = bes[co] = co;
    for(auto y : adj[x]) {
      if (!label[y]) {
        dfs(y); child[label[x]].pb(label[y]); }
      radj[label[y]].pb(label[x]);
    }
  }
  void init(int root) {
    dfs(root);
    for(int i = co; i >= 1; --i) {
      for(auto j : radj[i]) sdom[i] = min(sdom[i], sdom[get(j)]);
      if (i > 1) sdomChild[sdom[i]].pb(i);
      for(auto j : sdomChild[i]) {
        int k = get(j);
        if (sdom[j] == sdom[k]) dom[j] = sdom[j];
        else dom[j] = k;
      }
      for(auto j : child[i]) par[j] = i;
    }
    for(int i = 2; i < co+1; ++i) {
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
      ans[rlabel[dom[i]]].pb(rlabel[i]);
    }
  }
};
