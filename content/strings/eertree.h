const int A = 26;
struct eertree {
  vector<int> s, len, link, slink, diff;
  vector<vector<int>> dfa;
  int size, last, n;
  eertree() {}
  eertree(int N):
    n(0), last(0), s(N + 2), len(N + 2), link(N + 2),
    slink(N + 2), diff(N + 2), dfa(A, vector<int>(N + 2)) {
    s[n++] = len[1] = -1;
    link[0] = link[1] = 1;
    size = 2;
  }
  int get_link(int v) {
    while(s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
  }
  void extend(char cc) {
    int c = cc - 'a';
    s[n++] = c;
    last = get_link(last);
    if(!dfa[c][last]) {
      int u = size++;
      len[u] = len[last] + 2;
      link[u] = dfa[c][get_link(link[last])];
      diff[u] = len[u] - len[link[u]];
      if(diff[u] == diff[link[u]]) slink[u] = slink[link[u]];
      else slink[u] = link[u];
      dfa[c][last] = u;
    }
    last = dfa[c][last];
  }
};
