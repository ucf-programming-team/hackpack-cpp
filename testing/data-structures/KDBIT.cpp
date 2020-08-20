#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T, int... Ns>
struct BIT {
	T val = 0;
	void update(T v) {
		val += v;
	}
	T query() {
		return val;
	}
};
template <class T, int N, int... Ns>
struct BIT<T, N, Ns...> {
	BIT<T, Ns...> bit[N + 1];
	template <class... Args>
	void update(int i, Args... args) {
		for (i++; i <= N; i += i & -i)
			bit[i].update(args...);
	}
	template <class... Args>
	T query(int i, Args... args) {
		T ans = 0;
		for (i++; i; i -= i & -i)
			ans += bit[i].query(args...);
		return ans;
	}
	template <class... Args,
						enable_if_t<(sizeof...(Args) ==
												 2 * sizeof...(Ns))>* = nullptr>
	T query(int l, int r, Args... args) {
		return query(r, args...) - query(l - 1, args...);
	}
};

const int N = 1024;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int tests;
	cin >> tests;

	while (tests--) {
		int n;
		cin >> n;

		// this is too big for my stack locally
		BIT<ll, N, N> bit;

		while (true) {
			string t;
			cin >> t;

			if (t == "SET") {
				int x, y;
				ll d;
				cin >> x >> y >> d;

				ll old = bit.query(x, x, y, y);
				bit.update(x, y, d - old);
			}
			if (t == "SUM") {
				int x1, y1, x2, y2;
				cin >> x1 >> y1 >> x2 >> y2;
				cout << bit.query(x1, x2, y1, y2) << '\n';
			}
			if (t == "END")
				break;
		}
	}
}
