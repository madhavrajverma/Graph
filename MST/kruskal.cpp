#include<bits/stdc++.h>

using namespace std;

// basic implmentation 
// can replace with optimization

class DSU {
    public:
    vector<int>parent;
    DSU(int n) {
        parent.resize(n+1);
        for(int i = 1; i <= n;i++) {
            parent[i] = i;
        }
    }
    int findParent(int node) {
        if(parent[node] == node) return node;

        return findParent(parent[node]);
     }

     void Union(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);

        if(pu!= pv) {
            parent[pv] = pu; 
        }
     }
};



int main() {

ios::sync_with_stdio(false);
cin.tie(NULL);
#ifndef ONLINE_JUDGE
freopen("../input.txt", "r", stdin);
freopen("../output.txt", "w", stdout);
#endif
    int V, E;
    cin>>V>>E;
   // vector<vector<pair<int,int>>> adj(V);
   vector<vector<int>>edgeList(E,vector<int>(3));


    // count indegree

    //vector<int>deg(V,0);
    for(int i = 0 ; i < E;i++) {
        int u , v,w;
        cin>>u>>v>>w;
        edgeList[i] =  {w, u, v};
    }

    sort(edgeList.begin(),edgeList.end());

    DSU dsu(V);

    int sum = 0;
    for(auto edge : edgeList) {
        int wt = edge[0];
        int u = edge[1];
        int v = edge[2];
       
        int pu = dsu.findParent(u);
        int pv = dsu.findParent(v);

       if(pu == pv) continue;
       sum += wt;
       dsu.Union(u,v);

    }
    cout<<sum<<" ";
}