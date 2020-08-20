#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T, class Compare = less<T>>
struct RMQ {
	vector<vector<T>> t;
	Compare cmp;
	RMQ(vector<T>& a) : t(__lg(a.size()) + 1, a) {
		int n = a.size(), lg = __lg(n);
		for (int k = 1, len = 1; k <= lg; k++, len <<= 1)
			for (int i = 0; i + 2 * len - 1 < n; i++)
				t[k][i] = min(t[k - 1][i], t[k - 1][i + len], cmp);
	}
	T query(int a, int b) {
		int k = __lg(b - a + 1), len = 1 << k;
		return min(t[k][a], t[k][b - len + 1], cmp);
	}
};

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