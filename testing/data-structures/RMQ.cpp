// tested on https://www.spoj.com/problems/RMQSQ/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/data-structures/RMQ.h"

const bool USE_LAMBDA = true;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int& x : a) cin >> x;

  // using less<int>
  if (!USE_LAMBDA) {
    RMQ<int> rmq(a);

    int q;
    cin >> q;
    while (q--) {
      int x, y;
      cin >> x >> y;
      if (y < x) swap(x, y);
      cout << rmq.query(x, y) << '\n';
    }
  }
  // using lambda to return indices in rmq
  else {
    auto cmp = [&](int x, int y) { return a[x] < a[y]; };
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    RMQ<int, decltype(cmp)> rmq(idx, cmp);

    int q;
    cin >> q;
    while (q--) {
      int x, y;
      cin >> x >> y;
      if (y < x) swap(x, y);
      cout << a[rmq.query(x, y)] << '\n';
    }
  }
}
