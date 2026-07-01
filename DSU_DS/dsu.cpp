#include<bits/stdc++.h>


// coding minutes


using namespace std;


// basic implmentation 
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

// this basic implmentation worst case it becomes O(n)
// optimaztion 


// Optimization 1 : Path compression
//Whenever we perform find(), we make every visited node directly point to the root.

// optmixzation 3 : Union by size
// Instead of storing the rank, store the number of nodes in each set.

class DSU1 {
    public:
    vector<int>parent;
    vector<int>size;
    DSU1(int n) {
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i = 1; i <= n;i++) {
            parent[i] = i;

        }
    }

    int findParent(int node) {
        if(parent[node] == node) return node;

        return parent[node] = findParent(parent[node]);
     }

     void Union(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        
        if(pu == pv) return;

        if(size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        }else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
     }
};


// Union by Rank
// optimization 2: Union by Rank
// Always attach the shorter tree under the taller tree.

class DSU2 {
    public:
    vector<int>parent;
    vector<int>rank;


    DSU2(int n) {
        parent.resize(n+1);
        rank.resize(n+1,1);
        for(int i = 1; i <= n;i++) {
            parent[i] = i;
        }
    }

    int findParent(int node) {
        if(parent[node] == node) return node;

        return parent[node] = findParent(parent[node]);
     }

     void Union(int u, int v) {
        int pu = findParent(u);
        int pv = findParent(v);
        
        if(pu == pv) return;
        if(rank[pu]  < rank[pv]) {
            parent[pu] = pv;
        }else if(rank[pv] < rank[pu]) {
            parent[pv] = pu;
        }else {
            parent[pv] = pu;
            rank[pu]++;
        }
     }
};




int main() {

}


