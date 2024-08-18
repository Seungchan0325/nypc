#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 500005;

ll N, U[MAXN], D[MAXN], PSUM[MAXN];

int main()
{
    cin >> N;
    for(ll i = 1; i <= N; i++) cin >> U[i];
    for(ll i = 1; i <= N; i++) cin >> D[i];

    if(D[N] != -1) PSUM[N] += D[N];
    for(ll i = N-1; i >= 1; i--) {
        PSUM[i] += PSUM[i+1];
        if(D[i] != -1) PSUM[i] += D[i];
    }

    ll used = 0;
    string s;
    for(ll i = 1; i <= N; i++) {
        if(U[i] != -1 && used + U[i] <= PSUM[i+1]) {
            used += U[i];
            s += '+';
        } else if(D[i] != -1 && used > PSUM[i+1]) {
            used -= D[i];
            s += '-';
        } else {
            s += '0';
        }
    }

    assert(used <= 0);
    assert(s.size() == N);

    cout << s;
}