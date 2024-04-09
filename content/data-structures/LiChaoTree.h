#pragma once
template<class T, class F, F (*big)(), T (*eval)(F, ll)>
struct LiChao {
    static constexpr T oo = numeric_limits<T>::max();
    struct node { F f; node *l = 0, *r = 0; };
    ll tlo, thi;
    node* root = 0;
    LiChao(ll lo, ll hi): tlo(lo), thi(hi) {}
    T query(ll x, node* u, ll lo, ll hi) {
        if (!u) return oo;
        if (lo + 1 == hi) return eval(u->f, x);
        ll mid = lo + (hi - lo) / 2;
        auto res = x < mid ? query(x, u->l, lo, mid)
                           : query(x, u->r, mid, hi);
        return min(eval(u->f, x), res);
    }
    T query(ll x) { return query(x, root, tlo, thi); }
    void update(ll a, ll b, F f, node*& u, ll lo, ll hi) {
        if (b <= lo || hi <= a) return;
        ll mid = lo + (hi - lo) / 2;
        if (a <= lo && hi <= b) {
            if (!u) { u = new node({f}); return; }
            bool cl = eval(f, lo) < eval(u->f, lo);
            bool cm = eval(f, mid) < eval(u->f, mid);
            if (cm) swap(u->f, f);
            if (lo + 1 == hi) return;
            if (cl != cm) update(a, b, f, u->l, lo, mid);
            else update(a, b, f, u->r, mid, hi);
            return;
        }
        if (!u) u = new node({big()});
        update(a, b, f, u->l, lo, mid);
        update(a, b, f, u->r, mid, hi);
    }
    void update(ll a, ll b, F f) { return update(a, b, f, root, tlo, thi); }
};
