template<class T, T (*e)(), T (*op)(T, T), class F, F (*id)(),
	T (*onto)(F, T), F (*comp)(F, F)>
struct lazy_segtree {
	int N, log, S;
	vector<T> d;
	vector<F> lz;
	lazy_segtree(const vector<T>& v):
		N(sz(v)), log(__lg(2 * N - 1)), S(1 << log), d(2 * S, e()),
		lz(S, id()) {
		for (int i = 0; i < N; i++) d[S + i] = v[i];
		for (int i = S - 1; i >= 1; i--) pull(i);
	}
	void apply(int k, F f) {
		d[k] = onto(f, d[k]);
		if (k < S) lz[k] = comp(f, lz[k]);
	}
	void push(int k) {
		apply(2 * k, lz[k]), apply(2 * k + 1, lz[k]), lz[k] = id();
	}
	void push(int l, int r) {
		int zl = __builtin_ctz(l), zr = __builtin_ctz(r);
		for (int i = log; i > min(zl, zr); i--) {
			if (i > zl) push(l >> i);
			if (i > zr) push((r - 1) >> i);
		}
	}
	void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
	void set(int p, T x) {
		p += S;
		for (int i = log; i >= 1; i--) push(p >> i);
		for (d[p] = x; p /= 2;) pull(p);
	}
	T query(int l, int r) {
		if (l == r) return T{};
		push(l += S, r += S);
		T vl = e(), vr = e();
		for (; l < r; l /= 2, r /= 2) {
			if (l & 1) vl = op(vl, d[l++]);
			if (r & 1) vr = op(d[--r], vr);
		}
		return op(vl, vr);
	}
	void update(int l, int r, F f) {
		if (l == r) return;
		push(l += S, r += S);
		for (int a = l, b = r; a < b; a /= 2, b /= 2) {
			if (a & 1) apply(a++, f);
			if (b & 1) apply(--b, f);
		}
		int zl = __builtin_ctz(l), zr = __builtin_ctz(r);
		for (int i = min(zl, zr) + 1; i <= log; i++) {
			if (i > zl) pull(l >> i);
			if (i > zr) pull((r - 1) >> i);
		}
	}
};
