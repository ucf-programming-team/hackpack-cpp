const int LIM = 1e6 + 10;
vi primes;
bitset<LIM> notPrime;
int ps[LIM], ks[LIM];
ll f[LIM];
template<ll (*g)(int, int, int)> void sieve(int n = LIM) {
	f[1] = 1;
	for (int i = 2; i < n; i++) {
		if (!notPrime[i]) {
			primes.push_back(i);
			ps[i] = i, ks[i] = 1;
			f[i] = g(i, i, 1);
			for (ll pk = i, x = 1ll * i * i; x < n;
					 pk *= i, x *= i) {
				ps[x] = x, ks[x] = ks[pk] + 1;
				f[x] = g(x, i, ks[x]);
			}
		}
		for (ll j = 0, p;
				 j < sz(primes) && (p = primes[j]) * i < n; j++) {
			ll x = i * p;
			if (x >= n) break;
			notPrime[x] = 1;
			if (i % p == 0) {
				if (i != ps[i]) {
					ps[x] = ps[i] * p, ks[x] = ks[i] + 1;
					f[x] = f[i / ps[i]] * f[ps[x]];
				}
				break;
			} else {
				f[x] = f[i] * f[p];
				ps[x] = p, ks[x] = 1;
			}
		}
	}
}
