// Tested on https://codeforces.com/problemset/problem/427/C

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/graphs/SCCTarjan.h"

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

  ll ans1 = 0, ways1 = 1;

  // solve using the lambda
  SCCTarjan::scc(adj, [&](vector<int>& v) {
    int add = ( int )1e9 + 10;
    int cnt = 0;

    for (int i : v)
      if (cost[i] < add) {
        add = cost[i];
        cnt = 1;
      } else if (cost[i] == add)
        cnt++;

    ans1 += add;
    ways1 = (ways1 * cnt) % MOD;
  });

  // solve using the component IDs
  vector<int> comp = SCCTarjan::scc(adj);
  vector<ll> add(comp.size(), ( int )1e9 + 10),
   cnt(comp.size(), 1);
  ll ans2 = 0, ways2 = 1;
  int ncomps = 0;

  for (int i = 0; i < n; i++) {
    ncomps = max(ncomps, comp[i] + 1);

    if (cost[i] < add[comp[i]]) {
      add[comp[i]] = cost[i];
      cnt[comp[i]] = 1;
    } else if (cost[i] == add[comp[i]])
      cnt[comp[i]]++;
  }

  for (int i = 0; i < ncomps; i++) ans2 += add[i];
  for (int i = 0; i < ncomps; i++)
    ways2 = (ways2 * cnt[i]) % MOD;

  // show both ways work
  assert(ans1 == ans2);
  assert(ways1 == ways2);

  cout << ans1 << " " << ways1 << '\n';
}
