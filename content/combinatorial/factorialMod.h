int factmod(int n, int p) {
  vector<int> f(p);
  f[0] = 1;
  for (int i = 1; i < p; i++) f[i] = f[i - 1] * i % p;
  int res = 1;
  while (n > 1) {
    if ((n / p) % 2) res = p - res;
    res = res * f[n % p] % p;
    n /= p; }
  return res; }
int multiplicityFactorial(int n, int p) {
  int count = 0;
  do { n /= p; count += n; } while (n);
  return count; }
