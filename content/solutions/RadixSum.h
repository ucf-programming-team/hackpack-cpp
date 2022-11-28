#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define rep(a, b, c) for (int a = b; a < c; a++)
#define sz(x) (int)x.size()
using namespace std;
using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using ull = unsigned long long;
const int N = ll(1e5);
const int L = 5;
const ull INV =
	6723469279985657373ULL; // inverse of 5^5 mod 2^64
const ull MOD = 1LL << 58;
// if a is a root of p(x) = x^4 - x^3 + x^2 - x + 1,
// then a is a primitive 10th root of unity (a^10 = 1, and no smaller power works)
struct Poly {
	array<ull, L> a = {};
	Poly() {}
	Poly(int i, ull v = 1) { a[i] = v; }
	Poly operator+(const Poly& o) const {
		Poly ret;
		for (int i = 0; i < L; i++) ret.a[i] = a[i] + o.a[i];
		return ret;
	}
	Poly operator*(const Poly& o) const {
		array<ull, 2 * L> temp = {};
		for (int i = 0; i < L; i++)
			for (int j = 0; j < L; j++) temp[i + j] += a[i] * o.a[j];
		// mod by x^4 - x^3 + x^2 - x + 1
		for (int i = 2 * L - 1; i >= 4; i--) {
			ll v = temp[i];
			temp[i - 0] -= v;
			temp[i - 1] += v;
			temp[i - 2] -= v;
			temp[i - 3] += v;
			temp[i - 4] -= v;
		}
		Poly ret;
		for (int i = 0; i < L; i++) ret.a[i] = temp[i];
		return ret;
	}
	friend ostream& operator<<(ostream& os, const Poly& p) {
		for (int i = L - 1; i >= 0; i--)
			if (p.a[i]) os << p.a[i] << " ";
		return os;
	}
};
vector<Poly> pws;
vector<Poly> transform(const vector<Poly>& a, bool inv) {
	int n = a.size();
	int nb = n / 10;
	if (n == 1) return a;
	vector<Poly> c(n);
	vector<vector<Poly>> b(10, vector<Poly>(nb));
	for (int i = 0; i < n; i++) b[i / nb][i % nb] = a[i];
	for (int i = 0; i < 10; i++) b[i] = transform(b[i], inv);
	int shift = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int pw = (i * j) % 10;
			if (inv) pw = (10 - pw) % 10;
			Poly root = Poly(pw % 5, pw / 5 ? -1 : 1);
			for (int k = 0; k < nb; k++)
				c[shift + k] = c[shift + k] + b[j][k] * root;
		}
		shift += nb;
	}
	return c;
}
Poly binpow(Poly a, int n) {
	Poly ret(0, 1);
	for (; n; n /= 2, a = a * a)
		if (n & 1) ret = a * ret;
	return ret;
}
void solve() {
	vector<Poly> f(N);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		f[x] = f[x] + Poly(0, 1);
	}
	f = transform(f, false);
	for (int i = 0; i < N; i++) f[i] = binpow(f[i], n);
	f = transform(f, true);
	for (int i = 0; i < n; i++) {
		ull ans = f[i].a[0];
		// "divide" by n
		ans *= INV;
		ans >>= 5;
		ans %= 1ULL << 58;
		cout << ans << '\n';
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	// int t; cin >> t; while (t--)
	solve();
	return 0;
}
