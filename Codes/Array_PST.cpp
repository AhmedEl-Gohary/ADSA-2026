#include <bits/stdc++.h>
using namespace std;

template<class T, int N, int M>
struct PST {
#define L(v) tree[v].L
#define R(v) tree[v].R
#define val(v) tree[v].val

    struct node {
        int L, R;
        T val = eye;
    };

    int roots[M];
    node tree[N];
    const static T eye = 0;
    int timer = 0, n, ver = 0;

    int create_node() {
        assert(timer < N);
        return timer++;
    }

    int create_node(int vl, int vr) {
        assert(timer < N);
        L(timer) = vl, R(timer) = vr;
        val(timer) = f(val(vl), val(vr));
        return timer++;
    }

    T f(T x, T y) {
        return x + y;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) return;
        int tm = (tl + tr) / 2;
        L(v) = create_node();
        R(v) = create_node();
        build(L(v), tl, tm);
        build(R(v), tm + 1, tr);
    }

    void build(vector<T> &a, int v, int tl, int tr) {
        if (tl == tr) {
            val(v) = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        L(v) = create_node();
        R(v) = create_node();
        build(a, L(v), tl, tm);
        build(a, R(v), tm + 1, tr);
        val(v) = f(val(L(v)), val(R(v)));
    }

    T query(int l, int r, int v, int tl, int tr) {
        if (tl > r || tr < l) return eye;
        if (tl >= l && tr <= r) return val(v);
        int tm = (tl + tr) / 2;
        return f(query(l, r, L(v), tl, tm), query(l, r, R(v), tm + 1, tr));
    }

    T query(int version, int l, int r) {
        return query(l, r, roots[version], 0, n - 1);
    }

    int update(int i, int val, int v, int tl, int tr) {
        if (tl == tr) {
            int u = create_node();
            val(u) = val(v) + val;
            return u;
        }
        int tm = (tl + tr) / 2;
        if (i <= tm) return create_node(update(i, val, L(v), tl, tm), R(v));
        return create_node(L(v), update(i, val, R(v), tm + 1, tr));
    }

    int update(int version, int i, int val) {
        int u = update(i, val, roots[version], 0, n - 1);
        roots[++ver] = u;
        return ver;
    }

    int dfs(int vl, int vr, int tl, int tr, int k) {
        if (tl == tr) return tl;
        int cnt_l = val(L(vr)) - val(L(vl));
        int tm = (tl + tr) / 2;
        if (cnt_l >= k) return dfs(L(vl), L(vr), tl, tm, k);
        return dfs(R(vl), R(vr), tm + 1, tr, k - cnt_l);
    }

    int dfs(int ver_l, int ver_r, int k) {
        return dfs(roots[ver_l], roots[ver_r], 0, n - 1, k);
    }

    PST(int _n) {
        n = _n;
        build(create_node(), 0, n - 1);
    }

    PST(vector<int> &a) {
        n = a.size();
        build(a, create_node(), 0, n - 1);
    }
};
