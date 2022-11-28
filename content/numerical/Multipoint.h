vl inv(const vl& a, int N) {
	vl b = {modpow(a[0], mod - 2)};
	int k = 1;
	for (int k = 2; k / 2 < N; k *= 2) {
		vl temp = {begin(a), sz(a) > k ? begin(a) + k : end(a)};
		temp = conv(temp, b);
		for (int i = 0; i < sz(temp); i++)
			if (temp[i]) temp[i] = mod - temp[i];
		temp[0] += 2;
		if (temp[0] >= mod) temp[0] -= mod;
		b = conv(temp, b);
		b.resize(min(k, N));
	}
	return b;
}
pair<vl, vl> div(vl& a, vl& b) {
	if (sz(a) < sz(b)) return {{}, a};
	reverse(all(a)), reverse(all(b));
	vl q = conv(a, inv(b, sz(a) - sz(b) + 1));
	q.resize(sz(a) - sz(b) + 1);
	reverse(all(a)), reverse(all(b)), reverse(all(q));
	int cap = 0;
	vl r = conv(b, q);
	rep(i, 0, sz(a)) {
		r[i] = a[i] + mod - r[i];
		if (r[i] >= mod) r[i] -= mod;
		if (r[i]) cap = i + 1;
	}
	r.resize(cap);
	return {q, r};
}
const int M = 1 << 17;
vl t[4 * M]; // about 2 sec
void build(int v, int lo, int hi, vl& x) {
	if (hi - lo == 1) // handle if negative or w/e
		t[v] = {x[lo] ? mod - x[lo] : 0, 1};
	else {
		int mid = (lo + hi) / 2;
		build(2 * v, lo, mid, x), build(2 * v + 1, mid, hi, x);
		t[v] = conv(t[2 * v], t[2 * v + 1]);
	}
}
void calc(int v, int lo, int hi, vl a, vl& ans) {
	a = div(a, t[v]).second;
	if (hi - lo == 1) {
		ans[lo] = sz(a) ? a[0] : 0;
		return;
	}
	int mid = (lo + hi) / 2;
	calc(2 * v, lo, mid, a, ans);
	calc(2 * v + 1, mid, hi, a, ans);
}
