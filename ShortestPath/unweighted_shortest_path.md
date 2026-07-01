# SSSP with BFS — Unweighted Graphs & 0/1-Weighted Graphs

*Based on Competitive Programming 4 (CP4) by Steven Halim, Section 4.4.2*

---

## Part 1: BFS on Unweighted Graphs

### Core Idea

BFS visits vertices **layer by layer** from a source vertex `s`. In an unweighted graph, every edge costs exactly 1 unit, so:

> **The layer number of a vertex `u` = the shortest path distance from `s` to `u`.**

This works because BFS's FIFO queue guarantees vertices are discovered in non-decreasing order of distance — the first time a vertex is reached is always via the shortest path.

**Complexity:** `O(V + E)`

**Constant-weight trick:** If *all* edges share the same weight `C` (not necessarily 1), run BFS as usual (treating each edge as weight 1), then multiply every computed distance by `C`.

```cpp
vector<int> dist(V, INF);
queue<int> q;
dist[s] = 0;
q.push(s);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}
```

---

### 1a. Single-Source Single-Destination Shortest Paths (SSSDSP)

**Problem:** Only need the distance from `s` to one specific vertex `t`.

**Trick:** Check for `t` right when popping from the queue, and break early.

```cpp
while (!q.empty()) {
    int u = q.front(); q.pop();
    if (u == t) break;              // stop — dist[t] is already final
    for (int v : adj[u]) {
        if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}
```

**Why correct:** BFS finalizes a vertex's distance the moment it is *pushed* into the queue. By the time `t` is *popped*, its distance is already guaranteed correct, and everything closer to `s` has already been processed.

**Complexity:** Still `O(V + E)` worst case, but often terminates much sooner in practice. This trick also works with **Dijkstra** on non-negative weighted graphs.

---

### 1b. Single-Destination Shortest Paths (SDSP)

**Problem:** Many possible source vertices, one fixed destination `t`. Find shortest distance from *each* source to `t`.

**Naive approach:** Run BFS from every source separately → `O(K × (V + E))`.

**Trick — think backwards:** Transpose the graph (reverse all edge directions), then run a single BFS from `t` in the transposed graph.

```
dist(s, t) in original graph  ==  dist(t, s) in transposed graph
```

One BFS run gives you the answer for *every* possible source simultaneously.

**Complexity:** `O(V + E)` — a single pass. Works for weighted graphs too (transpose + Dijkstra/Bellman-Ford).

---

### 1c. Multi-Source Shortest Paths (MSSP)

**Problem:** Multiple source vertices `s1, s2, ..., sK`. Find, for every vertex, the shortest distance to the *nearest* source.

**Naive approach:** Run BFS `K` times → `O(K × (V + E))`.

**Trick — enqueue all sources upfront:**

```cpp
vector<int> dist(V, INF);
queue<int> q;
for (int s : sources) {
    dist[s] = 0;
    q.push(s);
}
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}
```

**Intuition:** Imagine a **virtual super-source** connected to all real sources via 0-weight edges. Running BFS from this super-source is equivalent to running BFS from all sources simultaneously.

**Complexity:** `O(V + E)` — just one BFS call. Works for weighted graphs too (push all sources into Dijkstra's priority queue with distance 0).

---

### 1d. Shortest Path Reconstruction

**Problem:** Recover the actual sequence of vertices along the shortest path, not just the distance value.

**Trick — parent pointers:** Whenever a vertex `v` is discovered through vertex `u`, record `parent[v] = u`.

```cpp
vector<int> dist(V, INF), parent(V, -1);
queue<int> q;
dist[s] = 0;
q.push(s);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == INF) {
            dist[v] = dist[u] + 1;
            parent[v] = u;
            q.push(v);
        }
    }
}
```

**Reconstruct the path to `t`:**

```cpp
vector<int> path;
for (int v = t; v != -1; v = parent[v])
    path.push_back(v);
reverse(path.begin(), path.end());   // s -> ... -> t
```

**Example:** Shortest path from 5 to 7 is `5 → 1 → 2 → 3 → 7`.
Parent chain: `parent[7]=3, parent[3]=2, parent[2]=1, parent[1]=5`.
Walking backward from 7 gives `7,3,2,1,5`; reversing gives `5,1,2,3,7`. ✓

Works identically for weighted graphs (Dijkstra, Bellman-Ford) — only the relaxation condition changes.

---

## Part 2: SSSP on 0/1-Weighted Graphs — BFS + Deque

### The Problem

A rarer SSSP variant: the graph has **only two distinct edge weights, 0 and 1**.

**Classic example — grid problem:**
- `.` cells cost **1** to enter (walkable corridor)
- `A`–`Z` letter cells cost **0** to enter (free movement)
- `#` cells are walls (impassable)
- Multiple sources (`A` cells), multiple destinations (`B` cells)
- Movement: N/E/S/W only

```
....................CCCC.
AAAAA...............CCCC.
AAAAA.AAA...........CCCC.
AAAAAAAAA....###....CCCC.
AAAAAAAAA................
AAAAAAAAA................
.......DD..............BB
```
Answer: **13** — walk 11 steps east through `.` cells to reach the `C` block, move freely (0 cost) through/around the `C` block, then 2 more steps south to `B`.

This combines:
- **Multi-source BFS** (all `A` cells are sources)
- **Two edge weights** (0 or 1) → naive instinct says "use Dijkstra"

### The Insight: Deque Instead of Priority Queue

Because there are only **two** possible weights, a full `O((V+E) log V)` Dijkstra is overkill. A **deque** achieves the same correctness in `O(V + E)`.

**Rule:**
- Relax via a **weight-0 edge** → push the neighbor to the **front** of the deque (same distance as current vertex).
- Relax via a **weight-1 edge** → push the neighbor to the **back** of the deque (one more than current vertex).

This keeps the deque **sorted by distance** at all times (front = smallest, back = largest), exactly the property Dijkstra's priority queue guarantees — but achieved here in O(1) per push instead of O(log V).

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int R, C;
vector<string> grid;
vector<vector<int>> dist;
vector<vector<bool>> visited;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int zeroOneBFS() {
    deque<pair<int,int>> dq;
    dist.assign(R, vector<int>(C, INT_MAX));
    visited.assign(R, vector<bool>(C, false));

    // MULTI-SOURCE: push ALL 'A' cells with distance 0
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            if (grid[r][c] == 'A') {
                dist[r][c] = 0;
                dq.push_back({r, c});
            }

    while (!dq.empty()) {
        auto [r, c] = dq.front();
        dq.pop_front();

        if (visited[r][c]) continue;   // skip stale duplicate entries
        visited[r][c] = true;

        // EARLY TERMINATION: stop as soon as we pop a 'B' cell
        if (grid[r][c] == 'B')
            return dist[r][c];

        for (int dir = 0; dir < 4; dir++) {
            int nr = r + dr[dir], nc = c + dc[dir];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (grid[nr][nc] == '#') continue;          // wall
            if (visited[nr][nc]) continue;

            // weight of moving INTO (nr, nc):
            int w = isalpha(grid[nr][nc]) ? 0 : 1;

            if (dist[r][c] + w < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + w;
                if (w == 0)
                    dq.push_front({nr, nc});   // free move -> front
                else
                    dq.push_back({nr, nc});    // costly move -> back
            }
        }
    }
    return -1; // unreachable
}
```

**Implementation notes:**
1. `visited[][]` is checked on **pop**, not push — a vertex may be pushed multiple times before its true shortest distance is finalized; stale entries are simply skipped.
2. **Multi-source init** — same trick as MSSP: push all `A` cells upfront with distance 0.
3. **Early termination** — the deque still pops vertices in non-decreasing distance order, so the first `B` popped has the guaranteed shortest distance.
4. Edge weight = cost of **entering** the target cell (0 for letters, 1 for `.`).

### Why It's Correct

**Invariant:** At any point during execution, the deque is sorted by distance — every element has distance either `d` or `d+1` for some `d`, with all `d`s appearing before all `d+1`s.

- Initially, all sources have distance 0 → trivially sorted.
- Popping the front (smallest distance `d`) and relaxing:
  - A weight-0 neighbor gets distance `d`, pushed to front → still consistent.
  - A weight-1 neighbor gets distance `d+1`, pushed to back → cannot exceed anything not yet in the deque, so order is preserved.

Because the deque stays sorted, popping the front always yields the true minimum-distance unvisited vertex — the same guarantee Dijkstra's priority queue provides, but at O(1) cost per operation.

### Complexity Comparison

| Approach              | Time Complexity     | When to use                                  |
|-----------------------|----------------------|-----------------------------------------------|
| Plain BFS (queue)      | `O(V + E)`          | All edges equal weight                       |
| **0/1-BFS (deque)**    | **`O(V + E)`**      | Exactly two distinct weights: 0 and 1        |
| Dijkstra (priority queue) | `O((V+E) log V)` | Arbitrary non-negative weights               |
| Bellman-Ford           | `O(V × E)`          | Negative weights allowed (no negative cycle) |

### Where to Apply 0/1-BFS

Recognize this pattern whenever a shortest-path problem has costs that are literally 0/1, or can be **transformed** into 0/1 costs:

- **Grids with "free" special cells** — teleporters, same-type regions, portals (the example above).
- **Minimum obstacles/walls to break** — breaking a wall costs 1, moving through open space costs 0.
- **Minimum number of turns** in a path — moving straight = 0, changing direction = 1.
- **State-space shortest paths** with some "free" state transitions and some "real" costed moves.

---

## Summary

| Technique | Problem Shape | Key Trick | Complexity |
|---|---|---|---|
| Plain BFS | Unweighted SSSP | Layer = distance | `O(V+E)` |
| SSSDSP | One source, one destination | Early-stop on pop | `O(V+E)` |
| SDSP | Many sources, one destination | Reverse graph, BFS once from `t` | `O(V+E)` |
| MSSP | Many sources, all destinations | Enqueue all sources upfront (virtual super-source) | `O(V+E)` |
| Path reconstruction | Need actual path | Parent pointers + backward walk | `O(V+E)` |
| 0/1-BFS | Two edge weights (0 and 1) | Deque: push front for 0, back for 1 | `O(V+E)` |