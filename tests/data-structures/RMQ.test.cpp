#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../../tests/TestRunner.h"
#include "../../content/data-structures/RMQ.h"

void test() {
  int n, q;
  cin >> n >> q;
  
  vector<int> a(n);
  for (auto& x : a) cin >> x;
  RMQ<int> rmq(a);

  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << rmq.query(x, y-1) << "\n";
  }
}
