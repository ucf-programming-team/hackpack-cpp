// segmented prime sieve
// much faster than the normal sieve, can do up to 1e9 in 1.5 s
// returns all primes strictly less than LIM

const int LIM = 1e8;
bitset<LIM> isPrime;
vector<int> primeSieve() {
	const int S = round(sqrt(LIM)), R = LIM / 2;
	vector<int> pr = {2}, sieve(S + 1);
	pr.reserve(int(LIM / log(LIM) * 1.1));
	vector<pair<int, int>> cp;
	for (int i = 3; i <= S; i += 2)
		if (!sieve[i]) {
			cp.push_back({i, i * i / 2});
			for (int j = i * i; j <= S; j += 2 * i)
				sieve[j] = 1;
		}
	for (int L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto& [p, idx] : cp)
			for (int i = idx; i < S + L; idx = (i += p))
				block[i - L] = 1;
		for (int i = 0; i < min(S, R - L); i++)
			if (!block[i])
				pr.push_back((L + i) * 2 + 1);
	}
	for (int i : pr)
		isPrime[i] = 1;
	return pr;
}
