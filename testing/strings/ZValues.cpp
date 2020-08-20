#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> zValues(string& s) {
	int n = ( int )s.length();
	vector<int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++) {
		string s;
		cin >> s;
		auto z = zValues(s);
		int ans = 0;
		for (int i = 1; i < s.length(); i++)
			ans += (s.length() - i == z[i]);
		cout << "Case " << tt << ": " << ans << '\n';
	}
}