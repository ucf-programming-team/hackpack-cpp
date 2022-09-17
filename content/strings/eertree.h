#include <bits/stdc++.h>
#include <math.h>

#define pb push_back
#define mp make_pair
#define eb emplace_back
#define xx first
#define yy second
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;

struct eertree
{
  vi s, len, link, cnt, cntMax;
  vector<vi> to;
  int node, last, n;

  eertree(): s(1), len(2), cnt(2), link(2), to(2, vi(26, 0)), cntMax(2)
  {
    s[0] = -1;
    link[0] = link[1] = 1;
    len[0] = 0, len[1] = -1;
    node = 2;
    n = 1;
    last = 0;
  }

  int get_link(int v)
  {
    while (s[n-len[v]-2] != s[n-1]) v = link[v];
    return v;
  }

  void insert(int c)
  {
    n++;
    s.pb(c), len.pb(0), cnt.pb(0), link.pb(0), to.eb(26, 0);
    cntMax.pb(0);
  }
  
  void add(char ch)
  {
    int c = ch - 'a';
    insert(c);
    last = get_link(last);

    if (to[last][c] == 0)
    {
      len[node] = len[last] + 2;
      link[node] = to[get_link(link[last])][c];
      to[last][c] = node;
      node++;
    }

    last = to[last][c];
    cntMax[last]++;
  }

  void go()
  {
    for (int i = node-1; i >= 0; i--)
      cnt[i] = cntMax[i];

    for (int i = node-1; i >= 0; i--)
      cnt[link[i]] += cnt[i];
  }
};

void solve()
{   
  string s; cin >> s;

  eertree et;

  for (int i = 0; i < s.length(); i++)
    et.add(s[i]);

  et.go();

  ll ans = 0;
  for (int i = 0; i < et.cnt.size(); i++)
    ans = max(ans, et.cnt[i] * 1ll * et.len[i]);
    // cout << i << ": " << et.cnt[i] << ", " << et.len[i] << '\n';

  cout << ans << '\n';
}       

int main()
{
  ios::sync_with_stdio(false); cin.tie(0);

  // int t; cin >> t; while (t--)
  solve();

  return 0;
}
