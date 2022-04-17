// tested on https://www.spoj.com/problems/SUFEQPRE/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/strings/ZValues.h"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;
  for (int tt = 1; tt <= t; tt++) {
    string s;
    cin >> s;
    auto z = zValues(s);
    int ans = 0;
    for (int i = 1; i < s.length(); i++)
      ans += (s.length() - i == z[i]);
    cout << "Case " << tt << ": " << ans << '\n';
  }
}
