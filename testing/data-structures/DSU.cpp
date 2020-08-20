#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct DSU {
	vector<int> s;
	DSU(int n) : s(n, -1) {
	}
	int find(int i) {
		return s[i] < 0 ? i : s[i] = find(s[i]);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b)
			return false;
		if (s[a] > s[b])
			swap(a, b);
		s[a] += s[b], s[b] = a;
		return true;
	}
	int size(int i) {
		return -s[find(i)];
	}
	bool same(int a, int b) {
		return find(a) == find(b);
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int n, q;
	cin >> n >> q;

	DSU dsu(n);

	while (q--) {
		string t;
		int a, b;
		cin >> t >> a >> b;

		if (t == "=")
			dsu.join(a, b);
		else
			cout << (dsu.same(a, b) ? "yes\n" : "no\n");
	}
}