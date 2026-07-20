#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;




void solve() {
    int n , m;
    cin>>n>>m;

    vector<string>adj(n);

    for(int i = 0 ; i  < n ; i++) {
        cin>>adj[i];
    }
    // first compute bfs on monstsers
    queue<pair<int,int>>q;
    vector<vector<int>> monsterTime(n,vector<int>(m,INF));
    
    
    int sr,sc;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m;j++) {
            if(adj[i][j] == 'M') {
                monsterTime[i][j] = 0;
                q.push({i,j});
            }

            if(adj[i][j] == 'A') {
                sr = i;
                sc = j;
            }
        }
    }
    int dr[] = {-1,1,0,0};
    int dc[] = {0,0,-1,1};

    while(!q.empty()) {
        auto [r,c] = q.front();
        q.pop();
        
        for(int i = 0;i < 4;i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if(nr < 0 || nc < 0 ||nr >=n || nc >=m) continue;

            if(adj[nr][nc] == '#' || monsterTime[nr][nc] != INF) continue;

            monsterTime[nr][nc] = monsterTime[r][c] + 1;

            q.push({nr,nc});
        }
    }

    vector<vector<int>> player(n,vector<int>(m,INF));
    vector<vector<pair<int,int> >> par(n,vector<pair<int,int> >(m,make_pair(-1,-1)));
    vector<vector<char>> dir(n,vector<char>(m));

    char move[] = {'U','D','L','R'};

    bool isAns = false;
    q.push({sr,sc});
    player[sr][sc] = 0;
    int er, ec;
    while(!q.empty()) {
        auto [r,c] = q.front();
        q.pop();

        if(r == 0 || r == n-1 || c == 0 || c == m-1) {
            er = r;
            ec = c;
            isAns  = true;
            break;
        }

        for(int i = 0;i < 4;i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if(nr < 0 || nc < 0 ||nr >=n || nc >=m) 
                continue;

            if(adj[nr][nc]=='#' || adj[nr][nc]=='M')
                 continue;

            if(player[nr][nc]!=INF)
                continue;

            if(player[r][c]+1>=monsterTime[nr][nc])
                continue;

            player[nr][nc] = player[r][c] + 1;
            dir[nr][nc] = move[i];
            par[nr][nc] = {r,c};
            q.push({nr,nc});
        }
    }



    if(isAns) {
        string ans;
        int r = er;
        int c = ec;

        while(!(r == sr && c == sc)) { // most important thing to remember so keep in mind this 

            ans += dir[r][c];

            auto [pr, pc] = par[r][c];

            r = pr;
            c = pc;
        }
        reverse(ans.begin(), ans.end());
        cout<<"YES\n";
        cout<<ans.size()<<"\n";
        cout<<ans<<"\n";

    }else {
         cout<<"NO\n";
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
PROBLEM : Monsters
PATTERN : Multi-Source BFS + Constrained BFS
===============================================================================

Recognition:
- Multiple sources spread simultaneously.
- Escape before a hazard reaches.

Concept:
- BFS computes minimum arrival time.
- Multi-Source BFS gives earliest time from ANY source.
- Player moves only if:
      playerTime < monsterTime.

Core Idea:
Precompute monster times.
Then run BFS for the player using monster times as constraints.

Algorithm:
1. Multi-Source BFS from all monsters.
2. Compute monsterTime[][].
3. BFS from player.
4. Move only if:
      playerTime + 1 < monsterTime[next].
5. Store parent + direction to reconstruct path.

Graph Concept:
- Multi-Source BFS.
- Time can be modeled as shortest distance.
- Precompute hazards, then plan safely.

Complexity:
Time  : O(N × M)
Space : O(N × M)

Remember:
- Push all monsters initially.
- Equal arrival time is NOT safe.
- Handle starting boundary case.
===============================================================================
*/