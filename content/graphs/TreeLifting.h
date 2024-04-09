/**
 * Author: lightseba
 * Date: 2022-04-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/100826
 * Description: Calculate jumps up a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N)$, queries $O(\log N)$
 * Status: Tested
 */
#pragma once
struct lift {
  vi d, p, j;
  lift(vector<vi>& adj): d(sz(adj)), p(d), j(d) {
    dfs(0, adj); }
  void dfs(int u, vector<vi>& adj) {
    int jmp = (d[u] + d[j[j[u]]] == 2 * d[j[u]]) ? j[j[u]]
                                                 : u;
    for (int v : adj[u]) if (v != p[u])
      d[v] = d[p[v] = u] + 1, j[v] = jmp, dfs(v, adj); }
  int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    while (d[u] > d[v]) u = d[j[u]] >= d[v] ? j[u] : p[u];
    if (u == v) return u;
    while (p[u] != p[v]) if (j[u] != j[v]) u = j[u], v = j[v];
    else u = p[u], v = p[v];
    return p[u]; }
  int kth(int u, int k) {
    if (k > d[u]) return -1;
    k = d[u] - k;
    while (d[u] > k) u = d[j[u]] >= k ? j[u] : p[u];
    return u; } };
