#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_PR = 100'000'000;
bitset<MAX_PR> isprime;
vector<int> primeSieve(int lim) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i*i < lim; i += 2) if (isprime[i])
		for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
	vector<int> pr;
	for (int i = 2; i < lim; i++) if (isprime[i]) pr.push_back(i);
	return pr;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int n, q;
	cin >> n >> q;

	vector<int> primes = primeSieve(n + 1);
	cout << primes.size() << '\n';

	for (int i = 0; i < q; i++)
	{
		int x;
		cin >> x;
		cout << isprime[x] << '\n';
	}
}