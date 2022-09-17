#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define rep(a, b, c) for (int a = b; a < c; a++)
using namespace std;
using vi = vector<int>;
using ll = long long;

pair<ll, int> operator+(ll x, const pair<ll, int>& o) {
	return {x + o.first, o.second};
}

template<class T1, class T2>
ostream& operator<<(ostream& cout, const pair<T1, T2>& o) {
	return cout << o.first << ":" << o.second;
}

struct LinkCut {
	struct Node {
		int p = 0, c[2] = {0, 0}, pp = 0;
		pair<ll, int> ppv = {0, 0};
		bool flip = 0;

		ll sum = 0, val = 0;
		pair<ll, int> dpL = {0, 0}, dpR = {0, 0};
		multiset<pair<ll, int>> hanging;
	};

	vector<Node> T;

	LinkCut(int n): T(n + 1) {}

	int dir(int x, int y) { return T[x].c[1] == y; }
	
	void set(int x, int d, int y) {
		if (x) T[x].c[d] = y, pull(x);
		if (y) T[y].p = x;
	}

	ll getSum(int x) { return x ? T[x].sum : 0; }
	pair<ll, int> getDPL(int x) { return x ? (!T[x].flip ? T[x].dpL : T[x].dpR) : make_pair(0ll, 0); }
	pair<ll, int> getDPR(int x) { return x ? (!T[x].flip ? T[x].dpR : T[x].dpL) : make_pair(0ll, 0); }

	void pull(int x) {
		if (!x) return;
		int &l = T[x].c[0], &r = T[x].c[1];

		T[x].sum = T[x].val + getSum(l) + getSum(r);

		pair<ll, int> hang = {0, 0};
		if (T[x].hanging.size())
			hang = *T[x].hanging.rbegin();

		T[x].dpL = max(getDPL(l), getSum(l) + T[x].val + max(hang, getDPL(r)));
		if (T[x].dpL.second == 0)
			T[x].dpL.second = x;

		
		T[x].dpR = max(getDPR(r), getSum(r) + T[x].val + max(hang, getDPR(l)));
		if (T[x].dpR.second == 0)
			T[x].dpR.second = x;
	}

	void push(int x) {
		if (!x || !T[x].flip) return;
		int &l = T[x].c[0], &r = T[x].c[1];

		if (l) T[l].flip ^= 1;
		if (r) T[r].flip ^= 1;
		swap(T[x].dpL, T[x].dpR);
		swap(l, r);
		T[x].flip = 0;
	}

	void rotate(int x, int d) {
		int y = T[x].p, z = T[y].p, w = T[x].c[d];
		swap(T[x].pp, T[y].pp);
		swap(T[x].ppv, T[y].ppv);
		set(y, !d, w);
		set(x, d, y);
		set(z, dir(z, y), x);
	}

	void splay(int x) {
		for (push(x); T[x].p;) {
			int y = T[x].p, z = T[y].p;
			push(z), push(y), push(x);
			int dx = dir(y, x), dy = dir(z, y);
			if (!z) rotate(x, !dx);
			else if (dx == dy) rotate(y, !dx), rotate(x, !dx);
			else rotate(x, dy), rotate(x, dx);
		}
	}

	void Access(int _u) {
		for (int v = 0, u = _u; u; u = T[v = u].pp) {
			splay(u), splay(v);
			int r = T[u].c[1];
			T[v].pp = 0;

			if (r) {
				T[u].hanging.insert(getDPL(r));
				T[r].ppv = getDPL(r);
			}
			if (v) {
				auto it = T[u].hanging.find(T[v].ppv);
				if (it != T[u].hanging.end()) {
					T[u].hanging.erase(it);
				}
			}

			swap(T[r].p, T[r].pp);
			set(u, 1, v);
		}
		splay(_u);
	}

	// to be able reroot a tree, you must be able to reverse
	// the inorder trav. of the splay tree
	// can be skipped if that is not possible
	void MakeRoot(int u) {
		Access(u);
		if (int l = T[u].c[0]) {
			T[l].flip ^= 1;
			swap(T[l].p, T[l].pp);
			T[l].ppv = getDPL(l);
			T[u].hanging.insert(getDPL(l));
		}
		set(u, 0, 0);
	}

	void Link(int u, int v) { // v is a child of u
		Access(u), Access(v);
		MakeRoot(v); // not needed if v is always a forest root
		set(u, 0, v);
	}

	void Cut(int u) { // cut u from its parent
		Access(u);
		if (int l = T[u].c[0]) T[l].p = 0;
		set(u, 0, 0);
	}

	int FindRoot(int u) {
		Access(u);
		while (T[u].c[0]) u = T[u].c[0];
		splay(u); return u;
	}

	bool Connected(int u, int v) {
		return FindRoot(u) == FindRoot(v);
	}

	// get a splay tree representing the u -> v path
	int GetPath(int u, int v) {
		return MakeRoot(u), Access(v), v;
	}
};

void build(int u, int p, vector<vi>& adj, LinkCut& lct) {
	for (int v : adj[u])
		if (v != p) {
			lct.Link(v, u);
			build(v, u, adj, lct);
		}
}

void solve() {
	int n, q;
	ll maxW;
	cin >> n >> q >> maxW;

	vector<vi> adj(2*n + 1);
	vector<ll> w(2*n + 1);
	LinkCut lct(2*n + 1);

	for (int i = 0; i < n-1; i++) {

		int mid = n + 1 + i;
		int u, v;
		cin >> u >> v >> w[mid];

		adj[u].push_back(mid);
		adj[mid].push_back(u);
		adj[v].push_back(mid);
		adj[mid].push_back(v);
	}

	for (int i = 1; i <= 2*n; i++)
		lct.T[i].val = w[i];

	build(1, -1, adj, lct);

	ll last = 0;
	int root = 1;
	lct.MakeRoot(1);

	for (int qq = 0; qq < q; qq++) {
		ll d, e;
		cin >> d >> e;

		d = (d + last) % (n - 1);
		e = (e + last) % maxW;

		int idx = n + 1 + d;

		lct.Access(idx);
		lct.T[idx].val = e;
		lct.push(idx);
		lct.pull(idx);

		lct.Access(root);
		auto [_, diam1] = lct.getDPL(root);

		lct.MakeRoot(root = diam1);
		auto [ans, __] = lct.getDPL(root);

		cout << ans << '\n';

		last = ans;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	solve();

	return 0;
}