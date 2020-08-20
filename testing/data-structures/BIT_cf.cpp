#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
struct BIT {
	vector<T> s;
	int n;
	BIT(int n) : s(n + 1), n(n) {
	}
	void update(int i, T v) {
		for (i++; i <= n; i += i & -i)
			s[i] += v;
	}
	T query(int i) {
		T ans = 0;
		for (i++; i > 0; i -= i & -i)
			ans += s[i];
		return ans;
	}
	T query(int l, int r) {
		return query(r) - query(l - 1);
	}
	int kth(T k) { // returns n if k > sum of tree
		if (k <= 0)
			return -1;
		int i = 0;
		for (int pw = 1 << __lg(n); pw; pw >>= 1)
			if (i + pw <= n && s[i + pw] < k)
				k -= s[i += pw];
		return i;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int n, q;
	cin >> n >> q;

	BIT<ll> bit(n + 1);

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bit.update(x, 1);
	}

	while (q--) {
		int i;
		cin >> i;

		if (i > 0)
			bit.update(i, 1);
		else
			bit.update(bit.kth(-i), -1);
	}

	cout << (bit.query(n) ? bit.kth(1) : 0) << '\n';
}