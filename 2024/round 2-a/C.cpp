#include <bits/stdc++.h>

using namespace std;

struct Train
{
    int s, d, ts, td;
};

struct PBS
{
    int lo, hi;
    vector<tuple<int, int, int>> problems;
};

const int MAXN = 100005;
const int MAXQ = 100005;
const int MAXT = 1000000005;

bool chk[MAXN];
int N, M, K, Q, ans[MAXQ];
vector<tuple<int, int, int>> graph[MAXN];

vector<int> dijkstra(int t)
{
    priority_queue<pair<int, int>> pq;
    pq.emplace(t, K);
    vector<int> dist(N + 1, -1);
    dist[K] = t;

    while(!pq.empty()) {
        auto [time, u] = pq.top(); pq.pop();
        if(dist[u] > time) continue;
        for(auto [v, td, ts] : graph[u]) {
            if(time >= td && ts > dist[v]) {
                pq.emplace(ts, v);
                dist[v] = ts;
            }
        }
    }

    return dist;
}

int main()
{
    cin >> N >> M >> K >> Q;
    for(int i = 0; i < M; i++) {
        int s, ts, d, td;
        cin >> s >> ts >> d >> td;
        graph[d].emplace_back(s, td, ts);
    }
    PBS start;
    start.lo = -1;
    // start.hi = 30;
    start.hi = MAXT + 5;
    for(int i = 0; i < Q; i++) {
        int s, t;
        cin >> s >> t;
        start.problems.emplace_back(s, t, i);
    }

    queue<PBS> q;
    q.push(start);
    while(!q.empty()) {
        auto [lo, hi, problems] = q.front(); q.pop();
        if(problems.empty()) continue;
        if(lo + 1 >= hi) {
            for(auto [s, t, idx] : problems) {
                ans[idx] = hi;
            }
            continue;
        }

        int mid = (lo + hi) / 2;
        auto dist = dijkstra(mid);

        PBS l, r;
        l.lo = lo;
        l.hi = mid;

        r.lo = mid;
        r.hi = hi;

        for(auto [s, t, idx] : problems) {
            if(dist[s] >= t) l.problems.emplace_back(s, t, idx);
            else r.problems.emplace_back(s, t, idx);
        }

        q.push(l);
        q.push(r);
    }

    for(int i = 0; i < Q; i++) {
        if(ans[i] >= MAXT) cout << -1 << "\n";
        else cout << ans[i] << "\n";
    }
}