/**
 * Description: An implicit balanced BST. You only need to
 * change \texttt{update()} and \texttt{prop()}. \\
 * If used for link-cut tree, code everything up to
 * \texttt{splay()}. Time: amortized $O(\log n)$ for all
 * operations
 */
struct node {
	node *ch[2] = {0}, *p = 0;
	int cnt = 1, val;
	node(int val, node* l = 0, node* r = 0):
		ch{l, r}, val(val) {}
};
int cnt(node* x) { return x ? x->cnt : 0; }
int dir(node* p, node* x) { return p && p->ch[0] != x; }
void setLink(node* p, node* x, int d) {
	if (p) p->ch[d] = x;
	if (x) x->p = p;
}
node* update(node* x) {
	if (!x) return 0;
	x->cnt = 1 + cnt(x->ch[0]) + cnt(x->ch[1]);
	setLink(x, x->ch[0], 0);
	setLink(x, x->ch[1], 1);
	return x;
}
void prop(node* x) {
	if (!x) return;
	// update(x); // needed if prop() can change subtree sizes
}
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
		if (!z) rotate(y, dy);
		else if (dy == dz) rotate(z, dz), rotate(y, dy);
		else rotate(y, dy), rotate(z, dz);
	}
	return x;
}
// the returned node becomes the new root, update the root
// pointer!
node* nodeAt(node* x, int pos) {
	if (!x) return 0;
	while (prop(x), cnt(x->ch[0]) != pos)
		if (pos < cnt(x->ch[0])) x = x->ch[0];
		else pos -= cnt(x->ch[0]) + 1, x = x->ch[1];
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
	if (pos > cnt(t)) return {t, 0};
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
template<class F> void each(node* x, F f) {
	if (x) prop(x), each(x->ch[0], f), f(x), each(x->ch[1], f);
}
