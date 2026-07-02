#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;
vector<int> dijkstraOriginal(int V, vector<vector<pair<int,int>>>& adj, int source) {
   
    vector<int> dist(V, INF);
    dist[source] = 0;

    set<pair<int,int>> pq;                     // (distance, vertex)
    for (int u = 0; u < V; u++)
        pq.insert({dist[u], u});

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin()); // this is finalized remove from the set

        for (auto& [w,v] : adj[u]) {
            if (dist[u] + w >= dist[v]) continue;   // not an improvement
            pq.erase({dist[v], v});                 // remove stale entry
           // pq.erase(pq.find({dist[v], v})); 
            dist[v] = dist[u] + w;                  // relax
            pq.insert({dist[v], v});                // insert updated entry
        }
    }
    return dist;
}



int main() {
ios::sync_with_stdio(false);
cin.tie(NULL);
#ifndef ONLINE_JUDGE
freopen("../input.txt", "r", stdin);
freopen("../output.txt", "w", stdout);
#endif

int V, E;
cin>>V>>E;
vector<vector<pair<int,int>>>adj(V);

for(int i = 0 ; i < E;i++) {
    int u , v,w;
    cin>>u>>v>>w;
    adj[u].push_back({w,v});
}
int src;
cin>>src;
vector<int>dist = dijkstraOriginal(V,adj,src);
for (int u = 0; u < V; u++)
        cout << "SSSP(" << src << ", " << u << ") = " << dist[u] << "\n";


}
