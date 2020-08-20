#include <bits/stdc++.h>

typedef int ll;

struct suffix_tree {
  std::vector<ll> starts, lens, suffix_links;
  std::vector<std::vector<ll>> children;
  ll root, node;
  ll n, node_count, cur_len;
  ll alpha_size;

  std::vector<ll> alphabet;
  std::map<ll, ll> alpha_mapping;

  std::vector<ll> string;

  suffix_tree(const std::string& s) {
    std::vector<ll> alpha_list;
    for (char c : s) {
      if (alpha_mapping.find(c) == alpha_mapping.end()) {
        alpha_mapping[c] = alpha_list.size();
        alpha_list.push_back(c);
      }
    }

    std::sort(alpha_list.begin(), alpha_list.end());

    alphabet.resize(alpha_list.size() + 1);
    for (int i = 0; i < alpha_list.size(); ++i) {
      alphabet[i + 1] = alpha_list[i];
    }
    for (int i = 0; i < alphabet.size(); ++i) {
      alpha_mapping[alphabet[i]] = i;
    }

    string.resize(s.size() + 1);
    for (int i = 0; i < s.size(); ++i) {
      string[i] = alpha_mapping[s[i]];
    }

    alpha_size = alphabet.size();
    n = string.size();

    start();
  }

  suffix_tree(const std::vector<ll>& s, ll alpha_size) {
    string = s;
    this->alpha_size = alpha_size;
    n = string.size();
    start();
  }

  void start() {
    node_count = 0;

    starts.assign(n * 2, 0);
    lens.assign(n * 2, 0);
    suffix_links.assign(n * 2, 0);
    children.assign(n * 2, std::vector<ll>(alpha_size));

    root = create_node(-1, -1);
    node = root;
    cur_len = 0;
    for (int i = 0; i < n; ++i) { add_character(i); }
  }

  int create_node(int start, int len) {
    starts[node_count] = start;
    lens[node_count] = len;
    suffix_links[node_count] = 0;
    return node_count++;
  }
  void set_child(int node, int child, int c) {
    children[node][c] = child;
  }
  int get_child(int node, int c) { return children[node][c]; }
  bool has_child(int node, int c) {
    return children[node][c] != 0;
  }
  void add_character(int index) {
    ++cur_len;
    int lastCreated = -1;
    while (cur_len > 0) {
      while (
        has_child(node, string[index - cur_len + 1]) &&
        cur_len >
          lens[get_child(node, string[index - cur_len + 1])]) {
        node = get_child(node, string[index - cur_len + 1]);
        cur_len -= lens[node];
      }
      int edge = string[index - cur_len + 1];
      if (!has_child(node, edge)) {
        set_child(node, create_node(index - cur_len + 1, n),
                  edge);
        if (lastCreated != -1) {
          suffix_links[lastCreated] = node;
          lastCreated = -1;
        }
      } else {
        int next = get_child(node, edge);
        int currChar = string[index];
        int ch = string[starts[next] + cur_len - 1];
        if (ch == currChar) {
          if (lastCreated != -1 && node != root) {
            suffix_links[lastCreated] = node;
            lastCreated = -1;
          }
          return;
        }
        int split = create_node(starts[next], cur_len - 1);
        set_child(split, create_node(index, n), currChar);
        set_child(split, next, ch);
        starts[next] += cur_len - 1;
        lens[next] -= cur_len - 1;
        set_child(node, split, edge);
        if (lastCreated != -1) {
          suffix_links[lastCreated] = split;
        }
        lastCreated = split;
      }
      if (node == root && cur_len > 0) {
        --cur_len;
      } else if (node != root) {
        node = suffix_links[node];
      }
    }
  }

  void dfs() { dfs(root, 0); }

  void dfs(int n, int depth) {
    for (int i = 0; i < depth; ++i) { std::cerr << " "; }
    if (starts[n] != -1) {
      int curr;
      for (curr = 0;
           starts[n] + curr < static_cast<ll>(string.size()) &&
           curr < lens[n];
           ++curr)
        std::cerr << ( char )
            alphabet[string[starts[n] + curr]];
      if (starts[n] + lens[n] >=
          static_cast<ll>(string.size()))
        std::cerr << "$";
    }

    bool leaf = true;
    for (int child : children[n]) {
      if (child == 0) continue;
      if (leaf && starts[n] != -1) std::cerr << "\n";
      leaf = false;
      dfs(child, depth + 1);
    }
    if (leaf) { std::cerr << "\n"; }
  }

  std::vector<ll> suffix_array;
  int suffix_array_ind;
  std::vector<ll> lcp_array;
  int lcp_ind;
  std::stack<ll> lcp_stk;

  void get_sa_lcp(void) {
    suffix_array.resize(n);
    suffix_array_ind = 0;
    lcp_array.resize(n);
    lcp_ind = 0;
    lcp_stk = std::stack<ll>();
    lcp_stk.push(0);
    goiter(root, 0);

    suffix_array.erase(suffix_array.begin(),
                       std::next(suffix_array.begin()));
    lcp_array.erase(lcp_array.begin(),
                    std::next(lcp_array.begin(), 2));

    suffix_array.resize(n);
    lcp_array.resize(n);
  }

  void goiter(ll n, ll len) {
    bool leaf;
    std::stack<ll> stk;
    stk.push(0);
    stk.push(1);
    stk.push(len);
    stk.push(n);

    while (stk.size()) {
      n = stk.top();
      stk.pop();
      len = stk.top();
      stk.pop();
      leaf = stk.top();
      stk.pop();
      ll vis_kids = stk.top();
      stk.pop();

      const int l = std::max(lens[n], 0);

      const ll sz = children[n].size();

      if (vis_kids > 0) {
        if (leaf && children[n][vis_kids - 1] != 0) {
          leaf = false;
          lcp_stk.push(len + l);
        }
      }

      for (; vis_kids < sz && children[n][vis_kids] == 0;
           ++vis_kids)
        ;

      if (vis_kids < sz) {
        stk.push(vis_kids + 1);
        stk.push(leaf);
        stk.push(len);
        stk.push(n);

        stk.push(0);
        stk.push(1);
        stk.push(len + l);
        stk.push(children[n][vis_kids]);

        continue;
      } else {
        if (leaf) {
          suffix_array[suffix_array_ind++] = starts[n] - len;
          lcp_array[lcp_ind++] = lcp_stk.top();
        } else {
          lcp_stk.pop();
        }
      }
    }
  }

  void go(int n, int len) {
    bool leaf = true;
    int l = lens[n] == -1 ? 0 : lens[n];
    for (int child : children[n]) {
      if (child == 0) continue;
      go(child, len + l);
      if (leaf) {
        leaf = false;
        lcp_stk.push(len + l);
      }
    }
    if (leaf) {
      suffix_array[suffix_array_ind++] = starts[n] - len;
      lcp_array[lcp_ind++] = lcp_stk.top();
    } else {
      lcp_stk.pop();
    }
  }
};
