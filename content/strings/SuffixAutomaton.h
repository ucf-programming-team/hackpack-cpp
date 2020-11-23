const int A = 26;
struct SuffAuto {
  int size, N, last;
  vector<int> first_pos, link, len;
  vector<vector<int>> dfa;
  vector<bool> term, is_clone;
  SuffAuto(): size(0) {}
  SuffAuto(const string& s):
    N(sz(s) << 1), link(N), len(N), first_pos(N),
    term(N), dfa(A, vector<int>(N)), is_clone(N) {
    size = 1;  last = 0;  link[0] = -1;
    for(char c : s) extend(c);
    for(int p = last; p; p = link[p]) term[p] = true;
  }
  void extend(char cc) {
    int c = cc - 'a';
    int cur = size++;
    len[cur] = len[last] + 1;
    first_pos[cur] = len[cur] - 1;
    int p = last;  last = cur;
    for(; p != -1 && !dfa[c][p]; p = link[p]) dfa[c][p] = cur;
    if(p == -1) return;
    int q = dfa[c][p];
    if(len[p] + 1 == len[q]) return void(link[cur] = q);
    int clone = size++;
    is_clone[clone] = true;
    len[clone] = len[p] + 1;
    link[clone] = link[q];
    for(int i = 0; i < A; i++) dfa[i][clone] = dfa[i][q];
    for(; p != -1 && dfa[c][p] == q; p = link[p]) dfa[c][p] = clone;
    link[q] = link[cur] = clone;
    first_pos[clone] = first_pos[q];
  }
};
