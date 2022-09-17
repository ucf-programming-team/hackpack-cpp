#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../../tests/TestRunner.h"
#include "../../content/data-structures/BIT.h"

void test() {
	int n, q;
	cin >> n >> q;

	BIT<ll> bit(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bit.update(i, x);
	}

	while (q--) {
		int t, x, y;
		cin >> t >> x >> y;

		if (t == 0) bit.update(x, y);
		else
			cout << bit.query(x, y) << "\n";
	}
}
