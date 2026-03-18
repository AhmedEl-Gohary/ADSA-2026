#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double PI = acos(-1);

using cd = complex<double>;

/*
This is the version that was explained in the lecture.
It explicitly returns the array of samples.
Notice that we don't need to pass the array of points to evaluate as we can infer them from the array size.
 */
vector<cd> fft_explicit_return(vector<cd> &a) {
    if (a.size() == 1) return {a[0]};

    int n = a.size();
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    auto f0 = fft_explicit_return(a0), f1 = fft_explicit_return(a1);
    vector<cd> f(n);
    cd w(cos(2 * PI / n), sin(2 * PI / n)), wi = 1;
    for (int i = 0; i < n / 2; i++) {
        f[i] = f0[i] + wi * f1[i];
        f[i + n / 2] = f0[i] - wi * f1[i];
        wi = wi * w;
    }
    return f;
}

/*
This is a more optimized version that does the FFT in place.
It also handles the case when we want to find the IFFT.
 */
void fft(vector<cd> &a, bool invert) {
    if (a.size() == 1) return;

    int n = a.size();
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);
    cd w(cos(2 * PI / n), sin(2 * PI / n)), wi = 1;
    if (invert) w = conj(w);
    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + wi * a1[i];
        a[i + n / 2] = a0[i] - wi * a1[i];
        wi = wi * w;
    }
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size() - 1) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    for (auto &x: fa) x /= n;

    vector<ll> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());

    result.resize(a.size() + b.size() - 1);
    return result;
}

void solve() {
    vector<ll> p = {1, 1}, res = {1};
    for (int i = 0; i < 6; i++) {
        res = multiply(res, p);
        for (int x: res) cout << x << ' ';
        cout << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
