#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const char nl = '\n';
#define int ll

void fileIO(){
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
}

struct shash {
    int base, inv, mod, n;
    vector<ll> pw{1}, invpw{1}, pref{0};

    shash(){}
    shash(const string& s, int m, int b){
        base = b;
        mod = m;
        n = s.size();

        inv = 1;
        ll cur = base;
        int e = mod - 2;
        while (e){
            if (e & 1) inv = 1ll * inv * cur % mod;
            (cur *= cur) %= mod;
            e >>= 1;
        }

        for (int i = 0; i < n; ++i) {
            pw.push_back(pw.back() * base % mod);
            invpw.push_back(invpw.back() * inv % mod);
            pref.push_back((pref.back() + s[i] * pw[i]) % mod);
        }
    }

    ll get(int l, int r){
        return (pref[r + 1] - pref[l] + mod) * invpw[l] % mod;
    }
};

const int b1 = 31, b2 = 37; // randomize bases to avoid anti-hash tests
const int m1 = 1e9 + 7, m2 = 1e9 + 9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l, ll r){
    return uniform_int_distribution<ll>(l, r)(rng);
}

struct doublehash {
    shash hash1, hash2;

    doublehash(const string& s, int base1, int base2, int mod1, int mod2){
        hash1 = shash(s, mod1, base1);
        hash2 = shash(s, mod2, base2);
    }

    pair<ll, ll> get(int l, int r){
        return make_pair(hash1.get(l, r), hash2.get(l, r));
    }
};

const int N = 1e5 + 5;
int h[N];

void calc_xor_hash() {
    for (int i = 1; i < N; ++i) h[i] = rand(1, 1e18);   
}

void solve(){

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fileIO();
    solve();
}
