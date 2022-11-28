#define IGNORE // atcoder tests currently don't work due to dropbox
#define PROBLEM "https://atcoder.jp/contests/abc234/tasks/abc234_d"
#include "../../tests/TestRunner.h"
#include "../../content/data-structures/BIT.h"

void test() {
	int n, k;
	cin >> n >> k;

	BIT<int> bit(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bit.update(n - x, 1);
		if (i >= k - 1) cout << n - bit.kth(k - 1) << "\n";
	}
}
