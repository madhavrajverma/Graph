
#include<bits/stdc++.h>
using namespace std;

// 


void dfs(int r , int c, vector<vector<char>>&adj, vector<vector<bool>> & vis) {

    int n = adj.size();
    int m = adj[0].size();

    vis[r][c] =1;

    int dr[] = {-1,1,0,0};
    int dc[] = {0,0,1,-1};


    for(int d = 0 ; d < 4 ;d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];

        if(nr < 0 || nc <  0 || nr >= n || nc >= m) continue;

        if(vis[nr][nc] || adj[nr][nc] =='#') continue;


        dfs(nr,nc,adj,vis);

    }
}



void solve() {
    int n , m ;
    cin>>n>>m;
    vector<vector<char>> adj(n, vector<char>(m,0));

    for(int i = 0 ; i < n ;i++) {
        for(int j = 0; j < m;j++) {
            char ch;
            cin>>ch;
            adj[i][j] = ch; 
        }
    }
    int cnt = 0;
     vector<vector<bool>> vis(n, vector<bool>(m,0));
     
    for(int i = 0 ; i < n;i++) {
        for(int j = 0;j<m;j++) {
            if(adj[i][j] == '.' && !vis[i][j]) {
                cnt++;
                dfs(i,j,adj,vis);
              
            }
        }
    }

    cout<<cnt<<" ";
}

int main()
{
 
 ios::sync_with_stdio(false);
 cin.tie(NULL);

 #ifndef ONLINE_JUDGE
 freopen("input.txt", "r", stdin);
 freopen("output.txt", "w", stdout);
 #endif


 solve();


return 0;
}


/*
PATTERN:
Connected Components in Grid (Flood Fill)

Algorithm:
DFS / BFS

Core Idea:
Each '.' cell is a graph node.
All connected '.' cells belong to one room.
Start DFS/BFS from every unvisited '.' to discover one complete room.

Observation:
Answer = Number of times DFS/BFS is started.

Implementation:
1. Traverse every cell.
2. If cell == '.' and unvisited:
      rooms++
      DFS/BFS(cell)
3. Explore only 4 directions.

Remember:
- Grid is an implicit graph (don't build adjacency list).
- Mark visited immediately.
- Handle boundary checks.
- Ignore '#' cells.
- Iterate over the entire grid (multiple components).

Complexity:
Time  : O(N × M)
Space : O(N × M)

Common Mistakes:
- Forgetting boundary checks.
- Exploring 8 directions instead of 4.
- Visiting '#' cells.
- Recursive DFS may overflow for very large grids; iterative DFS/BFS is safer.
*/