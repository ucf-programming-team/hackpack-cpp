// Tested on NEERC 2015 Northern: Journey to the "The World's
// Start" https://codeforces.com/gym/100801
#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
using ll = long long;

#include "../../content/data-structures/MonotonicQueue.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  freopen("journey.in", "r", stdin);
  freopen("journey.out", "w", stdout);

  int n;
  ll t;
  cin >> n >> t;

  vector<ll> p(n), d(n);

  for (int i = 1; i < n; i++) cin >> p[i];
  for (int i = 1; i < n - 1; i++) cin >> d[i];

  auto go = [&](int r) {
    monotonic_queue<ll> q;
    q.push(0);

    for (int i = n - 2; i >= 0; i--) {
      q.push(d[i] + q.min());
      while (q.size() > r) q.pop();
    }

    return q.back() + n - 1;
  };

  int lo = 1, hi = n - 1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;

    if (go(mid) <= t)
      hi = mid;
    else
      lo = mid + 1;
  }

  cout << *min_element(p.begin() + hi, p.end()) << '\n';
}
