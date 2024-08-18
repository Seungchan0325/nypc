#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    map<int, int> xs, ys;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        xs[x]++;
        ys[y]++;
    }

    int cnt = 0;
    for(auto [key, val] : xs) {
        if(val >= 2) cnt++;
    }
    for(auto [key, val] : ys) {
        if(val >= 2) cnt++;
    }
    cout << cnt;
}