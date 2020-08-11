struct DSU {
	vector<int> s;
	DSU(int n): s(n, -1) { }
	int find(int i) { return s[i] < 0 ? i : s[i] = find(s[i]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (s[a] > s[b]) swap(a, b);
		s[a] += s[b], s[b] = a;
		return true;
	}
	int size(int i) { return -s[find(i)]; }
	bool same(int a, int b) { return find(a) == find(b); }
};
