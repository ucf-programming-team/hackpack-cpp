// Tested on https://codeforces.com/problemset/problem/427/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/graphs/SCCKosaraju.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const ll MOD = 1000000007;

  int n;
  cin >> n;

  vector<int> cost(n);
  for (int& x : cost) cin >> x;

  vector<vector<int>> adj(n);
  int m;
  cin >> m;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u - 1].push_back(v - 1);
  }

  vector<int> comp = SCCKosaraju::scc(adj);
  vector<ll> add(comp.size(), ( int )1e9 + 10);
  vector<ll> cnt(comp.size(), 1);
  int ncomps = 0;

  for (int i = 0; i < n; i++) {
    ncomps = max(ncomps, comp[i] + 1);

    if (cost[i] < add[comp[i]]) {
      add[comp[i]] = cost[i];
      cnt[comp[i]] = 1;
    } else if (cost[i] == add[comp[i]])
      cnt[comp[i]]++;
  }

  ll ans = 0, ways = 1;
  for (int i = 0; i < ncomps; i++) ans += add[i];
  for (int i = 0; i < ncomps; i++)
    ways = (ways * cnt[i]) % MOD;

  cout << ans << " " << ways << '\n';
}
