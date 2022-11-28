/**
 * Description: Struct for representing fractions/rationals.
 * All ops are $O(\log N)$ due to GCD in constructor.
 * Uses cross multiplication.
 */
template<class T> struct Q {
	T a, b;
	Q(T p, T q = 1) {
		T g = gcd(p, q);
		a = p / g;
		b = q / g;
		if (b < 0) a = -a, b = -b;
	}
	T gcd(T x, T y) const { return __gcd(x, y); }
	Q operator+(const Q& o) const {
		return {a * o.b + o.a * b, b * o.b};
	}
	Q operator-(const Q& o) const {
		return *this + Q(-o.a, o.b);
	}
	Q operator*(const Q& o) const { return {a * o.a, b * o.b}; }
	Q operator/(const Q& o) const { return *this * Q(o.b, o.a); }
	Q recip() const { return {b, a}; }
	int signum() const { return (a > 0) - (a < 0); }
	bool operator<(const Q& o) const {
		return a * o.b < o.a * b;
	}
	friend ostream& operator<<(ostream& cout, const Q& o) {
		return cout << o.a << "/" << o.b;
	}
};
