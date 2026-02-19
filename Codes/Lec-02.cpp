#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const char el = '\n', sp = ' ';

const int mod = 1e9 + 7;

struct PST {
    static ll f(ll a, ll b) {
        return a + b;
    }

    struct node {
        node *l, *r;
        ll sum;

        node(ll val) : l(nullptr), r(nullptr), sum(val) {
        }

        node(node *l, node *r) : l(l), r(r), sum(0) {
            if (l) sum = f(sum, l->sum);
            if (r) sum = f(sum, r->sum);
        }
    };

    node *build(int tl, int tr, vector<int> &a) {
        if (tl == tr) return new node(a[tl]);
        int tm = (tl + tr) / 2;
        return new node(build(tl, tm, a), build(tm + 1, tr, a));
    }

    ll query(node *v, int tl, int tr, int l, int r) {
        if (l > tr || r < tl) return 0;
        if (l <= tl && tr <= r) return v->sum;
        int tm = (tl + tr) / 2;
        return f(query(v->l, tl, tm, l, r), query(v->r, tm + 1, tr, l, r));
    }

    node *update(node *v, int tl, int tr, int idx, ll val) {
        if (tl == tr) return new node(val);
        int tm = (tl + tr) / 2;
        if (idx <= tm) return new node(update(v->l, tl, tm, idx, val), v->r);
        return new node(v->l, update(v->r, tm + 1, tr, idx, val));
    }

    int n;
    vector<node *> roots;

    PST(vector<int> &a) {
        n = a.size();
        roots.push_back(build(0, n - 1, a));
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &i: a) cin >> i;
    PST pst(a);
    while (q--) {
        int t, k;
        cin >> t >> k, k--;
        if (t == 1) {
            int val, idx;
            cin >> idx >> val, idx--;
            pst.roots[k] = pst.update(pst.roots[k], 0, n - 1, idx, val);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r, l--, r--;
            cout << pst.query(pst.roots[k], 0, n - 1, l, r) << el;
        } else {
            pst.roots.push_back(pst.roots[k]);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
