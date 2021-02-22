/**
 * Description: Factorize numbers using Pollard's Rho
 * Returns a vector of prime factors
*/

// if __int128 is unavailable, use binary multiplication like
// fast pow
inline ll mult(ll a, ll b, ll mod) {
  return ( __int128 )a * b % mod;
}

inline ll f(ll x, ll c, ll mod) {
  return (mult(x, x, mod) + c) % mod;
}

inline ll pow(ll a, ll b, ll mod) {
  ll res = 1;
  while (b) {
    if (b & 1) res = mult(res, a, mod);
    a = mult(a, a, mod);
    b >>= 1;
  }
  return res;
}

int miller(ll d, ll n) {
  ll a = 2 + rand() % (n - 4);
  ll x = pow(a, d, n);
  if (x == 1 || x == n - 1) return 1;
  while (d != n - 1) {
    x = mult(x, x, n);
    d <<= 1;
    if (x == 1) return 0;
    if (x == n - 1) return 1;
  }
  return 0;
}

int isProbablePrime(ll n, ll k) {
  if (n <= 1 || n == 4) return 0;
  if (n <= 3) return 1;

  ll d = n - 1;
  while (!(d & 1)) d >>= 1;

  while (k--)
    if (!miller(d, n)) return 0;
  return 1;
}

ll brent(ll n, ll x0 = 2, ll c = 1) {
  if (isProbablePrime(n, 20)) return n;
  ll x = x0;
  ll g = 1;
  ll q = 1;
  ll xs, y;

  int m = 128;
  int l = 1;
  while (g == 1) {
    y = x;
    for (int i = 1; i < l; i++) x = f(x, c, n);
    int k = 0;
    while (k < l && g == 1) {
      xs = x;
      for (int i = 0; i < m && i < l - k; i++) {
        x = f(x, c, n);
        q = mult(q, abs(y - x), n);
      }
      g = __gcd(q, n);
      k += m;
    }
    l *= 2;
  }
  if (g == n) {
    do {
      xs = f(xs, c, n);
      g = __gcd(abs(xs - y), n);
    } while (g == 1);
  }
  return g;
}
const int primes[] = {2, 3, 5, 7, 11, 13, 17};

vector<ll> factor(ll x) {
  vector<ll> ans(0);

  for (auto p : primes) {
    while (x % p == 0) {
      x /= p;
      ans.emplace_back(p);
    }
  }
  while (x != 1) {
    ll curf = brent(x);
    ans.emplace_back(curf);
    x /= curf;
  }
  return ans;
}
