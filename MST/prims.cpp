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
    vector<vector<pair<int,int>>> adj(V);
    // count indegree

    //vector<int>deg(V,0);
    for(int i = 0 ; i < E;i++) {
        int u , v,w;
        cin>>u>>v>>w;
        adj[u].push_back({w,v});
        adj[v].push_back({w,u}); // directed graph
      
    }

    vector<bool> vis(V,false); // it means we have already included this in set

    int sum = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>> , greater<pair<int,int>> > pq;
    pq.push({0,0});

    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();

        int wt = node.first;
        int u = node.second;

        if(vis[u])
            continue;

        vis[u] = 1;
       
        sum += wt;

        for(auto [wt,v] : adj[u]) {
           if(!vis[v]) {
             pq.push({wt,v});
           }
        }
        return sum;
    }





}