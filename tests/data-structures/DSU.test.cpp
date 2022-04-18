#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../../tests/TestRunner.h"
#include "../../content/data-structures/DSU.h"

void test() {
	int n, q;
	cin >> n >> q;

	DSU dsu(n);

	while (q--) {
		int t, x, y;
		cin >> t >> x >> y;

		if (t == 0) dsu.join(x, y);
		else
			cout << dsu.same(x, y) << "\n";
	}
}
