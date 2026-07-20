#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int cycleStart  = -1, cycleEnd = -1;

bool dfs(int u ,vector<vector<int>> & adj ,vector<int>& vis, vector<int>&par,int parent) {
    vis[u] = 1;
    par[u] = parent;
    for(int v : adj[u]) {
        if(!vis[v]) {
          if(dfs(v,adj,vis,par,u)) return true;
        }else if(v != parent) {
            cycleStart = v;
            cycleEnd = u;
            return true;
        }
    }
    return false;
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

    bool isAns = false;
    vector<int>par(n+1,-1);
    for(int i = 1;  i <=n ;i++) {
        if(!vis[i]) {
           if(dfs(i,adj,vis,par,-1)) {
            isAns = true;
            break;
           }
        }
    }

    if(isAns) {
        vector<int>cycle;
        cycle.push_back(cycleStart);
        int cur = cycleEnd;

        while(cur != cycleStart) {
            cycle.push_back(cur);
            cur = par[cur];
        }
        cycle.push_back(cycleStart);
        cout<<cycle.size()<<"\n";
        for(int x : cycle) {
            cout<<x<<" ";
        }
    }
    else cout<<"IMPOSSIBLE";

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
PROBLEM : Round Trip
PATTERN : Cycle Detection (Undirected Graph)
===============================================================================

Recognition:
- Find any cycle in an undirected graph.

Concept:
- DFS builds a DFS tree.
- Ignore the edge to the parent.
- Visited neighbor (not parent) => Cycle exists.
- Use parent[] to reconstruct the cycle.

Core Idea:
A non-parent back edge creates an alternate path,
forming a cycle.

Algorithm:
- Start DFS from every unvisited node.
- Track parent of each node.
- If visited neighbor != parent:
      cycleStart = neighbor
      cycleEnd = current
- Backtrack using parent[] to print the cycle.

Graph Concept:
- Cycle Detection in Undirected Graph
- Parent edge is not a cycle.
- A visited non-parent neighbor implies a cycle.

Complexity:
Time  : O(V + E)
Space : O(V)

Remember:
- Handle disconnected graphs.
- Recurse on the neighbor (dfs(v), not dfs(u)).
- Reverse the reconstructed path before printing.
===============================================================================
*/