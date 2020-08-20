// standard prime sieve, O(n log log n)
// can sieve up to 1e8 ish
// returns all primes strictly less than lim

const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vector<int> primeSieve(int lim) {
  isprime.set();
  isprime[0] = isprime[1] = 0;
  for (int i = 4; i < lim; i += 2) isprime[i] = 0;
  for (int i = 3; i * i < lim; i += 2)
    if (isprime[i])
      for (int j = i * i; j < lim; j += i * 2) isprime[j] = 0;
  vector<int> pr;
  for (int i = 2; i < lim; i++)
    if (isprime[i]) pr.push_back(i);
  return pr;
}
