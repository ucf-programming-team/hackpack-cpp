const int oo = 1e9;

// Use to traverse tree
struct State {
  int id, l, r;

  int getLen() { return r - l + 1; }
};

struct Node {
  int id;
  int suffLink;
  int l, r;
  int depth;
  map<char, int> child;

  Node(int id, int l, int r): id(id), l(l), r(r) {}

  bool hasEdge(char c) { return child.find(c) != child.end(); }
  int getLen() { return r - l + 1; }
};

struct SuffixTree {
  State active;
  int root;
  vector<Node> nodes;
  string st;

  SuffixTree(string inp): st(inp) {
    // append $ if need to know which nodes are suffixes
    nodes.emplace_back(0, -1, -1);
    nodes.emplace_back(1, 0, 0);
    nodes[1].suffLink = 0;
    root = 1;
    active = State{root, 0, 0};
    for (int i = 0; i < st.size(); i++) {
      nodes[0].child[st[i]] = 1;
      active.r = i;
      active = update(active);
      active = canonize(active);
    }
    for (int i = 0; i < nodes.size(); i++) {
      nodes[i].r = min(nodes[i].r, ( int )st.size() - 1);
    }
  }

  // call canonize when following suffix links
  State canonize(State s) {
    if (s.r < s.l) return s;
    int curr = nodes[s.id].child[st[s.l]];
    while (nodes[curr].getLen() <= s.getLen()) {
      s.l += nodes[curr].getLen();
      s.id = curr;
      if (s.l <= s.r) { curr = nodes[s.id].child[st[s.l]]; }
    }
    return s;
  }

  int newNode(int l, int r) {
    nodes.emplace_back(nodes.size(), l, r);
    return nodes.size() - 1;
  }

  pair<bool, int> split(State s, char t) {
    if (s.l <= s.r) {
      int curr = nodes[s.id].child[st[s.l]];
      if (t == st[nodes[curr].l + s.getLen()]) {
        return {true, s.id};
      }
      newNode(nodes[curr].l, nodes[curr].l + s.r - s.l);
      nodes[s.id].child[st[s.l]] = nodes.back().id;
      nodes.back().child[st[nodes[curr].l + s.getLen()]] =
       curr;
      nodes[curr].l = nodes[curr].l + s.getLen();
      return {false, nodes.back().id};
    } else {
      if (!nodes[s.id].child.count(t)) {
        return {false, s.id};
      } else {
        return {true, s.id};
      }
    }
  }

  State update(State s) {
    int oldr = root;
    auto [endPoint, r] =
     split(State{s.id, s.l, s.r - 1}, st[s.r]);
    while (!endPoint) {
      newNode(s.r, oo);
      nodes[r].child[st[s.r]] = nodes.back().id;
      if (oldr != root) { nodes[oldr].suffLink = r; }
      oldr = r;
      State canon =
       canonize(State{nodes[s.id].suffLink, s.l, s.r - 1});
      tie(s.id, s.l) = {canon.id, canon.l};
      tie(endPoint, r) =
       split(State{s.id, s.l, s.r - 1}, st[s.r]);
    }
    if (oldr != root) { nodes[oldr].suffLink = s.id; }
    return s;
  }
};
