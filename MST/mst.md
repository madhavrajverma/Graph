# Minimum Spanning Tree (MST) — Complete Notes

## Table of Contents

1. [Overview and Motivation](#1-overview-and-motivation)
2. [Kruskal's Algorithm](#2-kruskals-algorithm)
3. [Prim's Algorithm](#3-prims-algorithm)
4. [Kruskal's vs Prim's — Comparison](#4-kruskals-vs-prims--comparison)
5. [Variant: Maximum Spanning Tree](#5-variant-maximum-spanning-tree)
6. [Variant: 'Minimum' Spanning Subgraph](#6-variant-minimum-spanning-subgraph)
7. [Variant: Minimum 'Spanning Forest'](#7-variant-minimum-spanning-forest)
8. [Variant: MiniMax and MaxiMin Path](#8-variant-minimax-and-maxiMin-path) — includes MST-based method, Dijkstra-variant ("widest path") method, and a Multi-Source BFS + MaxiMin applied example (grid problem)
9. [Variant: Second Best Spanning Tree](#9-variant-second-best-spanning-tree)
10. [MST in Programming Contests](#10-mst-in-programming-contests)
11. [Summary](#11-summary)

---

## 1. Overview and Motivation

### The Problem

> Given a **connected, undirected, weighted graph** `G = (V, E)`, select a subset of edges `E' ⊆ E` such that the graph `G' = (V, E')` is **still connected**, and the total weight of `E'` is **minimal**.

### Why We Need At Least `V-1` Edges

To keep the graph connected while touching all `V` vertices, the resulting edge subset must form a **tree** that **spans** (covers) every vertex — a **spanning tree**. Any tree with `V` vertices has exactly `V-1` edges.

There can be **many valid spanning trees** of a graph `G` (e.g., DFS spanning tree, BFS spanning tree, SSSP spanning tree). Among all of them, at least one has the **minimum total weight** — that's the **Minimum Spanning Tree (MST)**.

**Note:** the MST *weight* is always unique for a given graph, but there can be **multiple different spanning trees** that all achieve that same minimum weight.

### Practical Motivation

Classic example: building a road network connecting remote villages.
- **Vertices** = villages.
- **Edges** = potential roads between villages.
- **Edge weight** = cost of building that road.
- The **MST** = the cheapest possible road network that still connects every village.

### Solving Algorithms

Two classic **greedy** algorithms solve MST:
- **Kruskal's algorithm**
- **Prim's algorithm**

Both always find a spanning tree with the same (minimum) total weight, though the actual set of edges chosen can differ.

---

## 2. Kruskal's Algorithm

### Core Idea

1. **Sort all `E` edges** by non-decreasing weight.
2. **Greedily** consider each edge (from lightest to heaviest); add it to the MST **only if it does not create a cycle** with edges already chosen.
3. Stop once `V-1` edges have been added (the tree is complete).

**Cycle detection:** done efficiently using a **Union-Find Disjoint Sets (UFDS)** data structure — two endpoints of an edge are in the same "cycle risk" if they're already in the same connected component (same disjoint set).

**Conceptually:** Kruskal's algorithm maintains a **forest** of small trees that gradually merge together into one single MST as edges are added.

### Union-Find Disjoint Sets (UFDS) — Minimal Implementation

```cpp
#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent, rank_;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank_.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);   // path compression
        return parent[x];
    }

    bool isSameSet(int x, int y) {
        return find(x) == find(y);
    }

    void unionSet(int x, int y) {
        int xRoot = find(x), yRoot = find(y);
        if (xRoot == yRoot) return;
        if (rank_[xRoot] < rank_[yRoot]) swap(xRoot, yRoot);
        parent[yRoot] = xRoot;
        if (rank_[xRoot] == rank_[yRoot]) rank_[xRoot]++;
    }
};
```

### Kruskal's Code

```cpp
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int kruskalMST(int V, vector<tuple<int,int,int>>& edges) {
    // edges: each tuple is (weight, u, v)
    sort(edges.begin(), edges.end());   // sort by weight, O(E log E)

    UnionFind uf(V);
    int mstCost = 0, numTaken = 0;

    for (auto& [w, u, v] : edges) {
        if (uf.isSameSet(u, v)) continue;   // would form a cycle, skip
        mstCost += w;                       // take this edge
        uf.unionSet(u, v);
        numTaken++;
        if (numTaken == V - 1) break;       // optimization: MST complete
    }

    return mstCost;
}
```

**Usage — reading input and building the edge list:**

```cpp
#include <cstdio>
#include <vector>
#include <tuple>
using namespace std;

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    vector<tuple<int,int,int>> edges(E);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i] = {w, u, v};    // reorder as (w, u, v) so sort() sorts by weight first
    }

    int mstCost = kruskalMST(V, edges);
    printf("MST cost = %d (Kruskal's)\n", mstCost);
    return 0;
}
```

**Why store as `(w, u, v)` instead of `(u, v, w)`?** `std::tuple` has a built-in lexicographic comparison — sorting tuples compares the first element first. By putting `w` first, `sort()` automatically sorts by weight (with `u`, `v` as tie-breakers), with zero extra code needed.

### Why Early Termination (`if (numTaken == V-1) break;`) Is Correct

Once `V-1` edges have been successfully added without forming a cycle, the tree is **already complete and spans all vertices** — no more edges are needed, and continuing would only waste time scanning through the (already-sorted) remaining edges. This doesn't change correctness because the greedy choice has already locked in the minimum-cost tree structure by this point.

### Complexity

$$O(\text{sorting} + \text{trying to add each edge} \times \text{cost of UFDS ops})$$
$$= O(E \log E + E \times O(\alpha(V))) \approx O(E \log E)$$
$$= O(E \log V^2) = O(2 \cdot E \log V) = O(E \log V)$$

(Union-Find operations with path compression + union by rank run in near-constant amortized time, `O(α(V))`, which is negligible compared to the sort.)

### Worked Example

Graph (5 vertices, from the book's Figure 4.9): edges with weights — `0-1(4)`, `0-2(4)`, `0-3(6)`, `0-4(6)`, `1-2(2)`, `2-3(5)`, `3-4(6)`... *(exact weights reconstructed from the described animation)*.

**Sorted edge list (by weight):** process edges from lightest to heaviest, skip any that connect two vertices already in the same set.

**Result:** MST cost = **18** (compared to a non-optimal spanning tree of cost 20 shown for comparison in the book).

**Key insight — MST is not unique:** the book notes that swapping edge `0-1` for edge `0-2` (if they have equal weight) produces a **different spanning tree with the same total cost of 18**. The MST *weight* is unique; the *edge set* achieving it may not be.

---

## 3. Prim's Algorithm

### Core Idea

Unlike Kruskal's (which builds a *forest* that merges), Prim's algorithm grows a **single connected tree**, starting from one vertex and expanding outward.

1. Pick a starting vertex (commonly vertex `0`), mark it **taken**.
2. Push all edges incident to the taken vertex into a **priority queue**, keyed by weight (min-heap: smallest weight first).
3. Repeatedly pop the minimum-weight edge `(w, u)`:
   - If `u` is already taken, **skip** (this would create a cycle).
   - Otherwise: add weight `w` to the MST cost, mark `u` as taken, and push all of `u`'s edges to not-yet-taken neighbors into the priority queue.
4. Repeat until the priority queue is empty (or `V-1` edges have been taken).

**Conceptually:** Prim's grows **one single tree/component** outward from the starting vertex until it spans the whole graph — unlike Kruskal's forest-merging approach.

### Code

```cpp
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

vector<vector<pair<int,int>>> adj;   // adjacency list: adj[u] = list of (neighbor, weight)
vector<int> taken;
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;  // min-heap of (weight, vertex)

void process(int u) {
    taken[u] = 1;
    for (auto& [v, w] : adj[u]) {
        if (!taken[v])
            pq.push({w, v});
    }
}

int primMST(int V) {
    taken.assign(V, 0);
    process(0);   // start from vertex 0

    int mstCost = 0, numTaken = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (taken[u]) continue;   // already taken, would form a cycle — skip

        mstCost += w;
        process(u);
        numTaken++;
        if (numTaken == V - 1) break;   // optimization
    }

    return mstCost;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    adj.assign(V, vector<pair<int,int>>());
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});   // undirected
    }

    int mstCost = primMST(V);
    printf("MST cost = %d (Prim's)\n", mstCost);
    return 0;
}
```

**Note on the min-heap:** C++'s `std::priority_queue` is a **max-heap by default**. The book's original code uses negative weights (`-w, -u`) to simulate a min-heap using the default max-heap. In this rewrite, we instead just declare the priority queue with `greater<pair<int,int>>` as the comparator, which directly gives a min-heap without needing to negate anything — cleaner and avoids sign-flipping bugs.

### Why the "Already Taken" Check Prevents Cycles

Just like Kruskal's cycle check via UFDS, Prim's `if (taken[u]) continue;` check serves the same purpose: if `u` is already part of the growing tree, adding this edge would create a cycle rather than extending the tree — so it's discarded.

### Lazy Deletion Note

Similar to Modified Dijkstra's, Prim's algorithm here uses a form of **lazy deletion**: multiple stale `(w, v)` pairs for the same vertex `v` can sit in the priority queue simultaneously (pushed at different times, from different "taken" neighbors). The `if (taken[u]) continue;` check filters these out — only the first (and cheapest, thanks to the min-heap ordering) valid pop for each vertex is actually processed.

### Complexity

$$O(\text{process each edge once} \times \text{cost of enqueue/dequeue})$$
$$= O(E \times \log E) = O(E \log V)$$

(Same reasoning as Kruskal's: `log E = O(log V)` since `E = O(V²)` at most.)

---

## 4. Kruskal's vs Prim's — Comparison

| Aspect | Kruskal's | Prim's |
|---|---|---|
| Approach | Sort all edges, greedily add if no cycle | Grow one tree outward from a start vertex |
| Data structure | Union-Find Disjoint Sets | Priority Queue + boolean "taken" array |
| Graph representation | Edge List | Adjacency List |
| Conceptual structure | Forest of trees merging into one | Single tree growing |
| Complexity | `O(E log V)` | `O(E log V)` |
| Best when | Edge list is naturally available, or graph is sparse | Adjacency list is naturally available |

Both algorithms are **greedy** and provably correct (see CP4 Exercise 4.3.4.4* — proving correctness is a good exercise, generally done via the **cut property** of MSTs: for any cut of the graph, the minimum-weight edge crossing that cut is safe to include in some MST).

Both produce the **same MST cost**, though the actual set of edges chosen can differ if there are ties in weight.

---

## 5. Variant: Maximum Spanning Tree

### Problem

Instead of minimizing total weight, we want to **maximize** it — find the spanning tree with the **largest** possible total edge weight.

*Example:* UVa 01234 - RACING (deliberately disguised so it doesn't look like an MST problem at first glance).

### Solution

Trivial modification of either algorithm:

- **Kruskal's:** sort edges by **non-increasing** weight instead of non-decreasing, then proceed identically.
- **Prim's:** use a **max-priority-queue** instead of a min-priority-queue (or equivalently, negate all edge weights before running the normal min-based algorithm, then negate the final answer back).

```cpp
// Kruskal's for Maximum Spanning Tree — only the sort direction changes
sort(edges.begin(), edges.end(), greater<tuple<int,int,int>>());
// ... rest of the algorithm is identical
```

```cpp
// Prim's for Maximum Spanning Tree — use a max-heap instead
priority_queue<pair<int,int>> pq;   // default: max-heap
// ... rest of the algorithm is identical
```

---

## 6. Variant: 'Minimum' Spanning Subgraph

### Problem

Some edges are **already fixed** and **must** be included in the solution (given by the problem statement), even if they aren't part of what would normally be the MST. The task is to add the remaining necessary edges as cheaply as possible to make the graph connected.

*Example:* UVa 10147 - Highways.

**Why "Minimum" is in quotes:** the resulting subgraph may not even be a tree in general, and even if it happens to be a tree, it's not necessarily the *true* MST (since we're forced to include specific edges regardless of cost).

**Concrete example from the book:** if edge `(0,1)` with weight `25` is fixed/mandatory, but the true MST (cost `10+13+17=40`) doesn't use that edge at all, then the actual required solution must be `25 + 10 + 13 = 48` — forced to include the fixed edge even though it's expensive.

### Solution

- **Kruskal's:** first account for all fixed/mandatory edges and their costs (union their endpoints in the UFDS upfront, add their weights to the running total). Then continue running normal Kruskal's on the remaining "free" edges until the graph is fully connected (spanning subgraph achieved).

```cpp
int kruskalWithFixedEdges(int V, vector<tuple<int,int,int>>& fixedEdges,
                            vector<tuple<int,int,int>>& freeEdges) {
    UnionFind uf(V);
    int totalCost = 0, numTaken = 0;

    // Step 1: force-include all fixed edges
    for (auto& [w, u, v] : fixedEdges) {
        if (!uf.isSameSet(u, v)) {
            uf.unionSet(u, v);
            numTaken++;
        }
        totalCost += w;   // fixed edges are always counted, cycle or not
    }

    // Step 2: run Kruskal's normally on the remaining free edges
    sort(freeEdges.begin(), freeEdges.end());
    for (auto& [w, u, v] : freeEdges) {
        if (uf.isSameSet(u, v)) continue;
        totalCost += w;
        uf.unionSet(u, v);
        numTaken++;
        if (numTaken == V - 1) break;
    }

    return totalCost;
}
```

- **Prim's:** give the fixed edges **higher priority** in the priority queue so they're always chosen first whenever they connect to the growing tree, guaranteeing they end up included.

---

## 7. Variant: Minimum 'Spanning Forest'

### Problem

Instead of one single connected spanning tree, we want to form a **forest of `K` connected components** (i.e., `K` separate subtrees) at minimum total cost, where `K` is given.

*Example:* Kattis - arcticnetwork (also UVa 10369 - Arctic Networks).

**Concrete example from the book:** if the normal MST costs `10+13+17=40` (fully connected, 1 component), but a forest with **2** components is acceptable, the solution drops to `10+13=23` — by simply **not** taking the single most expensive edge (`17`) that would have merged the last two components into one.

### Solution

- **Kruskal's:** run exactly as normal, but **stop early** — as soon as the number of remaining disjoint components equals the target `K` (instead of running until only 1 component remains).

```cpp
int kruskalSpanningForest(int V, vector<tuple<int,int,int>>& edges, int K) {
    sort(edges.begin(), edges.end());
    UnionFind uf(V);
    int totalCost = 0;
    int numComponents = V;   // initially, every vertex is its own component

    for (auto& [w, u, v] : edges) {
        if (numComponents == K) break;         // target forest size reached
        if (uf.isSameSet(u, v)) continue;
        totalCost += w;
        uf.unionSet(u, v);
        numComponents--;
    }

    return totalCost;
}
```

- **Prim's:** run normally to completion (get the full MST), then **remove the `K-1` most expensive edges** from the resulting MST — this naturally splits it into `K` components at minimum extra cost, since removing the largest edges loses the least "value."

---

## 8. Variant: MiniMax and MaxiMin Path

### Problem

**MiniMax path:** between two vertices `i` and `j`, find the path (among all possible paths) that **minimizes the maximum edge weight** along that path. I.e., the cost of a path is defined as its single worst (heaviest) edge, and we want the path with the smallest such worst-case edge.

**MaxiMin path:** the reverse — maximize the minimum edge weight along the path.

*Example:* UVa 10048 - Audiophobia.

### Solution — Model as an MST Problem

**Key insight:** MiniMax prefers paths with individually low edge weights, even if the path is longer (more hops). This is *exactly* the bias that Kruskal's/Prim's MST construction has — greedily favoring cheap edges. So:

1. Build the **MST** of the given weighted graph (using Kruskal's or Prim's).
2. Since the MST is connected, there's a **unique path** between any two vertices `i` and `j` within the MST (a tree has exactly one path between any pair of nodes).
3. The **MiniMax path cost** = the **maximum edge weight** found along that unique path within the MST.

**For MaxiMin:** build a **Maximum** Spanning Tree instead, then take the **minimum** edge weight along the unique path in that tree.

### Code

```cpp
#include <vector>
using namespace std;

// After building MST as an adjacency list mstAdj[u] = list of (neighbor, weight):
int miniMaxDFS(vector<vector<pair<int,int>>>& mstAdj, int u, int target,
               int maxSoFar, vector<bool>& visited) {
    if (u == target) return maxSoFar;
    visited[u] = true;
    for (auto& [v, w] : mstAdj[u]) {
        if (visited[v]) continue;
        int result = miniMaxDFS(mstAdj, v, target, max(maxSoFar, w), visited);
        if (result != -1) return result;
    }
    return -1;   // not found on this branch
}

int findMiniMaxPath(vector<vector<pair<int,int>>>& mstAdj, int V, int source, int target) {
    vector<bool> visited(V, false);
    return miniMaxDFS(mstAdj, source, target, 0, visited);
}
```

### Worked Example

Graph: 7 vertices, 9 edges (UVa 10048 - Audiophobia sample). After running Kruskal's/Prim's, **6 edges** form the MST.

**Query:** MiniMax path between vertex 0 and vertex 6.
- Traverse the unique path in the MST: `0 → 2 → 5 → 3 → 6`.
- The maximum edge weight along this path is **80** (from edge `5-3`).
- **Answer: 80.**

### Complexity

$$O(\text{build MST} + \text{one traversal on the resulting tree})$$

Since a tree has `E = V-1` edges, any traversal (DFS/BFS) on it costs just `O(V)`. So overall:

$$O(E \log V + V) = O(E \log V)$$

### Alternative Solution — Modified Dijkstra's ("Widest/Narrowest Path")

The MST-based method above is **not the only** way to solve MiniMax/MaxiMin — it's the best choice when you need to answer **many queries** on the same graph (build the tree once, `O(E log V)`, then each query is a cheap `O(V)` tree traversal). But for a **single** source-to-target query, or on an **implicit graph** (like a grid, where materializing an explicit MST first is wasted work), a more direct method is to run a **modified Dijkstra's algorithm** that propagates the running bottleneck value instead of a summed distance.

**Core idea — mirror every part of standard Dijkstra's:**

| Standard Dijkstra's (shortest path, sum) | MaxiMin variant (widest path, bottleneck) |
|---|---|
| `dist[v] = dist[u] + w` (accumulate sum) | `best[v] = min(best[u], w)` (propagate the running minimum) |
| Want the **smallest** total distance | Want the **largest** minimum-so-far |
| **Min-heap**, pop smallest first | **Max-heap**, pop largest first |
| Relax if new value is **smaller**: `dist[u]+w < dist[v]` | Relax if new value is **larger**: `candidate > best[v]` |
| Stale-entry check: `if (d > dist[u]) continue;` | Stale-entry check: `if (val < best[u]) continue;` (mirrored) |

(For **MiniMax** — minimize the maximum edge — flip the roles again: propagate the running **maximum**, use a **min-heap**, and relax when the new value is **smaller**.)

```cpp
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// MaxiMin: find the path from source to target that maximizes the minimum edge weight
int maxiMinDijkstra(int V, vector<vector<pair<int,int>>>& adj, int source, int target) {
    vector<int> best(V, -1);                  // best bottleneck value reaching each vertex

    // max-heap: (bottleneck value so far, vertex) — largest bottleneck popped first
    priority_queue<pair<int,int>> pq;

    best[source] = INT_MAX;                    // no constraint yet at the source
    pq.push({best[source], source});

    while (!pq.empty()) {
        auto [val, u] = pq.top();
        pq.pop();

        if (val < best[u]) continue;            // stale entry, skip (mirrored lazy deletion)
        if (u == target) return val;             // early termination (same SSSDSP trick)

        for (auto& [v, w] : adj[u]) {
            int candidate = min(val, w);          // bottleneck propagation
            if (candidate > best[v]) {             // relax if BETTER (larger)
                best[v] = candidate;
                pq.push({candidate, v});
            }
        }
    }

    return best[target];
}
```

**Why this works:** exactly the same greedy correctness argument as standard Dijkstra's — at every step we finalize the vertex with the best (here: largest) confirmed bottleneck value, and since edge weights only ever *constrain* (never improve) the running minimum, once a vertex is popped with its true best value, it can never be improved later (mirroring the non-negative-weight assumption that makes standard Dijkstra's greedy strategy valid).

### MST-based vs Dijkstra-variant — When to Use Which

| | MST-based | Dijkstra-variant |
|---|---|---|
| Upfront cost | `O(E log V)` — build Max/Min ST once | None — direct search |
| Per-query cost | `O(V)` tree traversal | `O(E log V)` per query |
| Best when... | **Many** MiniMax/MaxiMin queries on the same graph | **Single** query, or implicit/grid graphs |

Both are valid, correct algorithms for the *same* MiniMax/MaxiMin problem — this mirrors how BFS and Dijkstra's are both valid shortest-path algorithms, just suited to different graph/query shapes.

### Applied Example — Multi-Source BFS + MaxiMin on a Grid

**LeetCode: Find the Safest Path in a Grid.** Given an `n×n` grid with some cells marked as thieves, find a path from `(0,0)` to `(n-1,n-1)` that maximizes the **minimum "safeness"** (Manhattan distance to the nearest thief) along the path.

This is a two-stage graph-modeling problem that combines two techniques from these notes:

**Stage 1 — Multi-Source BFS** (see the SSSP notes, MSSP section): compute the safeness value of *every* cell in one pass by pushing **all thief cells** into a BFS queue at once with distance `0`.

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> computeSafeness(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> safeness(n, vector<int>(n, -1));
    queue<pair<int,int>> q;

    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (grid[r][c] == 1) {              // thief cell = source
                safeness[r][c] = 0;
                q.push({r, c});
            }

    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
            if (safeness[nr][nc] != -1) continue;
            safeness[nr][nc] = safeness[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return safeness;
}
```

**Stage 2 — MaxiMin path on the grid** (the Dijkstra-variant above, adapted so grid **cells** carry the bottleneck value instead of edges):

```cpp
int maximumSafenessFactor(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> safeness = computeSafeness(grid);
    vector<vector<int>> pathMin(n, vector<int>(n, -1));

    priority_queue<tuple<int,int,int>> pq;   // max-heap: (bottleneck, row, col)
    pathMin[0][0] = safeness[0][0];
    pq.push({pathMin[0][0], 0, 0});

    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};
    while (!pq.empty()) {
        auto [val, r, c] = pq.top(); pq.pop();
        if (val < pathMin[r][c]) continue;              // stale entry
        if (r == n-1 && c == n-1) return val;            // early termination

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
            int candidate = min(val, safeness[nr][nc]);   // bottleneck propagation
            if (candidate > pathMin[nr][nc]) {
                pathMin[nr][nc] = candidate;
                pq.push({candidate, nr, nc});
            }
        }
    }
    return pathMin[n-1][n-1];
}
```

**Why this is the Dijkstra-variant, not the MST-based method:** this problem only asks for **one** query (`(0,0) → (n-1,n-1)`), on an **implicit grid graph**. Building a full Maximum Spanning Tree first would mean materializing all `O(n²)` cells and edges into an explicit MST structure — extra work with no payoff for a single query. The direct Dijkstra-variant search reaches the same correct answer in one pass, no separate tree-construction phase needed.

| Piece | Source technique |
|---|---|
| Multi-source BFS for safeness grid | SSSP notes — MSSP (Section 2c) |
| Priority-queue relaxation loop structure | SSSP notes — Modified Dijkstra's |
| Lazy deletion / stale-entry skip | SSSP notes — Modified Dijkstra's |
| Early termination on reaching target | SSSP notes — SSSDSP (Section 2a) |
| Max-heap instead of min-heap | This section — Maximum ST / MaxiMin |
| "Optimize the bottleneck, not the sum" idea | This section — MiniMax/MaxiMin path |

---

## 9. Variant: Second Best Spanning Tree

### Problem

Sometimes the MST alone isn't enough — we also want the **second-best** spanning tree (the next cheapest one), useful in case the true MST becomes unusable for some reason.

*Example:* UVa 10600 - ACM Contest and Blackout.

### Key Structural Insight

The second-best spanning tree differs from the MST by **exactly two edges**:
- **One edge is removed** from the MST.
- **One "chord" edge is added** (a chord edge = any edge in `G` that is *not* part of the MST).

*Example from the book:* MST weight = `9+19+51+31=110`. Second-best ST swaps out edge `3-4` and swaps in edge `1-4`, giving weight `9+19+51+42=121`.

### Solution — Modified Kruskal's

1. Sort all edges once — `O(E log E) = O(E log V)`.
2. Build the original MST using Kruskal's — `O(E)`.
3. For **each edge in the MST** (there are at most `V-1` of them):
   - Temporarily **flag/exclude** that edge (forbid Kruskal's from using it).
   - Re-run Kruskal's from scratch on the remaining edges (still sorted — **no need to re-sort**) — `O(E)`.
   - Record the resulting spanning tree's total weight.
4. The **best** (cheapest) spanning tree found across all these `V-1` reruns is the **second-best spanning tree**.

### Code

```cpp
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>
using namespace std;

int tryKruskalExcluding(int V, vector<tuple<int,int,int>>& sortedEdges, int excludeIdx) {
    UnionFind uf(V);
    int totalCost = 0, numTaken = 0;

    for (int i = 0; i < (int)sortedEdges.size(); i++) {
        if (i == excludeIdx) continue;         // skip the flagged edge
        auto& [w, u, v] = sortedEdges[i];
        if (uf.isSameSet(u, v)) continue;
        totalCost += w;
        uf.unionSet(u, v);
        numTaken++;
        if (numTaken == V - 1) break;
    }

    if (numTaken != V - 1) return INT_MAX;   // couldn't reconnect, not a valid ST
    return totalCost;
}

int secondBestST(int V, vector<tuple<int,int,int>>& edges) {
    sort(edges.begin(), edges.end());   // sort once, O(E log E)

    // find original MST edges' indices
    UnionFind uf(V);
    vector<int> mstEdgeIndices;
    int mstCost = 0, numTaken = 0;

    for (int i = 0; i < (int)edges.size(); i++) {
        auto& [w, u, v] = edges[i];
        if (uf.isSameSet(u, v)) continue;
        mstCost += w;
        uf.unionSet(u, v);
        mstEdgeIndices.push_back(i);
        numTaken++;
        if (numTaken == V - 1) break;
    }

    // try excluding each MST edge, one at a time
    int secondBest = INT_MAX;
    for (int idx : mstEdgeIndices) {
        int result = tryKruskalExcluding(V, edges, idx);
        if (result < secondBest) secondBest = result;
    }

    return secondBest;
}
```

### Complexity

$$O(\text{sort edges once} + \text{find original MST} + \text{find second best ST})$$
$$= O(E \log V + E + V \cdot E) = O(V \cdot E)$$

(The `V · E` term dominates: up to `V-1` reruns, each costing `O(E)`.)

**Note:** This `O(V·E)` solution is **not optimal**. The book poses better approaches as starred exercises — using **Lowest Common Ancestor (LCA)** techniques or more clever Union-Find tricks to avoid the full `V-1` re-runs, achieving better complexity. *(Left as an advanced exercise — see Exercise 4.3.4.1* and 4.3.4.2* in the original text.)*

---

## 10. MST in Programming Contests

### Choosing Between Kruskal's and Prim's

Both are viable in almost all contest settings:
- **Kruskal's** — often preferred for being conceptually simple and pairing naturally with the Union-Find Disjoint Sets structure.
- **Prim's** — also simple, and only needs built-in structures (priority queue + boolean array), no custom UFDS class needed.

There are other, more advanced MST algorithms (e.g., Borůvka's), but they're generally **not needed** for standard competitive programming.

### Common Contest Behavior

Most MST problems only ask for the **MST cost/weight**, not the actual edge set — because there can be multiple different MSTs with the same minimum weight, and building an automated checker for "is this a valid MST" is often more trouble than it's worth for problem setters.

### Variant Frequency

Per the authors' experience, the "exotic" variants discussed above (Minimum Spanning Subgraph, Minimum Spanning Forest, Second Best ST, MiniMax/MaxiMin) are **relatively rare** compared to the basic MST problem. The **Maximum Spanning Tree** variant is somewhat more common and trivial to implement (just flip the sort order or heap direction).

### The Real Challenge: Graph Modeling

The modern trend in contest problems is to **disguise** MST problems so they don't obviously look like graph problems at all (e.g., UVa 01013, 01216, 01234, 01235, 01265, 10457, Kattis - lostmap). The real skill tested is **recognizing** that a given problem can be modeled as an MST problem in the first place — once that's spotted, the problem often becomes straightforward.

### Harder Variants (Beyond Scope of Basic MST)

- **Steiner Tree** problem (see Book 2).
- **Arborescence problem** (MST for directed graphs).
- **Degree-constrained MST**.
- **k-MST** (minimum spanning tree using only `k` vertices, not all `V`).

---

## 11. Summary

### Core Algorithms

| Algorithm | Data Structure | Complexity | Graph Rep. |
|---|---|---|---|
| Kruskal's | Union-Find Disjoint Sets | `O(E log V)` | Edge List |
| Prim's | Priority Queue + boolean array | `O(E log V)` | Adjacency List |

### Variant Cheat-Sheet

| Variant | Kruskal's modification | Prim's modification |
|---|---|---|
| **Maximum ST** | Sort by non-increasing weight | Use max-heap |
| **'Minimum' Spanning Subgraph** | Pre-union fixed edges first, then run normally on free edges | Give fixed edges top priority |
| **Minimum Spanning Forest (K components)** | Stop early when `numComponents == K` | Build full MST, then remove `K-1` heaviest edges |
| **MiniMax / MaxiMin path** | Build (Min/Max) MST, then find unique path in tree, take max/min edge on that path | Same |
| **Second Best ST** | For each MST edge, exclude it and rerun Kruskal's; take best result | Possible but generally same complexity ballpark |

### Key Takeaways

1. **MST weight is unique; the specific edge set may not be.**
2. Both Kruskal's and Prim's are **greedy** and provably correct via the **cut property**.
3. Most contest MST problems only need the cost, not the tree itself.
4. The hardest part of many MST problems isn't the algorithm — it's **recognizing** the problem as an MST problem in the first place (graph modeling).
5. When variants come up, they almost always reduce to a **small, principled tweak** on the base Kruskal's/Prim's algorithm rather than requiring an entirely new algorithm.