#define PROBLEM "https://judge.yosupo.jp/problem/dominatortree"
#include "../../tests/TestRunner.h"
#include "../../content/graphs/DominatorTree.h"

void test() {
	int n, m, s;
	cin >> n >> m >> s;

	vector<vi> adj(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
	}

	auto tree = dominator_tree(adj, s);

	vi p(n, -1);
	p[s] = s;
	for (int i = 0; i < n; i++)
		for (int j : tree[i]) p[j] = i;

	for (int i = 0; i < n; i++) cout << p[i] << ' ';
	cout << '\n';
}
