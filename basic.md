# Graph Traversal — Complete Notes

## Table of Contents

1. [Chapter Overview](#1-chapter-overview)
2. [Depth First Search (DFS)](#2-depth-first-search-dfs)
3. [Breadth First Search (BFS)](#3-breadth-first-search-bfs)
4. [Finding Connected Components (Undirected Graph)](#4-finding-connected-components-undirected-graph)
5. [Flood Fill (Implicit 2D Grid Graph)](#5-flood-fill-implicit-2d-grid-graph)
6. [Bipartite Graph Check](#6-bipartite-graph-check)
7. [Cycle Check (Directed Graph)](#7-cycle-check-directed-graph)
8. [Finding Articulation Points and Bridges](#8-finding-articulation-points-and-bridges)
9. [Finding Strongly Connected Components (SCC)](#9-finding-strongly-connected-components-scc)
10. [Complexity Summary Table](#10-complexity-summary-table)

---

## 1. Chapter Overview

### Motivation

Many real-world problems map onto graph problems. Some have efficient (polynomial-time) solutions; others are NP-hard (no known polynomial solution — see Book 2).

**Prerequisite knowledge assumed:** basic graph terminology (vertices, edges, degree, paths, cycles, DAGs, trees, bipartite graphs, etc.) and graph representations (Adjacency Matrix, Adjacency List, Edge List — see CP4 Section 2.4.1).

**Contest relevance:** ICPC problem sets typically contain at least one graph problem, but the space of possible graph topics is huge — there's no way around studying the full breadth of material to be well-prepared. IOI restricts its syllabus to a subset of this material.

### Two Fundamental Traversal Algorithms

- **Depth First Search (DFS)** — uses an (often implicit) **stack** via recursion.
- **Breadth First Search (BFS)** — uses an explicit **queue**.

Both start from a source vertex and visit `(u, v)` edges to reach unvisited neighbors — they differ only in *order* of visitation, governed by their underlying data structure.

---

## 2. Depth First Search (DFS)

### Core Idea

Starting from a source vertex, DFS goes as **deep as possible** along one branch before backtracking. At every branching point (a vertex with multiple unvisited neighbors), DFS picks one neighbor, fully explores everything reachable through it, and only then backtracks to try the next neighbor.

### Code

```cpp
#include <vector>
using namespace std;

enum { UNVISITED = -1, VISITED = -2 };

vector<int> dfsNum;                  // state tracker per vertex
vector<vector<pair<int,int>>> adj;   // adj[u] = list of (neighbor, weight)

void dfs(int u) {
    dfsNum[u] = VISITED;
    for (auto& [v, w] : adj[u])            // w ignored for plain traversal
        if (dfsNum[v] == UNVISITED)        // avoid revisiting / cycles
            dfs(v);
}
```

**Simplification note:** if you only need basic visited/unvisited tracking (not the richer states used later for cycle detection, articulation points, etc.), you can replace `vector<int> dfsNum` with a simpler `vector<bool> visited`.

### Example Trace

Sample graph (Figure 4.1): edges `0-1`, `1-2`, `1-3`, `3-4`, plus a separate component `5`, and another component `6-7`, `6-8`.

Calling `dfs(0)`: visits `0 → 1 → 2` (backtrack to 1) `→ 3 → 4`.

**Note:** the exact visitation order depends on how neighbors are ordered in the adjacency list. E.g. `0 → 1 → 3 → 4` (backtrack to 3) `→ 2` is an equally valid DFS order on the same graph, depending on neighbor ordering.

**Key limitation:** one call `dfs(u)` only visits vertices **reachable from `u`**. Vertices `{5,6,7,8}` in the example remain unvisited after `dfs(0)` — they belong to different connected components. (See Section 4 for handling multiple components.)

### Complexity — Depends on Graph Representation

| Representation | Cost to enumerate neighbors of one vertex | Total DFS/BFS complexity |
|---|---|---|
| Adjacency Matrix (AM) | `O(V)` | `O(V × V) = O(V²)` |
| Adjacency List (AL) | `O(k)` (k = actual neighbor count) | `O(V + E)` |
| Edge List (EL) | `O(E)` | `O(V × E) = O(VE)` |

**Since Adjacency List is the most efficient representation for traversal**, it's often worth converting an AM- or EL-based input into an AL first before running DFS/BFS.

### DFS vs Recursive Backtracking

The DFS code closely resembles typical backtracking pseudocode:

```cpp
void backtrack(State state) {
    for (auto& neighbor : neighbors(state)) {
        if (isEndState(neighbor)) continue;      // base case
        if (isInvalidState(neighbor)) continue;   // optional pruning
        backtrack(neighbor);
    }
}
```

**Key difference:** backtracking **automatically un-flags** visited states when the recursion backtracks (there's no persistent global "visited" tracker), which allows **re-visiting the same state from a different branch**. DFS, by contrast, uses a persistent global `dfsNum`/`visited` array that permanently marks a vertex as visited — preventing re-visitation from any branch.

**Consequence:**
- Backtracking can explore **up to `V!`** possible paths from the source (since states can be revisited via different paths) — exponential, but thorough (used for combinatorial search / exhaustive enumeration).
- DFS only explores **each vertex once**, giving `O(V + E)` — fast, but only finds *one* traversal path structure, not all possible paths.

---

## 3. Breadth First Search (BFS)

### Core Idea

Starting from a source vertex `s`, BFS visits vertices **layer by layer**: first `s` itself (layer 0), then all direct neighbors of `s` (layer 1), then neighbors-of-neighbors (layer 2), and so on.

### Code

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<int> bfs(int V, vector<vector<pair<int,int>>>& adj, int source) {
    const int INF = 1e9;
    vector<int> dist(V, INF);
    dist[source] = 0;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& [v, w] : adj[u]) {       // w ignored for plain traversal
            if (dist[v] != INF) continue;    // already visited, skip
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}
```

**Key detail:** `vector<int> dist` serves **double duty** — it tracks whether a vertex has been visited (`dist[u] != INF`) **and** simultaneously records the layer number (distance from source). This distance-tracking property is later reused directly to solve SSSP on unweighted graphs (Section 4.4.2).

### Example Trace

Running BFS from vertex `5` on a connected grid-like graph (Figure 4.2):
- Layer 0: `{5}` (source)
- Layer 1: `{1, 6, 10}`
- Layer 2: `{0, 2, 11, 9}`
- Layer 3: `{4, 3, 12, 8}`
- Layer 4: `{7}`

This resulting layered structure is also the **BFS spanning tree** — and, since the graph is unweighted, it's simultaneously the **Shortest Paths spanning tree** rooted at `s=5`.

### Complexity

Same as DFS, depending on representation: `O(V+E)` on Adjacency List, `O(V²)` on Adjacency Matrix, `O(VE)` on Edge List.

---

## 4. Finding Connected Components (Undirected Graph)

### Core Idea

A single call `dfs(u)` (or `bfs(u)`) only visits vertices reachable from `u` — exactly the vertices in `u`'s **Connected Component (CC)**. So: repeatedly restart DFS/BFS from any remaining unvisited vertex to discover the next CC, until all vertices are visited.

### Code

```cpp
#include <vector>
#include <cstdio>
using namespace std;

int main() {
    int V;
    // ... read V, build adj[] ...

    vector<int> dfsNum(V, -1);   // UNVISITED = -1
    int numCC = 0;

    for (int u = 0; u < V; u++) {
        if (dfsNum[u] == -1) {          // unvisited => new component found
            printf("CC %d:", ++numCC);
            // dfs(u) here, printing each visited vertex
            printf("\n");
        }
    }
    printf("There are %d connected components\n", numCC);
    return 0;
}
```

**Sample output** for the graph in Figure 4.1:
```
CC 1: 0 1 2 3 4
CC 2: 5
CC 3: 6 7 8
There are 3 connected components
```

### Complexity

Despite potentially calling `dfs(u)` up to `V` times, the **overall** complexity remains `O(V + E)`, because each vertex and each edge is only ever visited **once** in total across all the calls combined — the work doesn't multiply, it's just distributed across multiple starting points.

**Alternative approaches:** this same problem can also be solved using **Union-Find Disjoint Sets (UFDS)** (union endpoints of every edge, then count distinct root sets), or using **BFS** instead of DFS — same underlying principle either way.

---

## 5. Flood Fill (Implicit 2D Grid Graph)

### Core Idea

A DFS/BFS variant used to **label** ("color") and **count the size of** each connected region, most commonly applied to **implicit graphs** — typically 2D grids, where cells are vertices and adjacency is defined geometrically (e.g., 8 directions: N/S/E/W + 4 diagonals).

### Code

```cpp
#include <vector>
#include <string>
using namespace std;

int R, C;
vector<string> grid;

int dr[] = { 1, 1, 0,-1,-1,-1, 0, 1};   // S/SE/E/NE/N/NW/W/SW
int dc[] = { 0, 1, 1, 1, 0,-1,-1,-1};

int floodfill(int r, int c, char c1, char c2) {   // returns size of the CC
    if (r < 0 || r >= R) return 0;                // outside grid bounds (row)
    if (c < 0 || c >= C) return 0;                // outside grid bounds (col)
    if (grid[r][c] != c1) return 0;                // wrong color, not part of this region

    int count = 1;                                  // (r,c) belongs to the region
    grid[r][c] = c2;                                // recolor to avoid revisiting (cycle prevention)

    for (int d = 0; d < 8; d++)
        count += floodfill(r + dr[d], c + dc[d], c1, c2);

    return count;
}
```

**Why recoloring works as "visited" marking:** overwriting `grid[r][c]` from `c1` to `c2` means subsequent recursive calls checking `grid[r][c] != c1` will correctly skip this already-processed cell — no separate `visited` array needed.

### Sample Application — UVa 00469 (Wetlands of Florida)

**Problem:** cells marked `'W'` (wet) that are connected (8-directionally) form a "wet area." Given a query cell, report the size of its wet area.

```cpp
#include <cstdio>

int main() {
    // ... read grid, R, C ...
    int row, col;
    scanf("%d %d", &row, &col);
    printf("%d\n", floodfill(row, col, 'W', '.'));   // count + mark visited as '.'
    return 0;
}
```

**Example:**
```
Before floodfill(2, 1, 'W', '.'):        After:
LLLLLLLLL                                LLLLLLLLL
LLWWLLWLL                                LL..LLWLL
LWWLLLLLL   <- query cell (2,1)          L..LLLLLL
LWWWLWWLL                                L...L..LL
LLLWWWLLL                                LLL...LLL
LLLLLLLLL                                LLLLLLLLL
LLLWWLLWL                                LLLWWLLWL
LLWLWLLLL                                LLWLWLLLL
LLLLLLLLL                                LLLLLLLLL
```
Result: **12** (the size of the connected `'W'` region containing `(2,1)`), and all cells in that region get replaced with `'.'`.

**Note:** flood fill problems used to be very common in contests, though the authors note this trend has been declining. A notable high-profile example: **UVa 01103 - Ancient Messages** (ICPC World Finals 2011).

---

## 6. Bipartite Graph Check

### Definition Recap

A **Bipartite Graph** is one where `V` can be split into two disjoint sets `V1, V2` such that **every edge** connects a vertex in `V1` to a vertex in `V2` (never within the same set). Equivalently: the graph is **2-colorable**, and it contains **no odd-length cycle**.

### Core Idea

Use a modified BFS: color the source vertex `0`, its direct neighbors `1`, their neighbors `0` again, alternating strictly by layer. If we ever find an edge connecting two same-colored vertices, the graph is **not** bipartite.

### Code

```cpp
#include <vector>
#include <queue>
using namespace std;

bool isBipartiteCheck(int n, vector<vector<int>>& adj, int source = 0) {
    const int INF = 1e9;
    vector<int> color(n, INF);
    color[source] = 0;

    queue<int> q;
    q.push(source);
    bool isBipartite = true;

    while (!q.empty() && isBipartite) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (color[v] == INF) {              // not yet colored
                color[v] = 1 - color[u];         // assign opposite color
                q.push(v);
            } else if (color[v] == color[u]) {   // conflict: same color on an edge
                isBipartite = false;
                break;                            // optional early exit
            }
        }
    }
    return isBipartite;
}
```

**Note:** DFS could also implement this check (see Exercise 4.2.7.4* in the original text), but BFS's natural layer-by-layer structure makes the "alternate colors by layer" logic feel more intuitive here.

**Reference problem:** UVa 10004 - Bicoloring.

**Important caveat:** this basic version only checks bipartiteness starting from **one connected component** (source vertex). For a graph with multiple components, you'd need to loop over all unvisited vertices (similar to the CC-finding pattern in Section 4) to fully verify bipartiteness across the entire graph.

---

## 7. Cycle Check (Directed Graph)

### Framing the Problem

- An **undirected** graph is trivially cyclic by nature — every bidirectional edge `(u,v)` forms a trivial 2-vertex cycle (`u→v→u`).
- A **directed** graph with two parallel directed edges between the same pair also has this trivial cycle issue.
- So, cycle checking for directed graphs is usually defined as: **does a non-trivial cycle of length ≥ 3 edges exist?**

### Three DFS Edge Classifications

Running DFS on a graph produces a **DFS spanning tree/forest**. Using **two vertex states** — `EXPLORED` (currently on the recursion stack, visited but not yet fully completed) and `VISITED` (fully completed) — in addition to `UNVISITED`, we can classify every edge encountered during DFS into one of three types:

1. **Tree edge:** DFS moves from `u` (currently `EXPLORED`) to `v` (currently `UNVISITED`). This is the normal "advance deeper" case — the necessary condition for DFS to progress.

2. **Back/Bidirectional edge:** DFS moves from `u` (`EXPLORED`) to `v` (also `EXPLORED`) — meaning `v` is an **ancestor** of `u` in the current DFS spanning tree.
   - If `v` is `u`'s **direct parent**, this is just a **trivial cycle** (a bidirectional edge, e.g., simple undirected edge `u↔v`).
   - Otherwise, it's a genuine **back edge** — indicating a **non-trivial cycle**.

3. **Forward/Cross edge** (rare in contests): DFS moves from `u` (`EXPLORED`) to `v` where `v` is already `VISITED` (fully completed). This happens when backtracking later discovers an edge to an already-finished subtree.

### Code

```cpp
#include <vector>
#include <cstdio>
using namespace std;

enum { UNVISITED = -1, EXPLORED = -2, VISITED = -3 };

vector<int> dfsNum, dfsParent;
vector<vector<pair<int,int>>> adj;

void cycleCheck(int u) {
    dfsNum[u] = EXPLORED;

    for (auto& [v, w] : adj[u]) {
        printf("Edge (%d, %d) is a ", u, v);

        if (dfsNum[v] == UNVISITED) {              // EXPLORED -> UNVISITED
            printf("Tree Edge\n");
            dfsParent[v] = u;
            cycleCheck(v);
        }
        else if (dfsNum[v] == EXPLORED) {           // EXPLORED -> EXPLORED
            if (v == dfsParent[u])
                printf("Bidirectional Edge\n");      // trivial cycle
            else
                printf("Back Edge (Cycle)\n");       // non-trivial cycle!
        }
        else if (dfsNum[v] == VISITED) {             // EXPLORED -> VISITED
            printf("Forward/Cross Edge\n");           // rare in contests
        }
    }

    dfsNum[u] = VISITED;   // fully done exploring u
}

// usage: run cycleCheck(u) for every unvisited u (handles disconnected graphs)
```

### Worked Example

For the undirected sample graph (Figure 4.1): edges `(0,1)`, `(1,2)`, `(2,3)`, `(3,4)`, `(6,7)`, `(6,8)` are all **bidirectional edges** (trivial cycles from the undirected nature). Edge `3→1` is a genuine **back edge** (real cycle: `0→1→2→3→1`), and edge `1→3` (discovered later, on backtrack) is a **forward/cross edge**.

For a separate sample directed graph (Figure 4.7 in the original text): edges `2→1` and `6→4` are back edges (indicating actual cycles).

### Complexity

`O(V+E)` — same as the base DFS, since this is just an annotation/classification layer added on top of the standard traversal.

---

## 8. Finding Articulation Points and Bridges

### Definitions

- **Articulation Point (Cut Vertex):** a vertex whose removal (along with all incident edges) **disconnects** the graph.
- **Bridge:** an edge whose removal disconnects the graph.
- A graph with **no** articulation points is called **Biconnected**.

*Motivating problem framing:* given a road network with sabotage costs on intersections and roads, find the cheapest single intersection or road to sabotage to disconnect the network — i.e., find the least-cost articulation point or bridge.

### Naive Algorithm — O(V² + VE)

1. Run DFS/BFS once to count the baseline number of Connected Components.
2. For **each** vertex `v`:
   - Temporarily remove `v` and its incident edges.
   - Re-run DFS/BFS — `O(V+E)` — and check if the CC count increased.
   - If yes, `v` is an articulation point. Restore `v`.

This calls DFS/BFS up to `V` times → `O(V × (V+E)) = O(V² + VE)`. Workable for small graphs but not efficient.

### The Efficient O(V+E) Algorithm — Hopcroft & Tarjan

**Two additional DFS attributes tracked per vertex:**

- **`dfsNum(u)`** — the iteration counter recording *when* `u` was first visited (its discovery time).
- **`dfsLow(u)`** — the **lowest** `dfsNum` reachable from the subtree rooted at `u` (including `u` itself), either directly within that subtree, or via **one back edge** leading out of the subtree to an ancestor.

**Initial value:** `dfsLow(u) = dfsNum(u)` at first visit. It can only ever **decrease**, and only decreases when DFS discovers a **back edge** from somewhere in `u`'s subtree to an ancestor with a lower `dfsNum`. (Bidirectional edges — i.e., edges back to the direct parent — do **not** trigger this update.)

### Intuition — Using dfsNum and dfsLow to Detect Articulation Points

**Core rule:** if `u` has a child `v` in the DFS tree with `dfsLow(v) ≥ dfsNum(u)`, then `u` **is** an articulation point.

**Why:** `dfsLow(v) ≥ dfsNum(u)` means **no vertex in `v`'s subtree has a back edge to any ancestor of `u`** — the only way out of `v`'s subtree back toward the rest of the tree is **through `u` itself**. Removing `u` would strand `v`'s entire subtree, disconnecting the graph.

**Special case:** the **root** of the DFS tree (the starting vertex) is an articulation point **only if it has more than one child** in the DFS spanning tree — a trivial case the general rule above doesn't catch (since the root has no "ancestor" to escape to via a back edge in the first place).

### Bridge Detection — Nearly Identical Rule

An edge `(u, v)` (tree edge, with `v` a child of `u`) is a **bridge** if:

$$dfsLow(v) > dfsNum(u)$$

(Note: **strict inequality**, unlike the `≥` used for articulation points.) This means `v`'s subtree has **no** back edge reaching `u` or any ancestor of `u` — so the tree edge `(u,v)` is the **only** connection between `v`'s subtree and the rest of the graph. Removing it disconnects the graph.

### Code

```cpp
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

enum { UNVISITED = -1 };

vector<int> dfsNum, dfsLow, dfsParent, articulationVertex;
vector<vector<pair<int,int>>> adj;
int dfsNumberCounter, dfsRoot, rootChildren;

void articulationPointAndBridge(int u) {
    dfsLow[u] = dfsNum[u] = dfsNumberCounter++;

    for (auto& [v, w] : adj[u]) {
        if (dfsNum[v] == UNVISITED) {                 // tree edge
            dfsParent[v] = u;
            if (u == dfsRoot) rootChildren++;           // track root's children (special case)

            articulationPointAndBridge(v);

            if (dfsLow[v] >= dfsNum[u])                 // articulation point condition
                articulationVertex[u] = 1;

            if (dfsLow[v] > dfsNum[u])                  // bridge condition (strict >)
                printf(" (%d, %d) is a bridge\n", u, v);

            dfsLow[u] = min(dfsLow[u], dfsLow[v]);      // propagate low value upward
        }
        else if (v != dfsParent[u]) {                  // back edge (not the trivial parent edge)
            dfsLow[u] = min(dfsLow[u], dfsNum[v]);
        }
    }
}

int main() {
    int V;
    // ... read V, build adj[] ...

    dfsNum.assign(V, UNVISITED);
    dfsLow.assign(V, 0);
    dfsParent.assign(V, -1);
    articulationVertex.assign(V, 0);
    dfsNumberCounter = 0;

    printf("Bridges:\n");
    for (int u = 0; u < V; u++) {
        if (dfsNum[u] == UNVISITED) {
            dfsRoot = u;
            rootChildren = 0;
            articulationPointAndBridge(u);
            articulationVertex[dfsRoot] = (rootChildren > 1);   // handle root special case
        }
    }

    printf("Articulation Points:\n");
    for (int u = 0; u < V; u++)
        if (articulationVertex[u])
            printf(" Vertex %d\n", u);

    return 0;
}
```

### Worked Example

Two sample graphs traced in the book (both rooted at vertex `0`):

**Graph A (tree-like, no cycles):** since there's no back edge anywhere, `dfsLow(u) = dfsNum(u)` for every vertex at the end. **All edges are bridges** (makes sense — it's a tree, every edge is essential).

**Graph B (has a cycle `1→4→5→1`):** the back edge `5→1` causes `dfsLow(1) = dfsLow(4) = dfsLow(5) = 1` (all can reach back to vertex 1, which has `dfsNum=1`). Result: **vertex 1** is the only articulation point (removing it disconnects `{2,3}` from `{4,5}`). Edges `(1,4)`, `(4,5)`, `(5,1)` — the cycle edges — are **not** bridges, since each can be individually removed while the cycle still provides an alternate path. All other edges (the "tree-only" parts, e.g., edges to vertex 2 or 3) **are** bridges.

### Complexity

`O(V + E)` — a single DFS pass, just with two extra numbers tracked per vertex.

---

## 9. Finding Strongly Connected Components (SCC)

### SCC vs CC — Key Distinction

**Strongly Connected Component (SCC)** is the **directed graph** analog of Connected Components: a maximal set of vertices where **every pair** `(u, v)` in the set has a path `u → v` **and** a path `v → u`.

**Critical distinction from plain CC:** a directed graph can "look" like one connected component (i.e., `dfs(u)` reaches every vertex) while **not** being a single SCC — because reachability in one direction doesn't guarantee reachability back.

**Example:** vertex 1 might reach vertex 0, but if there's no path *back* from 0 to 1, they're in **different** SCCs even though they're mutually "reachable" in the loose undirected sense.

**Contracting SCCs** (replacing each SCC with a single "super-vertex") always yields a **DAG** — a useful structural fact (see Book 2 for applications).

Two classic algorithms: **Kosaraju's algorithm** and **Tarjan's algorithm**.

---

### 9a. Kosaraju's Algorithm

**Two key observations underpinning the algorithm:**

1. **Running `dfs(u)` from a vertex `u` in the "smallest SCC"** (an SCC whose outgoing edges only point back within itself — a "sink" SCC in the SCC-DAG) will **only** visit vertices within that SCC. Running DFS from a vertex in a "non-sink" SCC can "leak" into other SCCs reachable via outgoing edges — so we need a way to always start from a sink SCC first.

2. **The SCCs of a graph and the SCCs of its transposed graph (all edges reversed) are identical.**

**The algorithm combines these two ideas:**

1. **First pass:** run DFS on the **original** graph, recording vertices in **decreasing finishing order** (post-order — same style as topological sort).
2. **Second pass:** run DFS on the **transposed** graph, processing vertices in the order determined by the first pass (highest finishing time first). Each DFS call in this second pass discovers exactly one complete SCC.

**Why this works (intuition):** the vertex with the highest finish time in pass 1 is guaranteed to belong to a "source" SCC in the SCC-DAG (or more precisely, the reversed-graph trick converts sources into sinks, letting DFS on the transpose naturally stay contained within one SCC at a time without leaking).

### Code

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<int> dfsNum;
vector<vector<pair<int,int>>> adj, adjTranspose;
vector<int> finishOrder;   // "S" in the book — stack of finished vertices
int numSCC;

void kosaraju(int u, int pass) {
    dfsNum[u] = 1;   // mark visited
    auto& neighbors = (pass == 1) ? adj[u] : adjTranspose[u];

    for (auto& [v, w] : neighbors)
        if (dfsNum[v] == -1)   // UNVISITED
            kosaraju(v, pass);

    finishOrder.push_back(u);   // record post-order (same idea as topological sort)
}

int findSCCsKosaraju(int N) {
    finishOrder.clear();
    dfsNum.assign(N, -1);

    // first pass: record post-order on the ORIGINAL graph
    for (int u = 0; u < N; u++)
        if (dfsNum[u] == -1)
            kosaraju(u, 1);

    // second pass: explore SCCs on the TRANSPOSED graph,
    // processing vertices in REVERSE finish order (i.e., highest finish time first)
    numSCC = 0;
    dfsNum.assign(N, -1);
    for (int i = N - 1; i >= 0; i--) {
        if (dfsNum[finishOrder[i]] == -1) {
            numSCC++;
            kosaraju(finishOrder[i], 2);
        }
    }

    return numSCC;
}
```

**Building the transpose:**

```cpp
vector<vector<pair<int,int>>> buildTranspose(int V, vector<vector<pair<int,int>>>& adj) {
    vector<vector<pair<int,int>>> adjT(V);
    for (int u = 0; u < V; u++)
        for (auto& [v, w] : adj[u])
            adjT[v].push_back({u, w});
    return adjT;
}
```

### Worked Example

Sample directed graph (Figure 4.7): decreasing finish order from the first pass: `{0, 1, 3, 4, 5, 7, 6, 2}`.

**Second pass on transposed graph:**
- `dfs(0)` on transpose: gets stuck immediately (no outgoing edges from 0 in the transpose) → **first SCC: `{0}`**.
- `dfs(1)`: reaches `{1, 2, 3}` (doesn't cross to `{0}` since vertex 0 already visited — "virtually removed") → **second SCC: `{1, 2, 3}`**.
- `dfs(3)` is skipped (already visited as part of the previous SCC).
- `dfs(4)`: reaches `{4, 5, 6, 7}` → **third SCC: `{4, 5, 6, 7}`**.

**Total: 3 SCCs.**

### Complexity

`O(V + E)` — two full DFS passes, each linear.

**Practical note:** Kosaraju's requires building/maintaining the **transposed graph** upfront and needs **two full passes** through the graph data structure.

---

### 9b. Tarjan's Algorithm

### Core Idea

SCCs form **subtrees** within the DFS spanning tree. Tarjan's algorithm computes `dfsNum(u)` and `dfsLow(u)` similarly to the articulation-points algorithm, but with a key difference in how `dfsLow` gets updated, plus an explicit **stack** to track the current "candidate" SCC members.

**Key mechanics:**
- Maintain a stack `S`, pushing each vertex `u` onto it as it's first visited.
- Maintain a boolean `onStack`/`visited` flag array — only vertices **currently on the stack** (i.e., part of the "current" unfinished SCC candidates) can be used to update `dfsLow(u)`.
- **Root of an SCC detected when:** `dfsLow(u) == dfsNum(u)` — at this point, **pop the stack** repeatedly until `u` itself is popped; everything popped in this process belongs to the same SCC as `u`.

### Code

```cpp
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int dfsNumberCounter, numSCC;
vector<int> dfsNum, dfsLow, onStack;
vector<vector<pair<int,int>>> adj;
stack<int> St;

void tarjanSCC(int u) {
    dfsLow[u] = dfsNum[u] = dfsNumberCounter++;
    St.push(u);
    onStack[u] = 1;

    for (auto& [v, w] : adj[u]) {
        if (dfsNum[v] == -1)             // UNVISITED
            tarjanSCC(v);
        if (onStack[v])                   // only update via vertices still "in play"
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
    }

    if (dfsLow[u] == dfsNum[u]) {         // u is the root of an SCC
        numSCC++;
        while (true) {
            int v = St.top();
            St.pop();
            onStack[v] = 0;
            if (u == v) break;
        }
    }
}

int findSCCsTarjan(int V) {
    dfsNum.assign(V, -1);
    dfsLow.assign(V, 0);
    onStack.assign(V, 0);
    while (!St.empty()) St.pop();
    dfsNumberCounter = numSCC = 0;

    for (int u = 0; u < V; u++)
        if (dfsNum[u] == -1)
            tarjanSCC(u);

    return numSCC;
}
```

### Worked Example

Sample graph (Figure 4.8): running Tarjan's, the stack content evolves as:

- When vertex `4` is found to satisfy `dfsLow(4) == dfsNum(4) == 4`: stack contains `{0,1,3,2,4,5,7,6}`. Pop until we reach `4`: **SCC = `{4,5,6,7}`**.
- Next, vertex `1` satisfies `dfsLow(1) == dfsNum(1) == 1`: stack now contains `{0,1,3,2}`. Pop until we reach `1`: **SCC = `{1,2,3}`**.
- Finally: **SCC = `{0}`**.

**Total: 3 SCCs** — matches Kosaraju's result, as expected (both algorithms always agree on the SCC structure, just discover them differently).

### Complexity

`O(V + E)` — this is essentially a single DFS pass with constant extra bookkeeping per vertex; the SCC-reporting stack-popping loop runs in **amortized** `O(V)` total across the whole algorithm, since each vertex is popped from the stack exactly once.

**Practical note:** unlike Kosaraju's, Tarjan's needs **no graph transpose** and only requires **one pass**.

---

### Kosaraju's vs Tarjan's — Comparison

| Aspect | Kosaraju's | Tarjan's |
|---|---|---|
| Number of DFS passes | 2 | 1 |
| Needs transposed graph? | ✅ Yes | ❌ No |
| Extra data structure | Post-order stack | Stack + `onStack` flags |
| Complexity | `O(V+E)` | `O(V+E)` |
| Conceptual ease | Easier to understand intuitively | Extends naturally from the articulation-points technique |

**Both are considered equally good** for solving standard SCC problems in competitive programming — pick whichever you find easier to memorize/implement, or bring both as printed library code if your contest format allows hard-copy references (e.g., ICPC).

---

## 10. Complexity Summary Table

| Technique | Complexity | Key Data Structure | Contest Frequency |
|---|---|---|---|
| DFS (basic) | `O(V+E)` | Recursion / implicit stack | Foundational — used everywhere |
| BFS (basic) | `O(V+E)` | Explicit queue | Foundational — used everywhere |
| Connected Components | `O(V+E)` | DFS/BFS restart loop | Rarely asked directly |
| Flood Fill | `O(V+E)` (grid: `R×C`) | DFS/BFS on implicit grid | Historically frequent, declining |
| Topological Sort (DFS-based) | `O(V+E)` | Post-order DFS | Rare directly; key preprocessing step for DP-on-DAG |
| Topological Sort (Kahn's) | `O(V+E)` or `O((V+E)log V)` | In-degree + queue/PQ | Used when tie-breaking order matters |
| Bipartite Check | `O(V+E)` | Modified BFS (2-coloring) | Less common now |
| Cycle Check (directed) | `O(V+E)` | DFS with 3-state tracking | Less common now |
| Articulation Points/Bridges | `O(V+E)` | DFS with `dfsNum`/`dfsLow` | Less common now |
| SCC (Kosaraju's) | `O(V+E)` | 2-pass DFS + transpose | Still relevant, esp. for cycle-contraction problems |
| SCC (Tarjan's) | `O(V+E)` | 1-pass DFS + stack | Still relevant, esp. for cycle-contraction problems |

### Practical Takeaways

1. **DFS is generally preferred** over BFS for pure structural traversal problems (finding CCs, cycles, articulation points, SCCs) — it tends to use less memory and many of these advanced techniques are natural DFS extensions.
2. **BFS's unique strength** is layer-by-layer traversal — reserved specifically for **SSSP on unweighted graphs**, where DFS cannot replicate this property.
3. Many of these techniques are **simple modifications** of the same base DFS/BFS code — mastering the base traversal thoroughly makes all these variants much easier to pick up.
4. **Kosaraju's/Tarjan's SCC algorithms** remain relevant in modern contests, particularly for problems requiring **cycle contraction** to convert a general directed graph into a DAG before applying DP or other DAG-specific techniques.
