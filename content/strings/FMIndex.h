const int LIM = 26, A = 'A';
struct FMIndex : SuffixArray {
  vector<array<int, LIM>> freq;
  array<int, LIM + 1> occ = {1};
  FMIndex(string& s): SuffixArray(s), freq(sz(s) + 2) {
    rep (i, 0, sz(sa)) {
      freq[i + 1] = freq[i];
      int p = sa[i] - 1;
      if (p >= 0) freq[i + 1][s[p] - A]++,
      occ[s[p] - A + 1]++; }
    rep (i, 0, LIM) occ[i + 1] += occ[i]; }
  int add(int i, char c) {
    return occ[c - A] + freq[i][c - A]; }
  vector<pii> query(string& q) {
    vector<pii> ret(sz(q) + 1);
    auto[L, R] = ret.back() = {0, sz(sa)};
    for (int i = sz(q) - 1; i >= 0; i--)
      ret[i] = {L = add(L, q[i]), R = add(R, q[i])};
    return ret; } };
