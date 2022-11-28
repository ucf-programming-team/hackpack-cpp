#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../../tests/TestRunner.h"
#include "../../content/graphs/LCA.h"

void test() {
	int n, q;
	cin >> n >> q;

	vector<vi> adj(n);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}

	LCA t(adj);

	for (int i = 0; i < q; i++) {
		int u, v;
		cin >> u >> v;
		cout << t.lca(u, v) << "\n";
	}
}
