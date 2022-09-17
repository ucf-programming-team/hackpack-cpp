#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../../tests/TestRunner.h"
#include "../../content/data-structures/RMQ.h"

void test() {
	int n, q;
	cin >> n >> q;

	vector<int> a(n);
	for (auto& x : a) cin >> x;
	// test lambda comparison
	auto cmp = [&](int x, int y) { return a[x] < a[y]; };
	vector<int> idx(n);
	iota(idx.begin(), idx.end(), 0);
	RMQ<int, decltype(cmp)> rmq(idx, cmp);

	while (q--) {
		int x, y;
		cin >> x >> y;
		cout << a[rmq.query(x, y)] << "\n";
	}
}
