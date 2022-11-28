/**
 * Source: https://codeforces.com/blog/entry/61203
 * Description: Maps points on a $2^k \times 2^k$ matrix
 * to their index on the Hilbert curve.
 */
const int logn = 21, maxn = 1 << logn;
ll hilbert(int x, int y) {
	ll d = 0;
	for (int s = 1 << (logn - 1); s > 0; s >>= 1) {
		int rx = x & s, ry = y & s;
		d = d << 2 | rx * 3 ^ ry;
		if (ry == 0) {
			if (rx != 0) {
				x = maxn - x;
				y = maxn - y;
			}
			swap(x, y);
		}
	}
	return d;
}
