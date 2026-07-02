#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;
void bellmanFord(int V, vector<vector<pair<int,int>>>& adj, int source) {
    // relax all edge V- 1 times
    vector<int>dist(V,INF);
    dist[source] = 0;
   
    for(int i = 0 ; i< V;i++) { // V-1 times iteration 
            bool updated = false;
        for(int u = 0 ; u < V ; u++) { // traverse of vertice 
            for(auto [w,v] : adj[u]) {
                // check also it is not INF 
                if(dist[u] == INF) continue; // if not INF + w may overflow
                 
                if(dist[u] + w  < dist[v])  {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
        }
        if(!updated) break; // just for early temrination 
    }
    // check for cycle
    bool hasNegativeCycle = false;
    for(int u = 0 ; u < V-1; u++) {
        for(auto [w,v] : adj[u]) {
            if(dist[v] == INF) continue;

            if(dist[u] + w < dist[v])  {
                hasNegativeCycle = true;
                break;
            }
        }
    }

   if (hasNegativeCycle)
        printf("Negative Cycle Exist\n");
    else {
        for (int u = 0; u < V; ++u)
            printf("SSSP(%d, %d) = %d\n", source, u, dist[u]);

}
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
bellmanFord(V,adj,src);

}
