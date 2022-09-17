const int ALPHA = 26;
struct AhoCorasick {
  int nodeCount;
  vector<vector<int>> transition, children;
  vector<int> term, leaf;
  queue<int> q;
  AhoCorasick(){}
  AhoCorasick(vector<string> &strs) {
    int maxNodes = 1;
    for(string &s : strs) maxNodes += (int) s.length();
    transition.resize(ALPHA);
    children.resize(ALPHA, vector<int>(maxNodes));
    leaf.resize(maxNodes);
    nodeCount = 1;
    for(string &s : strs) {
      int node = 0;
      for(char &ch : s) {
        int c = ch - 'a';
        if(children[c][node] == 0) children[c][node] = nodeCount++;
        node = children[c][node];
      }
      leaf[node]++;
    }
    for(int i = 0; i < ALPHA; ++i) transition[i].resize(nodeCount);
    term.resize(nodeCount);
    q.push(0), q.push(0);
    while(q.size()) {
      int node = q.front(); q.pop();
      int suffLink = q.front(); q.pop();
      term[node] = leaf[node] + term[suffLink];
      for(int ch = 0; ch < ALPHA; ++ch) {
        if(children[ch][node] != 0) {
          transition[ch][node] = children[ch][node];
          q.push(children[ch][node]);
          q.push(node == 0 ? 0 : transition[ch][suffLink]);
        } else {
          transition[ch][node] = transition[ch][suffLink];
        }
      }
    }
  }
};
