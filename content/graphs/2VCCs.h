struct graph {
  int n;
  vector<vector<pii>> edges;
  graph(int n): n(n), edges(n) {}
  void addEdge(int a, int b, int id) {
    edges[a].emplace_back(b, id);
    edges[b].emplace_back(a, id); } };
int preCnt, metaN;
vi pre, low, used, stk, lowMap, artMap;
void pop(int stopId) {
  while (size(stk)) {
    int id = stk.back();
    stk.pop_back();
    lowMap[id] = metaN;
    if (id == stopId) break; }
  ++metaN; }
void dfs(int idx, int par, graph& g) {
  pre[idx] = low[idx] = ++preCnt;
  bool hasFwd = false;
  for (auto [next, id] : g.edges[idx]) {
    if (next != par && !used[id]) {
      used[id] = true, stk.push_back(id); // back edge
      if (pre[next] != -1) {
        low[idx] = min(low[idx], pre[next]);
        continue; } // forward edge
      dfs(next, idx, g);
      low[idx] = min(low[idx], low[next]);
      if (par == -1 && hasFwd || par != -1 && low[next] >= pre[idx]) {
      // idx is an articulation point
        if (artMap[idx] == -1) artMap[idx] = metaN++;
        pop(id); }
      hasFwd = true; } }
  if (par == -1 && size(stk)) pop(-1); }
pair<graph, vi> getMeta(graph& g, int numEdges) {
  int n = g.n;
  preCnt = -1, metaN = 0;
  pre = vi(n, -1), low = vi(n), artMap = vi(n, -1);
  used = vi(numEdges), lowMap = vi(numEdges), stk = vi();
  for (int i = 0; i < n; ++i) if (pre[i] == -1) dfs(i, -1, g);
  graph meta = graph(metaN);
  vi seen(metaN, false);
  for (int u = 0; u < n; ++u) {
    if (artMap[u] == -1) continue;
    for (auto [v, id] : g.edges[u]) {
      if (!seen[lowMap[id]]) {
        seen[lowMap[id]] = true;
        meta.addEdge(artMap[u], lowMap[id], -1); } }
    for (auto [v, id] : g.edges[u]) seen[lowMap[id]] = false;
  } // use and return if needed:
  // gives a original node contribution to each meta node
  // articulation points are only counted toward their
  // individual meta nodes
  vi cont(metaN);
  for (int u = 0; u < n; ++u) if (artMap[u] != -1)
    cont[artMap[u]] = 1;
  else ++cont[lowMap[g.edges[u].begin()->second]];
  return {meta, cont}; }
