struct Aho {
  int N;
  vector<vector<int>> dfa;
  vector<int> link;
  vector<bool> term, leaf;
  Aho() {}
  Aho(const vector<string>& vs) {
    int maxN = 1;
    for(auto& s : vs) maxN += sz(s);
    dfa.resize(26, vector<int>(maxN));
    link = vector<int>(maxN);
    leaf = term = vector<bool>(maxN);
    N = 1;
    for(auto& s : vs) {
      int v = 0;
      for(auto& cc : s) {
        int c = cc - 'a';
        if(!dfa[c][v]) dfa[c][v] = N++;
        v = dfa[c][v];
      }
      leaf[v] = true;
    }
    deque<int> q = {0};
    while(!q.empty()) {
      int v = q.front();  q.pop_front();
      term[v] = leaf[v] || term[link[v]];
      for(int c = 0; c < 26; c++) {
        if(dfa[c][v]) {
          if(v) link[dfa[c][v]] = dfa[c][link[v]];
          q.pb(dfa[c][v]);
        } else dfa[c][v] = dfa[c][link[v]];
      }
    }
  }
};
