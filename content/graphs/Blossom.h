/**
 * Author: bicsi
 * Source: https://codeforces.com/blog/entry/92339?#comment-810242
 * Description: General matching in $O(nm)$.
 */
vi Blossom(vector<vi>& adj) {
	int n = adj.size(), T = -1;
	vi mate(n, -1), label(n), par(n), orig(n), aux(n, -1), q;
	auto lca = [&](int x, int y) {
		for (T++;; swap(x, y)) {
			if (x == -1) continue;
			if (aux[x] == T) return x;
			aux[x] = T;
			x = (mate[x] == -1 ? -1 : orig[par[mate[x]]]);
		}
	};
	auto blossom = [&](int v, int w, int a) {
		while (orig[v] != a) {
			par[v] = w;
			w = mate[v];
			if (label[w] == 1) label[w] = 0, q.push_back(w);
			orig[v] = orig[w] = a, v = par[w];
		}
	};
	auto augment = [&](int v) {
		while (v != -1) {
			int pv = par[v], nv = mate[pv];
			mate[v] = pv, mate[pv] = v, v = nv;
		}
	};
	auto bfs = [&](int root) {
		fill(all(label), -1), iota(all(orig), 0);
		q.clear(), q.push_back(root), label[root] = 0;
		for (int i = 0; i < sz(q); i++) {
			int v = q[i];
			for (auto x : adj[v])
				if (label[x] == -1) {
					label[x] = 1, par[x] = v;
					if (mate[x] == -1) return augment(x);
					label[mate[x]] = 0, q.push_back(mate[x]);
				} else if (label[x] == 0 && orig[v] != orig[x]) {
					int a = lca(orig[v], orig[x]);
					blossom(x, v, a), blossom(v, x, a);
				}
		}
	};
	// Time halves if you start with (any) maximal matching.
	for (int i = 0; i < n; i++)
		if (mate[i] == -1) bfs(i);
	return mate;
}
