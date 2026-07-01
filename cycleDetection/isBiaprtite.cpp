#include<bits/stdc++.h>
using namespace std;

// using dfs
bool checkBipartite(int u , vector<int>&vis, int color, vector<vector<int>> &adj) {
    vis[u] = color;
    
    for(int v : adj[u]) {
        if(vis[v] == -1) {
            bool isB = checkBipartite(v,vis,1-color,adj);
            if(!isB) return false;
        }else if(vis[v] == color) { 
            return false;
        }
    }
     return true;
}

// using bfs




bool checkBiparitebfs(int u, vector<int> & vis, vector<vector<int>> & adj) {

    queue<pair<int,int>>q;
    q.push({u,0});
    vis[u] = 0;

    while (!q.empty()){
        auto node  = q.front();
        q.pop();
        int u = node.first;
        int color = node.second;
        for(int v : adj[u]) {
          if(vis[v] == -1) {
            vis[v] = 1-color;
            q.push({v,1-color});
          }else if(color == vis[v]) {
            return false;
          }
        }
    }
    return true;
}
 

 


bool isBipartite(vector<vector<int>> graph){
    /// can be done by using bfs and dfs both
    int V = graph.size();
    vector<int>vis(V,-1);
    
    for(int u = 0 ; u < V;u++) {
        if(vis[u] ==-1) {
            if(!checkBipartite(u,vis,0,graph)) return false;
        }
    }
    
    return true;
}