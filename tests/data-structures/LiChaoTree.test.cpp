#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include "../../tests/TestRunner.h"
#include "../../content/data-structures/LiChaoTree.h"

const ll XV = ll(1e9) + 10;
const ll oo = ll(2e18) + 100;

ll eval(pair<ll, ll> p, ll x) { return p.first*x + p.second; }
pair<ll, ll> big() { return {XV, oo}; }

void test() {
	int n, q;
	cin >> n >> q;

    LiChao<ll, pair<ll, ll>, big, eval> t(-XV, XV);

    rep (_, 0, n) {
        ll l, r, a, b;
        cin >> l >> r >> a >> b;
        t.update(l, r, {a, b});
    }

    rep (_, 0, q) {
        int qt;
        cin >> qt;

        if (qt == 0) {
            ll l, r, a, b;
            cin >> l >> r >> a >> b;
            t.update(l, r, {a, b});
        }
        else {
            ll p;
            cin >> p;
            auto res = t.query(p);
            if (res >= oo / 2) cout << "INFINITY\n";
            else cout << res << "\n";
        }
    }
}
