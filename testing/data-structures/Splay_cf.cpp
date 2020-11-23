// tested on https://codeforces.com/contest/863/problem/D
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct node {
  node *ch[2] = {0}, *p = 0;
  int cnt = 1, val;
  bool flip = 0;

  node(int val, node* l = 0, node* r = 0):
    val(val), ch{l, r} {}
};

int cnt(node* x) { return x ? x->cnt : 0; }
int dir(node* p, node* x) { return p && p->ch[0] != x; }
void setLink(node* p, node* x, int d) {
  if (p) p->ch[d] = x;
  if (x) x->p = p;
}

node* update(node* x);
void prop(node* x);

void rotate(node* x, int d) {
  if (!x || !x->ch[d]) return;
  node *y = x->ch[d], *z = x->p;
  setLink(x, y->ch[d ^ 1], d);
  setLink(y, x, d ^ 1);
  setLink(z, y, dir(z, x));
  update(x);
  update(y);
}

node* splay(node* x) {
  while (x && x->p) {
    node *y = x->p, *z = y->p;
    // prop(z), prop(y), prop(x); // needed for LCT
    int dy = dir(y, x), dz = dir(z, y);
    if (!z)
      rotate(y, dy);
    else if (dy == dz)
      rotate(z, dz), rotate(y, dy);
    else
      rotate(y, dy), rotate(z, dz);
  }
  return x;
}

// ***** STOP HERE FOR LCT *****

// the returned node becomes the new root, update the root
// pointer!
node* nodeAt(node* x, int pos) {
  if (!x) return 0;
  while (prop(x), cnt(x->ch[0]) != pos)
    if (pos < cnt(x->ch[0]))
      x = x->ch[0];
    else
      pos -= cnt(x->ch[0]) + 1, x = x->ch[1];
  return splay(x);
}

node* merge(node* l, node* r) {
  if (!l || !r) return l ?: r;
  l = nodeAt(l, cnt(l) - 1);
  setLink(l, r, 1);
  return update(l);
}

// first is everything < pos, second is >= pos
pair<node*, node*> split(node* t, int pos) {
  if (pos <= 0 || !t) return {0, t};
  node *l = nodeAt(t, pos - 1), *r = l->ch[1];
  if (r) l->ch[1] = r->p = 0;
  return {update(l), update(r)};
}

// insert a new node between pos-1 and pos
node* insert(node* t, int pos, int val) {
  auto [l, r] = split(t, pos);
  return update(new node(val, l, r));
}

// apply lambda to all nodes in an inorder traversal
template <class F>
void each(node* x, F f) {
  if (x) prop(x), each(x->ch[0], f), f(x), each(x->ch[1], f);
}

// problem specific functions
node* update(node* x) {
  if (!x) return 0;
  x->cnt = 1 + cnt(x->ch[0]) + cnt(x->ch[1]);
  setLink(x, x->ch[0], 0), setLink(x, x->ch[1], 1);
  return x;
}

void prop(node* x) {
  if (!x || !x->flip) return;
  if (x->ch[0]) x->ch[0]->flip ^= x->flip;
  if (x->ch[1]) x->ch[1]->flip ^= x->flip;
  swap(x->ch[0], x->ch[1]);
  x->flip = 0;
  update(x);
}

void solve() {
  int n, q, m;
  cin >> n >> q >> m;

  node* root = NULL;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    root = insert(root, i, x);
  }

  for (int i = 0; i < q; i++) {
    int t, x, y;
    cin >> t >> x >> y;
    x--, y--;
    node *l, *c, *r;
    tie(l, r) = split(root, x);
    tie(c, r) = split(r, y - x + 1);

    if (t == 1) {
      auto [cl, cr] = split(c, cnt(c) - 1);
      c = merge(cr, cl);
    } else
      c->flip ^= 1;

    root = merge(l, merge(c, r));
  }

  vector<int> a(n);
  int k = 0;
  each(root, [&](node* x) { a[k++] = x->val; });

  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    cout << a[x - 1] << " ";
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  // int t; cin >> t; while (t--)
  solve();

  return 0;
}
