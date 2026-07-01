#include<bits/stdc++.h>

using namespace std;


void dfs(int u,vector<bool> &vis,vector<vector<int>>&adj) {
    // we mark it as vistied 
    vis[u] =1;
    cout<<u<<" ";
    for(int v : adj[u]) {
        if(!vis[v]) {
            dfs(v,vis,adj);
        }
    }
}


void iterativeDFS(int u,vector<bool> &vis,vector<vector<int>> adj) {
    stack<int>st;
    st.push(u);
    while(!st.empty()) {
        int u = st.top();st.pop();
        vis[u] = 1;
        cout<<u<<" ";

        // push in reverse order 

        for(int i = adj[u].size() - 1; i >=0 ;i--) {
            if(!vis[adj[u][i]]) {
                st.push(adj[u][i]);
            }
        }
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
    vector<vector<int>> adj(V);

    for(int i = 0 ; i < E;i++) {
        int u , v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool>vis(V,0);
    iterativeDFS(0,vis,adj);
}