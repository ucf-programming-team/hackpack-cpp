/**
 * Description: Answers lowest common ancestor
 * queries on a rooted tree using RMQ. Works with
 * both directed and undirected adjacency lists.
 * Time: $O(1)$ queries with an $O(n \log{n})$ precomp (RMQ).
 */

#include "../../content/data-structures/RMQ.h"

struct LCA {
  int T = 0;
  vector<int> pre, path, times;
  RMQ<int> rmq;
  LCA(vector<vector<int>>& adj, int root = 0)
    : pre(adj.size()), rmq((dfs(root, -1, adj), times)) {}
  void dfs(int u, int p, vector<vector<int>>& adj) {
    pre[u] = T++;
    for (int v : adj[u])
      if (v != p) {
        path.push_back(u), times.push_back(pre[u]);
        dfs(v, u, adj);
      }
  }
  int lca(int u, int v) {
    if (u == v) return u;
    tie(u, v) = minmax(pre[u], pre[v]);
    return path[rmq.query(u, v - 1)];
  }
};
