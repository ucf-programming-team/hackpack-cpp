// https://codeforces.com/blog/entry/75885

struct SplayTree {
  struct Node {
    int ch[2] = {0, 0}, p = 0, cnt = 1;
    long long self = 0, path = 0;        // Path aggregates
    long long sub = 0, vir = 0;          // Subtree aggregates
    bool flip = 0;                       // Lazy tags
  };
  vector<Node> T;
 
  SplayTree(int n) : T(n + 1) { T[0].cnt = 0; }
  
  void push(int x) {
    if (!x || !T[x].flip) return;
    int l = T[x].ch[0], r = T[x].ch[1];
 
    T[l].flip ^= 1, T[r].flip ^= 1;
    swap(T[x].ch[0], T[x].ch[1]);
    T[x].flip = 0;
  }
  
  void pull(int x) {
    int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r); 
 
    T[x].path = T[l].path + T[x].self + T[r].path;
    T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
    T[x].cnt = T[l].cnt + 1 + T[r].cnt;
  }
  
  void set(int x, int d, int y) {
    T[x].ch[d] = y; T[y].p = x; pull(x); 
  }
 
  void splay(int x) { 
    auto dir = [&](int x) {
      int p = T[x].p; if (!p) return -1;
      return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
    };
    auto rotate = [&](int x) {
      int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
      set(y, dx, T[x].ch[!dx]); 
      set(x, !dx, y);
      if (~dy) set(z, dy, x); 
      T[x].p = z;
    };
    for (push(x); ~dir(x); ) {
      int y = T[x].p, z = T[y].p;
      push(z); push(y); push(x);
      int dx = dir(x), dy = dir(y);
      if (~dy) rotate(dx != dy ? x : y);
      rotate(x);
    }
  }

  // TEST THIS STUFF

  int kth(int x, int k) {
    if (!x) return 0;
    k = min(max(k, 0), T[x].cnt - 1);
    for (int l = T[x].ch[0]; T[l].cnt != k; l = T[x].cnt[0]) 
      if (T[l].cnt < k) x = l;
      else k -= T[l].cnt + 1, x = T[x].ch[1];
    return splay(x), x;
  }

  // k = size of left subtree
  pair<int, int> split(int x, int k) {
    if (!x || k <= 0) return {0, x};
    if (k >= T[x].cnt) return {x, 0};
    int r = kth(x, k), l = T[r].ch[0];
    T[r].ch[0] = 0, T[l].p = 0;
    return {l, r};
  }

  int merge(int l, int r) {
    if (!l || !r) return !l ? r : l;
    r = kth(r, 0), set(r, 0, l);
    return r;
  }
};
