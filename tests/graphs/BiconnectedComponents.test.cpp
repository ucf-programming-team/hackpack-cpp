#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../../tests/TestRunner.h"
#include "../../content/graphs/BiconnectedComponents.h"
#include "../../content/data-structures/DSU.h"

void test() {
  int n, m;
  cin >> n >> m;

	ed.resize(n);
	vector<pii> edges(m);
  for (int i = 0; i < m; i++) {
    auto& [u, v] = edges[i];
		cin >> u >> v;
		ed[u].emplace_back(v, i);
		ed[v].emplace_back(u, i);
  }

	DSU dsu(n);
	int ans = n;

	bicomps([&](const auto& cedges) {
		for (int i : cedges) {
			auto [u, v] = edges[i];
			ans -= dsu.join(u, v);
		}
	});

	vector<vi> out(n);
	for (int i = 0; i < n; i++)
		out[dsu.find(i)].push_back(i);

	cout << ans << "\n";
	for (auto& it : out) {
		if (it.empty()) continue;
		cout << it.size() << " ";
		for (int i : it) cout << i << " ";
		cout << "\n";
	}
}
