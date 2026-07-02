#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;
vector<int> dijkstraOriginal(int V, vector<vector<pair<int,int>>>& adj, int source) {
   
    vector<int> dist(V, INF);
    dist[source] = 0; // this is imp

    priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;

    pq.push({0,source});

    while (!pq.empty()) {
      // now 
      auto [wt,u] = pq.top();
      pq.pop();


      if(wt > dist[u]) continue; // skip this if no update  stale entry, skip

      for(auto &[w,v] : adj[u]) {
        if(dist[u] + w >= dist[v]) continue;
        dist[v] = dist[u] + w;
        pq.push({dist[v],v});
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
