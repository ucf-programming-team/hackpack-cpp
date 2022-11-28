#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define sz(x) int(x.size())
#define rep(a, b, c) for (int a = (b); a < (c); a++)
typedef long long ll;
typedef vector<int> vi;
const ll mod = 998244353;
template<int MOD, int RT> struct mint {
	using mr = const mint&;
	int v;
	explicit operator int() const {
		return v;
	} // explicit -> don't silently convert to int
	mint(ll _v = 0) {
		v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD;
	}
	mint& operator+=(mr o) {
		if ((v += o.v) >= MOD) v -= MOD;
		return *this;
	}
	mint& operator-=(mr o) {
		if ((v -= o.v) < 0) v += MOD;
		return *this;
	}
	mint& operator*=(mr o) {
		v = int(ll(v) * o.v % MOD);
		return *this;
	}
	mint& operator/=(mr o) { return (*this) *= inv(o); }
	friend mint pow(mint a, ll p) {
		mint ans = 1;
		assert(p >= 0);
		for (; p; p /= 2, a *= a)
			if (p & 1) ans *= a;
		return ans;
	}
	friend mint inv(mr a) {
		assert(a.v != 0);
		return pow(a, MOD - 2);
	}
	friend mint operator+(mint a, mr b) { return a += b; }
	friend mint operator-(mint a, mr b) { return a -= b; }
	friend mint operator*(mint a, mr b) { return a *= b; }
	friend mint operator/(mint a, mr b) { return a /= b; }
	bool operator==(mr o) const { return v == o.v; }
	friend bool operator!=(mr a, mr b) { return !(a == b); }
	friend bool operator<(mr a, mr b) { return a.v < b.v; }
	mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
	friend istream& operator>>(istream& is, mint& a) {
		return is >> a.v;
	}
	friend ostream& operator<<(ostream& os, const mint& a) {
		return os << a.v;
	}
	static constexpr mint rt() {
		return RT;
	} // primitive root for FFT
};
using mi =
	mint<mod, 5>; // 5 is primitive root for both common mods
const int LIM = 4641588;
int primes[LIM], np = 0;
bitset<LIM> notPrime;
int ps[LIM], ks[LIM];
mi phi[LIM];
void sieve(int n) {
	phi[0] = 0, phi[1] = 1;
	for (int i = 2; i < n; i++) {
		if (!notPrime[i]) { // Define f(p^k)
			primes[np++] = i;
			ps[i] = i, ks[i] = 1;
			phi[i] = i - 1; // EDIT HERE: f(p)
			for (ll pk = i, x = 1ll * i * i; x < n;
					 pk *= i, x *= i) {
				ps[x] = x, ks[x] = ks[pk] + 1;
				phi[x] = phi[pk] * i; // EDIT HERE: f(p^k), k > 1
			}
		}
		for (ll j = 0, p; j < np && (p = primes[j]) * i < n; j++) {
			ll x = i * p;
			if (x >= n) break;
			notPrime[x] = 1;
			if (i % p == 0) {
				if (i != ps[i]) {
					ps[x] = ps[i] * p, ks[x] = ks[i] + 1;
					phi[x] = phi[i / ps[i]] * phi[ps[x]];
				}
				break;
			} else {
				phi[x] = phi[i] * phi[p];
				ps[x] = p, ks[x] = 1;
			}
		}
	}
}
const int KEEP = 2500;
mi dp[KEEP];
bool saved[KEEP];
/*    Prefix sum of multiplicative functions :
    p_f : the prefix sum of f (x) (1 <= x <= th).
    p_g : the prefix sum of g (x) (0 <= x <= N).
    p_c : the prefix sum of f * g (x) (0 <= x <= N).
    th : the thereshold, generally should be n ^ (2 / 3).
*/
struct prefix_mul {
	typedef mi (*func)(mi);
	func p_f, p_g, p_c;
	ll n, th;
	mi inv;
	unordered_map<ll, mi> mem;
	prefix_mul(func p_f, func p_g, func p_c):
		p_f(p_f), p_g(p_g), p_c(p_c) {}
	mi calc(ll x, ll io) {
		if (x <= th) return p_f(x);
		if (saved[io]) return dp[io];
		mi ans = 0;
		for (ll i = 2, la; i <= x; i = la + 1) {
			la = x / (x / i);
			ans += (p_g(la) - p_g(i - 1)) * calc(x / i, i * io);
		}
		ans = (p_c(x) - ans) * inv;
		saved[io] = 1;
		return dp[io] = ans;
	}
	mi solve(ll n, ll th) {
		if (n <= 0) return 0;
		prefix_mul::n = n;
		prefix_mul::th = th;
		fill(all(saved), 0);
		inv = 1 / p_g(1);
		return calc(n, 1);
	}
};
const mi INV2 = 499122177;
mi phi_f(mi n) { return phi[n.v]; }
mi ONE(mi n) { return n; }
mi Id(mi n) { return n * (n + 1) * INV2; }
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	sieve(LIM);
	rep(i, 2, LIM) phi[i] += phi[i - 1];
	prefix_mul lmao(phi_f, ONE, Id);
	ll n;
	cin >> n;
	cout << lmao.solve(n, LIM - 1) << "\n";
	return 0;
}
