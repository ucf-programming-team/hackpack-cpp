#include <bits/stdc++.h>
typedef long long ll;

// TODO: Add longest common subsring
const int MAXL = 100000;
struct suffix_automaton {
  std::vector<int> len, link, occur, cnt;
  std::vector<std::map<char, int>> next;
  std::vector<char> isclone;
  ll* occuratleast;
  int sz, last;
  std::string s;
  suffix_automaton(void)
    : len(MAXL * 2),
      link(MAXL * 2),
      occur(MAXL * 2),
      next(MAXL * 2),
      isclone(MAXL * 2) {
    clear();
  }
  suffix_automaton(const std::string& inp)
    : suffix_automaton() {
    for (const char c : inp) this->extend(c);
  }
  void clear() {
    sz = 1;
    last = len[0] = 0;
    link[0] = -1;
    next[0].clear();
    isclone[0] = false;
  }
  bool issubstr(const std::string& other) {
    for (int i = 0, cur = 0;
         i < static_cast<int>(other.size()); ++i) {
      if (cur == -1) return false;
      cur = next[cur][other[i]];
    }
    return true;
  }
  void extend(char c) {
    int cur = sz++;
    len[cur] = len[last] + 1;
    next[cur].clear();
    isclone[cur] = false;
    int p = last;
    for (; p != -1 && !next[p].count(c); p = link[p])
      next[p][c] = cur;
    if (p == -1) {
      link[cur] = 0;
    } else {
      int q = next[p][c];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int clone = sz++;
        isclone[clone] = true;
        len[clone] = len[p] + 1;
        link[clone] = link[q];
        next[clone] = next[q];
        for (; p != -1 && next[p].count(c) && next[p][c] == q;
             p = link[p]) {
          next[p][c] = clone;
        }
        link[q] = link[cur] = clone;
      }
    }
    last = cur;
  }
  void count() {
    cnt = std::vector<int>(sz, -1);
    std::stack<std::pair<int, int>> S;
    S.push(std::make_pair(0, 0));
    std::map<char, int>::iterator i;
    while (!S.empty()) {
      auto cur = S.top();
      S.pop();
      if (cur.second) {
        for (i = next[cur.first].begin();
             i != next[cur.first].end(); ++i) {
          cnt[cur.first] += cnt[i->second];
        }
      } else if (cnt[cur.first] == -1) {
        cnt[cur.first] = 1;
        S.push(std::make_pair(cur.first, 1));
        for (i = next[cur.first].begin();
             i != next[cur.first].end(); ++i) {
          S.push(std::make_pair(i->second, 0));
        }
      }
    }
  }

  // CALL COUNT FIRST
  std::string lexicok(ll k) {
    int st = 0;
    std::string res;
    std::map<char, int>::iterator i;
    while (k) {
      for (i = next[st].begin(); i != next[st].end(); ++i) {
        if (k <= cnt[i->second]) {
          st = i->second;
          res.push_back(i->first);
          k--;
          break;
        } else {
          k -= cnt[i->second];
        }
      }
    }
    return res;
  }
  void countoccur() {
    for (int i = 0; i < sz; ++i) { occur[i] = 1 - isclone[i]; }
    std::vector<std::pair<int, int>> states(sz);
    for (int i = 0; i < sz; ++i) {
      states[i] = std::make_pair(len[i], i);
    }
    sort(states.begin(), states.end());
    for (int i = sz - 1; i >= 0; --i) {
      int v = states[i].second;
      if (link[v] != -1) { occur[link[v]] += occur[v]; }
    }
  }

  // call after inserting entire string
  std::vector<char> get_terminal_array(void) {
    ll p = last;
    std::vector<char> term(2 * MAXL);
    while (p > 0) {
      term[p] = true;
      p = link[p];
    }
    return term;
  }
};

// src:
// https://github.com/SuprDewd/CompetitiveProgramming/blob/master/code/strings/suffix_automaton.cpp
