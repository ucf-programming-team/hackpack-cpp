/*	Prefix sum of multiplicative functions :
		p_f : the prefix sum of f (x) (1 <= x <= th).
		p_g : the prefix sum of g (x) (0 <= x <= N).
		p_c : the prefix sum of f * g (x) (0 <= x <= N).
		th : the thereshold, generally should be n ^ (2 / 3).
*/
struct prefix_mul {
	typedef long long (*func) (long long);
	func p_f, p_g, p_c;
	long long n, th;
	std::unordered_map <long long, long long> mem;
	prefix_mul (func p_f, func p_g, func p_c) : p_f (p_f), p_g (p_g), p_c (p_c) {}
	long long calc (long long x) {
		if (x <= th) return p_f (x);
		auto d = mem.find (x);
		if (d != mem.end ()) return d -> second;
		long long ans = 0;
		for (long long i = 2, la; i <= x; i = la + 1) {
			la = x / (x / i);
			ans = ans + (p_g (la) - p_g (i - 1) + mod) * calc (x / i);
		}
		ans = p_c (x) - ans; ans = ans / inv;
		return mem[x] = ans;
	}
	long long solve (long long n, long long th) {
		if (n <= 0) return 0;
		prefix_mul::n = n; prefix_mul::th = th;
		inv = p_g (1);
		return calc (n); 
	}
};
