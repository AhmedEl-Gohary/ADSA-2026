#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct seg_tree {
    const ll eye = 0; // identity value, depends on the opration

    int n, N;
    vector<ll> tree;

    seg_tree(int sz) {
        n = sz;
        N = 1;
        while (N < n) N *= 2; // find the lowes power of two greater than or equal n
        tree = vector(2 * N, eye);
    }

    ll f(ll a, ll b) { return a + b; }

    ll query(int l, int r, int v, int tl, int tr) {
        if (r < tl || l > tr) return eye;
        if (tl >= l && tr <= r) return tree[v];
        int tm = (tl + tr) / 2;
        return f(query(l, r, 2 * v, tl, tm), query(l, r, 2 * v + 1, tm + 1, tr));
    }

    void update(int i, ll val, int v, int tl, int tr) {
        if (i < tl || i > tr) return;
        if (tl == tr) {
            tree[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        int lv = 2 * v, rv = 2 * v + 1;
        update(i, val, lv, tl, tm);
        update(i, val, rv, tm + 1, tr);
        tree[v] = f(tree[lv], tree[rv]);
    }
};

/*
Sample case:
7
1 2 3 6 7 4 5
5
0 0
0 3
4 6
2 5
1 4
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); // fast I/O, always use
    int n;
    cin >> n;
    seg_tree st(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        st.update(i, x, 1, 0, n - 1);
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r; // zero-based
        cout << st.query(l, r, 1, 0, n - 1) << '\n';
    }
}
