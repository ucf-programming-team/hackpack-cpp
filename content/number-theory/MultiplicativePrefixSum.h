/*	Prefix sum of multiplicative functions :
		p_f : the prefix sum of f (x) (1 <= x <= th).
		p_g : the prefix sum of g (x) (0 <= x <= N).
		p_c : the prefix sum of f * g (x) (0 <= x <= N).
		th : the thereshold, generally should be n ^ (2 / 3).
*/
typedef ll (*func)(ll);
template<func p_f, func p_g, func p_c, ll TH>
struct prefix_mul {
	ll n, inv;
	unordered_map<ll, ll> mem;
	ll calc(ll x) {
		if (x < TH) return p_f(x);
		auto it = mem.find(x);
		if (it != mem.end()) return it->second;
		ll ans = 0;
		for (ll i = 2, la; i <= x; i = la + 1) {
			la = x / (x / i);
			ans = (ans + (p_g(la) - p_g(i-1) + mod) * calc(x/i)) % mod;
		}
		ans = (p_c(x) - ans + mod) * inv % mod;
		return mem[x] = ans;
	}
	ll solve (ll n) {
		if (n <= 0) return 0;
    this->n = n;
		inv = binpow(p_g(1), mod - 2);
		return calc(n); 
	}
};
