#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

using ll = long long;

ll N, A[MAXN], DP[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    DP[1] = A[1];
    for(int i = 2; i <= N; i++) {
        DP[i] = min(DP[i-1]+A[i], DP[i-2] + max(A[i-1], A[i]));
    }

    cout << DP[N];
}