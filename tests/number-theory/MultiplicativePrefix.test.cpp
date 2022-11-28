#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"
#include "../../tests/TestRunner.h"

const ll mod = 998244353;
ll binpow(ll a, ll n) {
	ll ans = 1;
	for (; n > 0; n /= 2, a = a * a % mod)
		if (n & 1) ans = a * ans % mod;
	return ans;
}

#include "../../content/number-theory/MultiplicativePrefixSum.h"
#include "../../content/number-theory/MultiplicativeSieve.h"

ll phi(int n, int p, int k) { return n / p * (p - 1); }
ll p_phi(ll n) { return f[n]; }
ll p_g(ll n) { return n % mod; }
const ll inv2 = binpow(2, mod - 2);
ll p_c(ll n) {
	n %= mod;
	return n * (n + 1) % mod * inv2 % mod;
}

void test() {
	sieve<phi>();
	for (int i = 1; i < LIM; i++) {
		f[i] += f[i - 1];
		if (f[i] >= mod) f[i] -= mod;
	}

	prefix_mul<p_phi, p_g, p_c, LIM> x;
	ll n;
	cin >> n;

	cout << x.solve(n) << "\n";
}
