#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150005;
const int LOGN = 18;

int N, M, D[MAXN], S[MAXN], E[MAXN], depth[MAXN], sparse[MAXN][LOGN+1];
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    for(int i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
    }
    for(auto v : graph[u]) {
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        sparse[v][0] = u;
        dfs(v, u);
    }
}

int par(int u, int dep)
{
    for(int i = 0; i <= LOGN; i++) {
        if(dep&(1<<i)) {
            u = sparse[u][i];
        }
    }
    return u;
}

int LCA(int u, int v)
{
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int i = 0; i <= LOGN; i++) {
        if(diff&(1<<i)) {
            u = sparse[u][i];
        }
    }

    if(u == v) return u;

    for(int i = LOGN; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }

    return sparse[u][0];
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> D[i];
    }
    for(int i = 1; i < N; i++) {
        // cin >> S[i] >> E[i];
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1; i <= M; i++) {
        cin >> S[i] >> E[i];
    }
    
    dfs(1, -1);

    queue<int> que[10], tmp[10];
    for(int i = 1; i <= M; i++) {
        que[0].push(i);
    }

    for(int i = N; i >= 0; i--) {
        for(int j = 0; j < 10; j++) {
            while(!que[j].empty()) {
                auto idx = que[j].front(); que[j].pop();

                int u = S[idx];
                int v = E[idx];

                int lca = LCA(u, v);
                int len = depth[u] + depth[v] - depth[lca] + 1;
                if(len < i) {
                    tmp[0].push(idx);
                    continue;
                }

                if(depth[v] - depth[lca] >= i) {
                    int cur = par(v, i);
                    tmp[D[cur]].push(idx);
                } else {
                    int cur = par(u, len - i - 1);
                    tmp[D[cur]].push(idx);
                }
            }
        }
        for(int j = 0; j < 9; j++) {
            que[j] = tmp[j];
            tmp[j] = queue<int>();
        }
    }

    for(int i = 0; i < 10; i++) {
        while(!que[i].empty()) {
            cout << que[i].front() << "\n";
            que[i].pop();
        }
    }
}