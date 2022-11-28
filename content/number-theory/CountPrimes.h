/**
 * Author: lightseba
 * Description: Count primes in $O(N^\frac{3}{4})$.
 */
const int SQN = 320'000;
bool notPrime[SQN];
ll countprimes(ll n) {
	vector<ll> divs;
	for (ll i = 1; i * i <= n; i++) {
		divs.push_back(i);
		divs.push_back(n / i);
	}
	sort(all(divs));
	divs.erase(unique(all(divs)), end(divs));
	vector<ll> dp(sz(divs));
	for (int i = 0; i < sz(divs); i++) dp[i] = divs[i] - 1;
	ll sq = sqrt(n), sum = 0;
	auto idx = [&](ll x) -> int {
		return x <= sq ? x - 1 : (sz(divs) - n / x);
	};
	for (ll p = 2; p * p <= n; p++)
		if (!notPrime[p]) {
			ll p2 = p * p;
			for (ll i = sz(divs) - 1; i >= 0 && divs[i] >= p2; i--)
				dp[i] -= dp[idx(divs[i] / p)] - sum;
			sum += 1;
			for (ll i = p * p; i < SQN && i * i <= n; i += p)
				notPrime[i] = 1;
		}
	return dp.back();
}
