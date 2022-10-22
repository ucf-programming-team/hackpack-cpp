// hash = 8f9536
template<class G> int max_right(int l, G g) { // bool g(T);
  assert(g(e()));
  if (l == N) return N;
  l += S;
  for (int i = log; i >= 1; i--) push(l >> i);
  T sm = e();
  do {
    while (l % 2 == 0) l >>= 1;
    if (!g(op(sm, d[l]))) {
      while (l < S) {
        push(l), l *= 2;
        if (g(op(sm, d[l]))) sm = op(sm, d[l++]);
      }
      return l - S;
    }
    sm = op(sm, d[l++]);
  } while ((l & -l) != l);
  return N;
}
template<class G> int min_left(int r, G g) {
  assert(g(e()));
  if (r == 0) return 0;
  r += S;
  for (int i = log; i >= 1; i--) push((r - 1) >> i);
  T sm = e();
  do {
    r--;
    while (r > 1 && (r % 2)) r >>= 1;
    if (!g(op(d[r], sm))) {
      while (r < S) {
        push(r), r *= 2;
        if (g(op(d[++r], sm))) sm = op(d[r--], sm);
      }
      return r + 1 - S;
    }
    sm = op(d[r], sm);
  } while ((r & -r) != r);
  return 0;
}
