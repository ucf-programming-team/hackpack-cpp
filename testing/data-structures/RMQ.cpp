// tested on https://www.spoj.com/problems/RMQSQ/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/data-structures/RMQ.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int& x : a) cin >> x;

  RMQ<int, less<int>> rmq(a);

  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    if (y < x) swap(x, y);
    cout << rmq.query(x, y) << '\n';
  }
}
