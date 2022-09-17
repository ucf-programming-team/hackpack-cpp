const int LIM = 1e6 + 10;
vi primes;
bitset<LIM> notPrime;
int ps[LIM], ks[LIM];
ll phi[LIM];
void sieve(int n) {
  phi[1] = 1;
  for (int i = 2; i < n; i++) {
    if (!notPrime[i]) { // Define f(p^k)
      primes.push_back(i);
      ps[i] = i, ks[i] = 1; 
      phi[i] = i - 1; // EDIT HERE: f(p)
      for (ll pk = i, x = 1ll*i*i; x < n; pk *= i, x *= i) {
        ps[x] = x, ks[x] = ks[pk] + 1;
        phi[x] = phi[pk] * i; // EDIT HERE: f(p^k), k > 1
      }
    }
    for (ll j = 0, p; j < sz(primes) && (p = primes[j]) * i < n; j++) {
      ll x = i * p; 
      if (x >= n) break;
      notPrime[x] = 1;
      if (i % p == 0) {
        if (i != ps[i]) {
          ps[x] = ps[i] * p, ks[x] = ks[i] + 1;
          phi[x] = phi[i / ps[i]] * phi[ps[x]];
        }
        break;
      }
      else {
        phi[x] = phi[i] * phi[p];
        ps[x] = p, ks[x] = 1;
      }
    }
  }
}