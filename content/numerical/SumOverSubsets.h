// in place sum over subsets (give desc.)
// works with vector, array, and std::array
template<class Arr> void sos(Arr& f, int n, bool inv = 0) {
	for (int i = 0, b = 1; i < n; i++, b *= 2)
		rep(mask, 0, 1 << n) if (mask & b) f[mask] +=
			inv ? -f[mask ^ b] : f[mask ^ b];
}
template<class T>
vector<T> conv(const vector<T>& a, const vector<T>& b) {
	int n = __lg(sz(a)), len = 1 << n;
	vector<vector<T>> f(n + 1, vector<T>(len)), g = f, h = f;
	rep(mask, 0, len) {
		int pc = __builtin_popcount(mask);
		f[pc][mask] = a[mask], g[pc][mask] = b[mask];
	}
	rep(i, 0, n + 1) sos(f[i], n), sos(g[i], n);
	rep(mask, 0, len) rep(i, 0, n + 1) rep(j, 0, i + 1)
		h[i][mask] += f[j][mask] * g[i - j][mask];
	rep(i, 0, n + 1) sos(h[i], n, 1);
	vector<T> c(len);
	rep(mask, 0, len) c[mask] =
		h[__builtin_popcount(mask)][mask];
	return c;
}