/**
 * Description: Safer struct for representing
 * fractions/rationals. Comparison is 100\% overflow safe;
 * other ops are safer but can still overflow. All ops are
 * $O(\log N)$.
 */
template<class T> struct QO {
	T a, b;
	QO(T p, T q = 1) {
		T g = gcd(p, q);
		a = p / g;
		b = q / g;
		if (b < 0) a = -a, b = -b;
	}
	T gcd(T x, T y) const { return __gcd(x, y); }
	QO operator+(const QO& o) const {
		T g = gcd(b, o.b), bb = b / g, obb = o.b / g;
		return {a * obb + o.a * bb, b * obb};
	}
	QO operator-(const QO& o) const {
		return *this + QO(-o.a, o.b);
	}
	QO operator*(const QO& o) const {
		T g1 = gcd(a, o.b), g2 = gcd(o.a, b);
		return {(a / g1) * (o.a / g2), (b / g2) * (o.b / g1)};
	}
	QO operator/(const QO& o) const {
		return *this * QO(o.b, o.a);
	}
	QO recip() const { return {b, a}; }
	int signum() const { return (a > 0) - (a < 0); }
	static bool lessThan(T a, T b, T x, T y) {
		if (a / b != x / y) return a / b < x / y;
		if (x % y == 0) return false;
		if (a % b == 0) return true;
		return lessThan(y, x % y, b, a % b);
	}
	bool operator<(const QO& o) const {
		if (this->signum() != o.signum() || a == 0) return a < o.a;
		if (a < 0) return lessThan(abs(o.a), o.b, abs(a), b);
		else return lessThan(a, b, o.a, o.b);
	}
	friend ostream& operator<<(ostream& cout, const QO& o) {
		return cout << o.a << "/" << o.b;
	}
};
