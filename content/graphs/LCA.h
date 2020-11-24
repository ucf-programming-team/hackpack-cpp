/**
 * Description: Answers lowest common ancestor
 * queries on a rooted tree using RMQ. Works with
 * both directed and undirected adjacency lists.
 * Time: $O(1)$ queries with an $O(n \log{n})$ precomp (RMQ).
 */

#include "../../content/data-structures/RMQ.h"

struct LCA {
  int T = 0;
  vector<int> pre, inv, tour;
  RMQ<int> rmq;
  LCA(vector<vector<int>>& adj, int root = 0):
    pre(size(adj)), inv(pre), rmq((dfs(adj, root), tour)) {}
  void dfs(vector<vector<int>>& adj, int u, int p = -1) {
    inv[pre[u] = T++] = u;
    for (int v : adj[u])
      if (v != p) tour.push_back(pre[u]), dfs(adj, v, u);
  }
  int lca(int u, int v) {
    if (u == v) return u;
    tie(u, v) = minmax(pre[u], pre[v]);
    return inv[rmq.query(u, v - 1)];
  }
};
