#include<bits/stdc++.h>

using namespace std;



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

    vector<int>deg(V,0);
    for(int i = 0 ; i < E;i++) {
        int u , v;
        cin>>u>>v;
        adj[u].push_back(v);
        // adj[v].push_back(u); // directed graph
        deg[v]++;
    }

    queue<int>q;
    // push all 0 degree node fitst
    for(int i = 0 ; i < V;i++) {
        if(!deg[i]) {
            q.push(i);
        }
    }


    // storing topo sort

    vector<int>toposort;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        toposort.push_back(u);

        for(int v : adj[u]) {
            deg[v]--;
            if(deg[v] == 0) {
                q.push(v);
            } 
        }
    }

    for(int e : toposort) cout<<e<<" ";
}