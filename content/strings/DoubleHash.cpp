#include <bits/stdc++.h>

typedef long long ll;

const ll MAX_N = 1e5 + 7;
const ll MODS[] = {1000000007, 1000000009};
const ll PRIME = 31;

ll pows[2][MAX_N], invs[2][MAX_N];

inline ll fastpow(const ll& base, const ll& pow,
                  const ll& MOD) {
  ll res = 1;
  for (ll n = base, exp = pow; exp;) {
    if (exp & 1) {
      res = (res * n) % MOD;
      exp--;
    } else {
      n = (n * n) % MOD;
      exp /= 2;
    }
  }
  return res;
}

struct hashboi {
  const int n;
  ll pref[2][MAX_N];

  hashboi(const std::string& str) : n(str.length()) {
    memset(pref, 0, sizeof(pref));

    for (int p = 0; p < 2; ++p) {
      for (int i = 1; i <= n; ++i) {
        ll val = cval(str[i - 1]);
        val = (val * pows[p][i]) % MODS[p];
        pref[p][i] = (pref[p][i - 1] + val) % MODS[p];
      }
    }
  }

  inline ll cval(const char& c) { return c - 'a' + 1; }

  std::pair<ll, ll> get(const int& left, const int& right) {
    assert(left <= right && right < n && left >= 0);
    std::vector<ll> ret(2);
    for (int p = 0; p < 2; ++p) {
      ret[p] = (pref[p][right + 1] - pref[p][left]) % MODS[p];
      if (ret[p] < 0) ret[p] += MODS[p];
      ret[p] = (ret[p] * invs[p][left]) % MODS[p];
    }
    return std::pair<ll, ll>{ret.front(), ret.back()};
  }
};

int main(void) {
  for (int p = 0; p < 2; ++p) {
    invs[p][0] = fastpow(pows[p][0] = 1, MODS[p] - 2, MODS[p]);
    for (int i = 1; i < MAX_N; ++i) {
      pows[p][i] = (pows[p][i - 1] * PRIME) % MODS[p];
      invs[p][i] = fastpow(pows[p][i], MODS[p] - 2, MODS[p]);
    }
  }

  // do stuff here.

  return 0;
}
