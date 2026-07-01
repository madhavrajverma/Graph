#include<bits/stdc++.h>
using namespace std;

// using bfs 
bool detect(int node, vector<int> adj[], vector<bool> & vis) {
    
    queue<pair<int,int>>q;
    q.push({node,-1});
    vis[node] =1; 
    
    while(!q.empty()) {
        auto node = q.front();
        q.pop();
        int u = node.first;
        int par = node.second;
        
        for(int v : adj[u]) {
            if(!vis[v]) {
                vis[v] =1;
                q.push({v,u});
            }else if(par != v) {
                return true;
            }
         }
    }
    return false;
}



// can also do using dfs
bool detect(int u, vector<int> adj[], vector<bool> & vis,int par) {
    vis[u] =1;
    for(int v : adj[u]) {
        if(!vis[v]) {
            if(detect(v,adj,vis,u)) return true;
        }else if (par != v) {
            return true;
        }
    }
    return false;
}

bool iscycle(vector<int> adj[], int n) {
    vector<bool> visited(n,false);
    for(int i = 1;i<n;i++) {
        if(!visited[i]) {
            if(detect(i,adj, visited)) return true;
        }
    }
    return false;
}


bool  solve(int n, vector<vector<int> > edges) {
    vector<int> adj[n+1];
    
    // create a graph with edges 
    for(int i = 0;i<edges.size();i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
      return iscycle(adj, n+1);
}