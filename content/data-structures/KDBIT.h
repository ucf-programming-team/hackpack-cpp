/**
 * Description: $k$-dimensional BIT. \texttt{BIT<int, N, M>} gives an $N \times M$ BIT.
 * \\ Query: \texttt{bit.query(x1, x2, y1, y2)} Update: \texttt{bit.update(x, y, delta)}
 * Time: $O(\log^k n)$
 * Status: Tested
 */

template <class T, int... Ns> struct BIT {
	T val = 0; 
	void update(T v) { val += v; }
	T query() { return val; }
};
template <class T, int N, int... Ns> struct BIT<T, N, Ns...> {
	BIT<T, Ns...> bit[N+1];
	template<class... Args> void update(int i, Args... args) {
		for (i++; i <= N; i += i & -i) bit[i].update(args...); 
	}
	template<class... Args> T query(int l, int r, Args... args) {
		T ans = 0; 
		for (r++; r; r -= r & -r) ans += bit[r].query(args...); 
		for (; l; l -= l & -l) ans -= bit[l].query(args...); 
		return ans; 
	}
};
