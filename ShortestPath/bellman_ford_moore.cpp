#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;
void bellmanFord(int V, vector<vector<pair<int,int>>>& adj, int source) {
    // relax all edge V- 1 times
    vector<int>dist(V,INF);
    dist[source] = 0;
    queue<int>q;
    vector<int>in_queue(V,0);

    q.push(source);
    in_queue[source] =1;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] =0;

        for(auto [w,v] : adj[u]) {
            
            if(dist[u] +w >= dist[v]) continue;
            dist[v] = dist[u] +w;
            if(!in_queue[v]) {
                q.push(v);
                in_queue[v] =1;
            }

            // if(in_queue[v]) continue;
            // q.push(v);
            // in_queue[v]=1;
        }
    }

  for (int u = 0; u < V; ++u)
            printf("SSSP(%d, %d) = %d\n", source, u, dist[u]);

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
