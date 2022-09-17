template<int MOD, int RT> struct mint {
  using mr = const mint&;
  int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
  mint(ll _v = 0) { v = int((-MOD < _v && _v < MOD) 
    ? _v : _v % MOD); if (v < 0) v += MOD; }
  mint& operator+=(mr o) { if ((v += o.v) >= MOD) v -= MOD;
    return *this; }
  mint& operator-=(mr o) { if ((v -= o.v) < 0) v += MOD; 
    return *this; }
  mint& operator*=(mr o) { v = int(ll(v) * o.v % MOD); 
    return *this; }
  mint& operator/=(mr o) { return (*this) *= inv(o); }
  friend mint pow(mint a, ll p) {
    mint ans = 1; assert(p >= 0);
    for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
    return ans; }
  friend mint inv(mr a) { assert(a.v != 0); 
    return pow(a,MOD-2); }
  friend mint operator+(mint a, mr b) { return a += b; }
  friend mint operator-(mint a, mr b) { return a -= b; }
  friend mint operator*(mint a, mr b) { return a *= b; }
  friend mint operator/(mint a, mr b) { return a /= b; }
  bool operator==(mr o) const { return v == o.v; }
  friend bool operator!=(mr a, mr b) { return !(a == b); }
  friend bool operator<(mr a, mr b) { return a.v < b.v; }
  mint operator-() const { return mint(-v); }
  mint& operator++() { return *this += 1; }
  mint& operator--() { return *this -= 1; }
  friend istream& operator>>(istream& is, mint& a) { 
    return is >> a.v; }
  friend ostream& operator<<(ostream& os, const mint& a) { 
    return os << a.v; }
  static constexpr mint rt() { return RT; } // primitive root for FFT
};
using mi = mint<MOD,5>; // 5 is primitive root for both common mods