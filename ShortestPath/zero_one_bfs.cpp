#include<bits/stdc++.h>

using namespace std;

// Problem is

/*
The grid problem :
Cells marked . are "corridor" cells — moving into them costs 1 unit.
Cells marked with any letter A-Z are "free" cells — moving into them costs 0 units (you can walk through/between letter cells for free).
# cells are walls — impassable.
You start on any A cell (multiple sources) and want the shortest path to any B cell (multiple destinations).
Movement is in 4 directions: N/E/S/W.


input:


5 6
AA.#..
..#...
.CC...
...C.B
......

o/p : 3

*/


int main() {
ios::sync_with_stdio(false);
cin.tie(NULL);
#ifndef ONLINE_JUDGE
freopen("../input.txt", "r", stdin);
freopen("../output.txt", "w", stdout);
#endif

int R , C;

cin>>R>>C;

//vector<vector<int>>(R, vector<int>(C,0));

vector<string>grid(R);

for(int i = 0 ; i < R; i++) cin>>grid[i];

// we have to do BFS

vector<vector<int>> dist(R, vector<int>(C,INT_MAX)); // we use as a visited matrxi

deque<pair<int,int>> dq;


int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

// it is also multi source so insert all A's
for(int r = 0 ; r < R; r++) {
    for(int c = 0 ;c< C; c++) {
        if(grid[r][c] == 'A') {
            dist[r][c] = 0;
            dq.push_back({r,c});
        }
    }
}

int ans = -1;
while(!dq.empty()) {
    auto [r,c] = dq.front();dq.pop_front();

    if(grid[r][c] =='B') {ans = dist[r][c]; break;}

    for(int d = 0 ;d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];

        // checking bounds 
        if(nr < 0 || nc < 0 ||nr >= R || nc >=C) continue;
        if(grid[nr][nc] == '#') continue;
        int w = isalpha(grid[nr][nc]) ? 0 : 1;

        int nd = dist[r][c] + w;

        // we relax only if we get shorter distance
        if( nd < dist[nr][nc]) {//  dist[][] itself gates re-processing 
            dist[nr][nc] = nd;
            if(w==0) dq.push_front({nr,nc});
            else dq.push_back({nr,nc});
        }


    }
}
    cout << ans << endl;


}
