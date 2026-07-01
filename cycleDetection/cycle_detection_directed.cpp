#include<bits/stdc++.h>
using namespace std;


bool checkCycle(int u ,vector<bool>&vis, vector<bool>&inStack, vector<vector<int>> &adj) {
    vis[u] = true;
    inStack[u] = true;
    
    for(int v : adj[u]) {
        if(!vis[v]) {
            bool nbrContainCycle = checkCycle(v,vis,inStack,adj);
            if(nbrContainCycle) return true;
        }else if (inStack[v]) {
            return true;
        }
    }
    inStack[u] = false;
    return false;
}


bool solve(int n, vector<vector<int>>edges) {
    vector<bool>vis(n+1,0);
    vector<bool> inStack(n+1,0);
    vector<vector<int>>adj(n+1);
    
    
     // create a graph with edges 
    for(int i = 0;i<edges.size();i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u].push_back(v);
    }
    
    for(int u  = 1;u<=n;u++) {
        if(!vis[u]) {
            if(checkCycle(u,vis,inStack,adj)) return true;
        }
    }
    
    return false;
}