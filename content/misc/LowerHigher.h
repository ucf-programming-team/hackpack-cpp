template<class S, class T>
auto lower(const S& s, const T& x, bool strict = 0) {
  auto it = strict ? s.lower_bound(x) : s.upper_bound(x);
  return it == begin(s) ? end(s) : prev(it); }
template<class S, class T>
auto higher(const S& s, const T& x, bool strict = 0) {
  return strict ? s.upper_bound(x) : s.lower_bound(x); }
