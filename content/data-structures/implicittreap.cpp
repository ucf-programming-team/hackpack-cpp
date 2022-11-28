namespace ImplicitTreap {
mt19937 rng(696969420);
struct node {
	int val;
	int count, prio;
	node *l, *r, *p;
	string debug(int index) {
		return "(" + to_string(index) + "," + to_string(val) + ")";
	}
};
static int getCount(node* root) {
	return root ? root->count : 0;
}
void update(node* root) {
	if (!root) return;
	root->p = NULL;
	if (root->l) root->l->p = root;
	if (root->r) root->r->p = root;
	root->count = 1 + getCount(root->l) + getCount(root->r);
}
void merge(node*& t, node* l, node* r) {
	if (!l || !r) t = l ? l : r;
	else if (l->prio > r->prio) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	update(t);
}
//splits s.t. l < index && r >= index
void split(node* t, node*& l, node*& r, int index,
	int add = 0) {
	if (!t) return void(l = r = NULL);
	int cur_index = add + getCount(t->l);
	if (index <= cur_index)
		split(t->l, l, t->l, index, add), r = t;
	else
		split(t->r, t->r, r, index, add + 1 + getCount(t->l)),
			l = t;
	update(t);
}
node* remove(node*& t, int index) {
	node *l, *r, *del;
	split(t, l, r, index);
	split(r, del, r, 1);
	merge(t, l, r);
	return del;
}
void insert(node*& t, node* item, int index) {
	node *l, *r;
	split(t, l, r, index);
	merge(l, l, item), merge(t, l, r);
}
node* insert(node*& root, int index, int val) {
	node* item = new node();
	item->val = val;
	item->count = 1;
	item->prio = rng();
	item->l = item->r = item->p = NULL;
	insert(root, item, index);
	return item;
}
node* get(node* t, int index, int add = 0) {
	int cur_index = add + getCount(t->l);
	if (index < cur_index) return get(t->l, index, add);
	if (index > cur_index)
		return get(t->r, index, add + 1 + getCount(t->l));
	return t;
}
int get_index(node* t) {
	int leq = getCount(t->l) + 1;
	while (t->p) {
		if (t->p->r == t) leq += getCount(t->p->l) + 1;
		t = t->p;
	}
	return leq - 1;
}
void print(node* t, int& index, bool isRoot) {
	if (!t) return;
	print(t->l, index, false);
	cerr << t->debug(index++) << ' ';
	print(t->r, index, false);
	if (isRoot) cout << endl;
}
void print(node* t) {
	int index = 0;
	print(t, index, true);
}
};
