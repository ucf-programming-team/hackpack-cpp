#include <bits/stdc++.h>

/* Sequence can be vector or string */
template <class Sequence>
struct KMP {
  typedef long long ll;

  const ll n;

  /* kmp table. */
  std::vector<ll> p;
  const Sequence needle;

  // may not work if n=1
  KMP(const Sequence& _needle)
    : needle(_needle), n(_needle.size()) {
    /* compute the table */
    p.assign(n + 1, 0);
    p[0] = -1;
    p[1] = 0;
    for (ll i = 2, k = 0; i <= n; ++i) {
      while (k > 0 && needle[k] != needle[i - 1]) k = p[k];
      p[i] = needle[k] == needle[i - 1] ? ++k : 0;
    }
  }

  std::vector<ll> find_occurences_in(
    const Sequence& haystack) const {
    std::vector<ll> locs;
    actual_kmp_search(haystack, true, locs);
    return locs;
  }

  ll count_occurences_in(const Sequence& haystack) const {
    return actual_kmp_search(haystack);
  }

private:
  /* search for the needle in the haystack. */
  ll actual_kmp_search(
    const Sequence& haystack, const bool& fill_vec = false,
    std::vector<ll>& locs = std::vector<ll>()) const {
    ll cnt = 0;
    for (ll i = 0, k = 0; i < haystack.size(); ++i) {
      while (k > 0 && needle[k] != haystack[i]) k = p[k];
      if (needle[k] == haystack[i]) ++k;
      if (k == needle.size()) {
        if (fill_vec) locs.push_back(i);
        ++cnt;
        k = p[k];
      }
    }
    return cnt;
  }
};
