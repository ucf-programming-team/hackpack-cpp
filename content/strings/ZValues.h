vector<int> zValues(string& s) {
  int n = (int)s.length();
  vector<int> z(n);
  for (int i = 1, L = 0, R = 0; i < n; ++i) {
    if (i <= R) z[i] = min(R - i + 1, z[i - L]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > R) L = i, R = i + z[i] - 1; }
  return z; }
