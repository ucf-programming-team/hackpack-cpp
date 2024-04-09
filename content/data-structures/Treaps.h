struct node {
  int pri, sz = 1;
  ll val, sum, min, lazy = 0;
  node* l = NULL, *r = NULL;
  node(ll v): val(v), sum(v), min(v) { pri = rand(); } };
int getSz(node* in) { return in ? in->sz : 0; }
ll getSum(node* in) { return in ? in->sum : 0; }
ll getMin(node* in) { return in ? in->min : 4e18; }
void pushNode(node* in, ll val) {
  in->sum += val;
  in->min += val;
  in->lazy += val; }
void push(node* in) {
  if (in->l) pushNode(in->l, in->lazy);
  if (in->r) pushNode(in->r, in->lazy);
  in->lazy = 0; }
void pull(node* in) {
  in->sz = getSz(in->l) + 1 + getSz(in->r);
  in->sum = getSum(in->l) + in->val + getSum(in->r);
  in->min = min(getMin(in->l), min(in->val, getMin(in->r))); }
pair<node*, node*> split(node* in, int leftIdx) {
  if (!in) return {NULL, NULL};
  push(in);
  if (leftIdx < getSz(in->l)) {
    auto [lLeft, lRight] = split(in->l, leftIdx);
    in->l = lRight;
    pull(in);
    return {lLeft, in}; }
  auto [rLeft,
        rRight] = split(in->r, leftIdx - (getSz(in->l) + 1));
  in->r = rLeft;
  pull(in);
  return {in, rRight}; }
node* merge(node* a, node* b) {
  if (!a) return b;
  if (!b) return a;
  push(a), push(b);
  if (a->pri < b->pri) {
    a->r = merge(a->r, b);
    pull(a);
    return a; }
  b->l = merge(a, b->l);
  pull(b);
  return b; }
ll getSum(node* in, int l, int r) {
  auto [rest, right] = split(in, r);
  auto [left, root] = split(rest, l - 1);
  ll out = getSum(root);
  in = merge(left, merge(root, right));
  return out; }
void add(node* in, int l, int r, ll val) {
  auto [rest, right] = split(in, r);
  auto [left, root] = split(rest, l - 1);
  pushNode(root, val);
  in = merge(merge(left, root), right); }
