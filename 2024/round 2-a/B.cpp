#include <bits/stdc++.h>

using namespace std;

const int MAXM = 200005;

int N, M, Q;
vector<int> h, v, u, d;

vector<bool> solve(vector<int> line, vector<tuple<int, int, int>> se)
{
    sort(se.begin(), se.end());
    sort(line.begin(), line.end());
    vector<bool> ans(se.size(), true);
    int lst = 0;
    for(auto [s, e, idx] : se) {
        while(lst < line.size() && line[lst] < s) lst++;
        if(lst == line.size()) break;
        if(line[lst] <= e) {
            ans[idx] = false;
        }
    }
    return ans;
}

int main()
{
    cin >> N >> M >> Q;
    for(int i = 1; i <= M; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        if(r1 == r2) v.push_back(r1);
        else if(c1 == c2) h.push_back(c1);
        else if(r1 + c1 == r2 + c2) u.push_back(r1 + c1);
        else if(r1 - c1 == r2 - c2) d.push_back(r1 - c1);
        else assert(0);
    }

    vector<tuple<int, int, int>> vs, hs, us, ds;
    for(int i = 0; i < Q; i++) {
        int rs, cs, re, ce;
        cin >> rs >> cs >> re >> ce;

        vs.emplace_back(rs, re, i);
        hs.emplace_back(cs, ce, i);
        us.emplace_back(rs + cs, re + ce, i);
        ds.emplace_back(rs - cs, re - ce, i);
    }

    for(auto& [s, e, idx] : vs) {
        if(s > e) swap(s, e);
    }
    for(auto& [s, e, idx] : hs) {
        if(s > e) swap(s, e);
    }
    for(auto& [s, e, idx] : us) {
        if(s > e) swap(s, e);
    }
    for(auto& [s, e, idx] : ds) {
        if(s > e) swap(s, e);
    }

    auto ansv = solve(v, vs);
    auto ansh = solve(h, hs);
    auto ansu = solve(u, us);
    auto ansd = solve(d, ds);

    for(int i = 0; i < Q; i++) {
        bool ans = ansv[i] && ansh[i] && ansu[i] && ansd[i];
        cout << ans << "\n";
    }
}