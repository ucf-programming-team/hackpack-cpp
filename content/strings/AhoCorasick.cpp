const ll ALPHA = 26;
struct aho_corasicc {
  ll node_count;
  std::vector<std::vector<ll>> trans;
  std::vector<char> term;

  aho_corasicc(void) {}

  aho_corasicc(const std::vector<std::string>& strs) {
    ll max_nodes = 1;
    for (const auto& s : strs) max_nodes += s.length();

    std::vector<std::vector<ll>> trie(
      ALPHA, std::vector<ll>(max_nodes));
    std::vector<char> leaf(max_nodes);
    node_count = 1;
    for (const auto& s : strs) {
      ll node = 0;
      for (const auto& ch : s) {
        ll c = ch - 'A';
        if (trie[c][node] == 0) {
          trie[c][node] = node_count++;
        }
        node = trie[c][node];
      }
      leaf[node] = true;
    }

    trans.assign(ALPHA, std::vector<ll>(node_count));
    term.assign(node_count, 0);

    std::queue<ll> order;
    order.push(0);
    order.push(0);

    while (!order.empty()) {
      ll node = order.front();
      order.pop();
      ll slink = order.front();
      order.pop();
      term[node] = leaf[node] || term[slink];
      for (ll ch = 0; ch < ALPHA; ++ch) {
        if (trie[ch][node] != 0) {
          trans[ch][node] = trie[ch][node];
          order.push(trie[ch][node]);
          order.push(node == 0 ? 0 : trans[ch][slink]);
        } else
          trans[ch][node] = trans[ch][slink];
      }
    }
  }

  const std::vector<ll>& operator[](const ll& idx) const {
    return trans[idx];
  }
};
