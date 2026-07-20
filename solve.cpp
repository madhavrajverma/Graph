#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    // dist[i][j] = shortest distance from i to j
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));

    // Distance from a node to itself is 0
    for (int i = 1; i <= n; i++)
        dist[i][i] = 0;

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        // Keep the minimum if multiple edges exist
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist[i][k] == INF) continue;

            for (int j = 1; j <= n; j++) {
                if (dist[k][j] == INF) continue; // small checks

                dist[i][j] = min(dist[i][j],
                                 dist[i][k] + dist[k][j]);
            }
        }
    }

  
    while (q--) {
        int u, v;
        cin >> u >> v;

        if (dist[u][v] == INF)
            cout << -1 << "\n";
        else
            cout << dist[u][v] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    solve();

    return 0;
}