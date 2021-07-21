static class BIT {
	int n, tree[];
	public BIT(int N) {
		n = N;  tree = new int[N + 1];
	}
	void update(int i, int val) {
		for (i++; i <= n; i += i & -i) tree[i] += val;
	}
	int read(int i) {
		int sum = 0;
		for (i++; i > 0; i -= i & -i) sum += tree[i];
		return sum;
	}
	// query sum of [l, r] inclusive
	int query(int l, int r) { return read(r) - read(l - 1); }
	// if the BIT is a freq array, returns the index of the
	// kth item (0-indexed), or n if there are <= k items.
	int getKth(int k) {
		if (k < 0) return -1;
		int i = 0;
		for (int pw = Integer.highestOneBit(n); pw > 0; pw >>= 1)
			if (i + pw <= n && tree[i + pw] <= k) k -= tree[i += pw];
		return i;
	}
}
