#include <bits/stdc++.h>
using namespace std;
using ll = long long;


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return uniform_int_distribution(l, r)(rng);
}

struct node {
    int val, priority;
    node *l, *r;

    node(int _val = 0) {
        val = _val;
        priority = rand(0, 1e8);
        l = r = nullptr;
    }
};

using nodep = node *;

pair<nodep, nodep> split(nodep v, int x) {
    if (!v) return {nullptr, nullptr};

    if (v->val <= x) {
        auto [vl, vr] = split(v->r, x);
        v->r = vl;
        return {v, vr};
    }

    auto [vl, vr] = split(v->l, x);
    v->l = vr;
    return {vl, v};
}

nodep merge(nodep vl, nodep vr) {
    if (!vl) return vr;
    if (!vr) return vl;

    if (vl->priority < vr->priority) {
        auto v = merge(vl->r, vr);
        vl->r = v;
        return vl;
    }

    auto v = merge(vl, vr->l);
    vr->l = v;
    return vr;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
