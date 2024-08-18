#include <bits/stdc++.h>

using namespace std;

bool check(int a, int b, int n)
{
    a -= n;
    b -= n;
    return (a + b) > 2*n;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int a, b;
        cin >> a >> b;
        if(a < b) swap(a, b);

        if(a > 3*b) {
            cout << "-1\n";
            continue;
        }
        
        int lo = 0;
        int hi = min(a, b);
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(check(a, b, mid)) lo = mid;
            else hi = mid;
        }

        cout << hi << "\n";
    }
}