#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

pair<int,int> bfs(
    int sr,
    int sc,
    vector<vector<char>> &grid,
    vector<vector<int>> &dist,
    vector<vector<pair<int,int>>> &par)
{
    int n = grid.size();
    int m = grid[0].size();

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    queue<pair<int,int>> q;

    q.push({sr, sc});
    dist[sr][sc] = 0;

    while (!q.empty())
    {
        auto [r, c] = q.front();
        q.pop();

        if (grid[r][c] == 'B')
            return {r, c};

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;

            if (grid[nr][nc] == '#')
                continue;

            if (dist[nr][nc] != INF)
                continue;

            dist[nr][nc] = dist[r][c] + 1;
            par[nr][nc] = {r, c};

            q.push({nr, nc});
        }
    }

    return {-1, -1};
}

void solve()
{
    int n, m;

    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));

    int sr = -1, sc = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];

            if (grid[i][j] == 'A')
            {
                sr = i;
                sc = j;
            }
        }
    }

   
    vector<vector<int>> dist(n, vector<int>(m, INF));

    vector<vector<pair<int,int>>> par(
        n,
        vector<pair<int,int>>(m, {-1,-1})
    );

    auto [er, ec] = bfs(sr, sc, grid, dist, par);

    if (er == -1)
    {
        cout << "NO\n";
        return;
    }

    string path;

    int r = er;
    int c = ec;

    while (!(r == sr && c == sc))
    {
        auto [pr, pc] = par[r][c];

        if (pr == r - 1)
            path.push_back('D');
        else if (pr == r + 1)
            path.push_back('U');
        else if (pc == c - 1)
            path.push_back('R');
        else
            path.push_back('L');

        r = pr;
        c = pc;
    }

    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << "\n";
    cout << path << "\n";
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
PATTERN:
Shortest Path in an Unweighted Graph

Algorithm:
BFS + Parent Tracking

Core Idea:
BFS visits nodes level by level.
The first time we reach the destination, we have found the shortest path.

Parent Concept:
Whenever BFS discovers a new cell,
store the cell from which it was reached.

parent[child] = current

Path Reconstruction:
Start from destination (B).
Keep moving to parent until source (A).
The path is obtained in reverse order,
so reverse it before printing.

Remember:
- Mark visited (or set distance) when pushing into the queue.
- Store parent immediately when discovering a node.
- BFS guarantees shortest path only in unweighted graphs.
- Parent array forms a BFS tree.

Complexity:
Time  : O(N × M)
Space : O(N × M)

Common Mistakes:
- Using DFS instead of BFS.
- Forgetting to store parents.
- Passing parent by value.
- Using bool for distance.
- Forgetting to reverse the reconstructed path.
*/