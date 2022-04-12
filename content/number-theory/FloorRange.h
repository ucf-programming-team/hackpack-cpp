for (int i = 1, la; i <= n; i = la + 1) {
	la = n / (n / i);
	//n / x yields the same value for i <= x <= la.
}