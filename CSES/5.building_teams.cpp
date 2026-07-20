
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

bool dfs(int u , int col,vector<vector<int>> & adj ,vector<int>& vis, vector<int>&color) {
    vis[u] = 1;
    color[u] = col;

    for(int v : adj[u]) {
        if(!vis[v]) {
           if(!dfs(v,3-col,adj,vis,color)) return false;
        }else if(color[v] == col) {
            return false;
        }
    }
    return true;
}
void solve() {
    int n , m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);

    for(int i = 0 ; i < m ;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int>vis(n+1,0);
    vector<int>color(n+1,-1);

    bool isAns = true;

    for(int i = 1;  i <=n ;i++) {
        if(!vis[i]) {
           if(!dfs(i,1,adj,vis,color)) {
            isAns = false;
            break;
           }
        }
    }

    if(!isAns) {
        cout<<"IMPOSSIBLE"<<endl;
        return;
    }

    for(int i = 1; i <=n;i++) {
        cout<<color[i]<<" ";
    }

  }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    solve();

    return 0;
}



/*
===============================================================================
PROBLEM : Building Teams
PATTERN : Bipartite Graph / Two Coloring
===============================================================================

Recognition:
- Divide graph into 2 groups.
- Adjacent vertices must belong to different groups.

Core Idea:
- Every edge enforces:
        color[u] != color[v]
- DFS/BFS propagates opposite colors.
- If an edge connects same-colored vertices -> Impossible.

Algorithm:
1. Traverse every connected component.
2. Assign first node color = 1.
3. DFS/BFS:
      - Unvisited neighbor -> assign opposite color (3-color).
      - Visited neighbor with same color -> Not Bipartite.

Graph Concept:
- Bipartite Graph
- A graph is bipartite iff it has NO odd cycle.

Complexity:
Time  : O(V + E)
Space : O(V)

Remember:
- Handle disconnected graphs.
- Color before exploring neighbors.
- Start DFS/BFS from every unvisited node.
===============================================================================
*/
