struct LinkCut : SplayTree {
// https://codeforces.com/blog/entry/75885
  LinkCut(int n): SplayTree(n) {}
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = T[u].p) {
      splay(u);
      int& ov = T[u].ch[1];
      T[u].vir += T[ov].sub;
      T[u].vir -= T[v].sub;
      ov = v;
      pull(u); }
    return splay(x), v; }
  void reroot(int x) { access(x); T[x].flip ^= 1; push(x); }
  void Link(int u, int v) {
    reroot(u), access(v);
    T[v].vir += T[u].sub;
    T[u].p = v;
    pull(v); }
  void Cut(int u, int v) {
    reroot(u), access(v);
    T[v].ch[0] = T[u].p = 0;
    pull(v); }
  // Rooted tree LCA. Returns 0 if u and v arent connected.
  int LCA(int u, int v) {
    if (u == v) return u;
    access(u);
    int ret = access(v);
    return T[u].p ? ret : 0; }
  // Query subtree of u where v is outside the subtree.
  ll Subtree(int u, int v) {
    reroot(v), access(u);
    return T[u].vir + T[u].self; } // Query path [u..v]
  ll Path(int u, int v) {
    reroot(u), access(v);
    return T[v].path; } // Update vertex u with value v
  void Update(int u,
              ll v) { access(u); T[u].self = v; pull(u); } };
