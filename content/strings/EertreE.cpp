#include <bits/stdc++.h>

struct eertree {
  const static ll ALPHA_LEN = 26;
  const static char ALPHA = 'a';
  struct node {
    std::vector<ll> next;
    ll len, suffix_link, cnt;
    node(const ll& l, const ll& link)
      : next(ALPHA_LEN), len(l), suffix_link(link), cnt(1) {}
  };

  ll len, suff, num;
  std::vector<node> tree;
  std::string s;

  eertree(void) : len(0), suff(2), num(2) {
    tree.push_back(node(0, 0));
    tree.push_back(node(-1, 1));
    tree.push_back(node(0, 1));
  }

  bool add_letter(const char& c) {
    const ll let = c - ALPHA;
    ll cur = suff, curlen = 0, pos = s.length();
    s += c;
    for (;;) {
      curlen = tree[cur].len;
      if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == c)
        break;
      cur = tree[cur].suffix_link;
    }

    if (tree[cur].next[let] != 0) {
      suff = tree[cur].next[let];
      tree[suff].cnt++;
      return false;
    }

    suff = tree[cur].next[let] = ++num;
    tree.push_back(node(tree[cur].len + 2, 2));
    if (tree[num].len == 1) { return true; }
    for (;;) {
      cur = tree[cur].suffix_link;
      curlen = tree[cur].len;
      if (pos - 1 - curlen >= 0 &&
          s[pos - 1 - curlen] == s[pos]) {
        tree[num].suffix_link = tree[cur].next[let];
        return true;
      }
    }
    return false;
  }

  ll num_palindromes(void) { return num - 2; }
};
