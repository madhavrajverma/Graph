#include<bits/stdc++.h>

using namespace std;

vector<int>topoSort;
void findTopo(int u, vector<int>& vis, vector<vector<int>>adj) {
    vis[u] = 1;
    for(int v : adj[u]) {
        if(!vis[v]) {
            findTopo(v,vis,adj);
        }
    }
    topoSort.push_back(u);
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
    vector<vector<int>> adj(V);
    // count indegree

    //vector<int>deg(V,0);
    for(int i = 0 ; i < E;i++) {
        int u , v;
        cin>>u>>v;
        adj[u].push_back(v);
        // adj[v].push_back(u); // directed graph
      //  deg[v]++;
    }

    vector<int>vis(V,0);
    for(int u = 0; u< V;u++) {
        if(!vis[u]) {
            findTopo(u,vis,adj);
        }
    }
    reverse(topoSort.begin(),topoSort.end());
    for(int x : topoSort) cout<<x<<" ";

}