namespace fast_suffix_array {
  /* sort suffixes of S in O(nlogn) */
  template <typename T>
  std::vector<ll> suffix_array(const std::vector<T>& S) {
    const ll n = S.size();
    std::vector<ll> order(n);
    for (ll i = 0; i < n; ++i) order[i] = n - 1 - i;

    /* stable sort of elements */
    std::stable_sort(
      order.begin(), order.end(),
      [&](const ll& a, const ll& b) { return S[a] < S[b]; });

    std::vector<ll> sa(order);
    std::vector<ll> classes(n);
    for (ll i = 0; i < n; ++i) classes[i] = S[i];

    /* sa[i] - suffix on i'th position after sorting by first
     * len elements */
    /* classes[i] - equiv class of the i'th suffix after
     * sorting by first len characters */

    for (ll len = 1; len < n; len *= 2) {
      std::vector<ll> c(classes);
      for (ll i = 0; i < n; ++i)
        classes[sa[i]] =
          i > 0 && c[sa[i - 1]] == c[sa[i]] &&
              sa[i - 1] + len < n &&
              c[sa[i - 1] + len / 2] == c[sa[i] + len / 2]
            ? classes[sa[i - 1]]
            : i;

      std::vector<ll> cnt(n);
      for (ll i = 0; i < n; ++i) cnt[i] = i;
      std::vector<ll> s(sa);
      for (ll i = 0; i < n; ++i) {
        ll s1 = s[i] - len;
        if (s1 >= 0) sa[cnt[classes[s1]]++] = s1;
      }
    }

    return sa;
  }

  template <typename T>
  std::vector<ll> lcp(const std::vector<ll>& sa,
                      const std::vector<T>& s) {
    const ll n = sa.size(), m = s.size();
    std::vector<ll> rank(n);
    for (ll i = 0; i < n; ++i) rank[sa[i]] = i;
    std::vector<ll> lcp(n);
    for (ll i = 0, h = 0; i < n; ++i) {
      if (rank[i] < n - 1) {
        for (ll j = sa[rank[i] + 1];
             std::max(i, j) + h < m && s[i + h] == s[j + h];
             ++h)
          ;
        lcp[rank[i]] = h;
        h -= h > 0;
      }
    }
    return lcp;
  }
}; // namespace fast_suffix_array
