/**
 * Description: Finds all Two Edge Connected Components and
 *  constructs a meta graph. The meta tree constructed has all
 *  nodes of the same 2ECC compressed into one, with bridges
 *  connecting them. Multi-edges are NOT bridges.
 * Time: O(V + E)
*/
vector<vector<pii>> ed;
int preCnt, metaN, stkSz;
vi pre, metaMap, stk;
void pop(int stop) {
  while (stkSz > 0) {
    int curr = stk[--stkSz];
    metaMap[curr] = metaN;
    if (curr == stop) break; }
  ++metaN; }
int dfs(int idx, int par) {
  int low = pre[idx] = ++preCnt;
  stk[stkSz++] = idx;
  for (auto [v, id] : ed[idx]) {
    if (id == par) continue;
    if (pre[v] != -1) low = min(low, pre[v]); // back edge
    else {
      int get = dfs(v, id);
      low = min(low, get);
      if (get == pre[v]) pop(v); // bridge
    } }
  if (par == -1 && stkSz) pop(idx); // root case
  return low; }
vector<vector<pii>> getMeta() {
  int n = sz(ed);
  preCnt = -1;
  metaN = 0;
  pre.assign(n, -1);
  metaMap.resize(n);
  stk.resize(n);
  stkSz = 0;
  rep (i, 0, n) if (pre[i] == -1) dfs(i, -1);
  vector<vector<pii>> metaEdges(metaN);
  rep (u, 0, n) for (auto [v, id] : ed[u])
    if (metaMap[u] != metaMap[v])
      metaEdges[metaMap[u]].emplace_back(metaMap[v], id);
  return metaEdges; }
