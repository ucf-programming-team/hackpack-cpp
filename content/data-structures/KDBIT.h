/**
 * Description: $k$-dimensional BIT. \texttt{BIT<int, N, M>}
 * gives an $N \times M$ BIT. Query \texttt{bit.query(x1, x2, y1, y2)} Update \texttt{bit.update(x, y, delta)} 
 * Time: $O(\log^k n)$ 
 * Status: Tested
 */
template<class T, int... Ns> struct BIT {
	T val = 0;
	void update(T v) { val += v; }
	T query() { return val; }
};
template<class T, int N, int... Ns> struct BIT<T, N, Ns...> {
	BIT<T, Ns...> bit[N + 1];
	// map<int, BIT<T, Ns...>> bit; // if the mem use is too high
	template<class... Args> void update(int i, Args... args) {
		for (i++; i <= N; i += i & -i) bit[i].update(args...);
	}
	template<class... Args> T query(int i, Args... args) {
		T ans = 0;
		for (i++; i; i -= i & -i) ans += bit[i].query(args...);
		return ans;
	}
	template<class... Args,
		enable_if_t<(sizeof...(Args) == 2 * sizeof...(Ns))>* =
			nullptr>
	T query(int l, int r, Args... args) {
		return query(r, args...) - query(l - 1, args...);
	}
};
