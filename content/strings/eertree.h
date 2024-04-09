/**
 * Description: For each unique palindromic substring, computes suffix link.
 * 	compute() calculates the frequencies of each palindrome in $O(|s|)$
 * Status: tested on https://codeforces.com/gym/104857/problem/C
 */
struct eertree {
  vi s, rem;
  struct node {
    int len = 0, link = 0, from = 0, cnt = 0, freq = 0;
    int visit = -1;
    array<int, 26> to{}; };
  vector<node> T;
  int last, n;
  int head = 1, overall = 0;
  eertree(): s(1), T(2), rem(2, -1), last(0), n(1) {
    s.reserve(1e6 + 5), T.reserve(1e6 + 5),
    rem.reserve(1e6 + 5);
    s[0] = -1;
    T[0].link = T[1].link = 1;
    T[1].len = -1;
    T[0].cnt = T[1].cnt = 1; }
  int get_link(int v) {
    while (s[n - T[v].len - 2] != s[n - 1]) v = T[v].link;
    return v; }
  void update(int u, int p) {
    if (u < 2) return;
    auto& x = T[u];
    if (p > x.visit) x.visit = p;
    if (!x.cnt && (rem[x.visit] == -1 || T[rem[x.visit]].len < x.len))
      rem[x.visit] = u; }
  void add(char ch) {
    int c = ch - 'a';
    s.push_back(c), rem.push_back(0);
    n++;
    last = get_link(last);
    if (T[last].to[c] == 0) {
      auto& nd = T.emplace_back();
      nd.len = T[last].len + 2;
      nd.link = T[get_link(T[last].link)].to[c];
      nd.from = last;
      T[last].to[c] = sz(T) - 1;
      T[nd.from].cnt++, T[nd.link].cnt++;
      overall++; }
    last = T[last].to[c];
    T[last].freq++;
    update(last, n - T[last].len); }
  void pop() {
    int node = rem[head], c = s[head];
    s[head++] = -1;
    if (node < 2) return;
    auto& nd = T[node];
    if (nd.cnt || nd.visit != head - 1) return;
    if (n - head + 1 == T[last].len) last = T[last].link;
    overall--;
    T[nd.from].to[c] = 0;
    T[nd.from].cnt--, T[nd.link].cnt--;
    update(nd.from, head);
    update(nd.link, head - 1 + nd.len - T[nd.link].len); }
  void compute() {
    for (int i = sz(T) - 1; i >= 0; i--) {
      T[T[i].link].freq += T[i].freq; } } };
