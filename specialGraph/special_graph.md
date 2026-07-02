# Special Graphs — Complete Notes

*Based on Competitive Programming 4 (CP4) by Steven Halim, Section 4.6*
*(Code rewritten in plain, standard C++ — no book macros like `vi`, `vii`, `AL`, `ii`)*

---

## Table of Contents

1. [Overview](#1-overview)
2. [Directed Acyclic Graph (DAG)](#2-directed-acyclic-graph-dag)
3. [Tree](#3-tree)
4. [Bipartite Graph](#4-bipartite-graph)
5. [Eulerian Graph](#5-eulerian-graph)
6. [Special Graphs in Programming Contests — Summary](#6-special-graphs-in-programming-contests--summary)

---

## 1. Overview

Some basic graph problems have **simpler or faster polynomial algorithms** if the given graph has special structure. Four special graphs commonly appear in programming contests, in decreasing estimated frequency:

1. **Directed Acyclic Graph (DAG)**
2. **Tree**
3. **Bipartite Graph**
4. **Eulerian Graph**

**Why this matters in contests:** problem authors often deliberately choose large input sizes specifically to force a Time Limit Exceeded (TLE) verdict on a general-graph algorithm, when a much faster specialized algorithm exists for the special-graph version of the same problem. Recognizing the special structure is often the entire "trick" to a problem.

All four special graphs discussed in this section are part of the IOI syllabus (as of 2020).

---

## 2. Directed Acyclic Graph (DAG)

### Definition

A **DAG** is a graph that is (1) **directed**, and (2) has **no cycle** — guaranteed by definition.

### Why DAGs Are Perfect for Dynamic Programming

**Key insight:** a DP recurrence must be **acyclic** (state `A` cannot depend on state `B` which depends back on `A`, or the recursion never terminates). This means:

> **DP states = vertices of an implicit DAG. Acyclic transitions between DP states = directed edges of that DAG.**

**Topological sort** of this implicit DAG guarantees each overlapping sub-problem (each vertex/subgraph of the DAG) is processed exactly **once** — this is the same principle underlying memoization/bottom-up DP table filling.

---

### 2a. (Single-Source) Shortest Paths on DAG

**Why SSSP is easier on a DAG:** a DAG always has at least one valid **topological order**. Using the `O(V+E)` topological sort algorithm, we can find one such order, then relax outgoing edges **according to this order**.

**Why this guarantees correctness in one linear pass:** the topological order ensures that if vertex `Y` has an incoming edge from vertex `X`, then `Y` is only relaxed **after** `X` has already obtained its correct shortest-distance value. There's no need for a priority queue (Dijkstra's) or repeated relaxation (Bellman-Ford) — a single `O(V+E)` linear pass through the topological order suffices.

**This is also literally the essence of bottom-up DP**: filling a DP table in topological order of the underlying DP-recurrence DAG avoids ever recomputing a state before its dependencies are ready.

### Code — SSSP on DAG

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<int> sssp_on_dag(int V, vector<vector<pair<int,int>>>& adj, int source) {
    const int INF = 1e9;

    // Step 1: get a topological order (via DFS-based method, see Topological Sort notes)
    vector<bool> visited(V, false);
    vector<int> topoOrder;

    // simple DFS-based topological sort
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (auto& [v, w] : adj[u])
            if (!visited[v]) dfs(v);
        topoOrder.push_back(u);
    };
    for (int u = 0; u < V; u++)
        if (!visited[u]) dfs(u);
    reverse(topoOrder.begin(), topoOrder.end());

    // Step 2: relax edges strictly in topological order
    vector<int> dist(V, INF);
    dist[source] = 0;

    for (int u : topoOrder) {
        if (dist[u] == INF) continue;
        for (auto& [v, w] : adj[u])
            dist[v] = min(dist[v], dist[u] + w);
    }

    return dist;
}
```

**Complexity:** `O(V+E)` — dramatically faster than general-graph Dijkstra's `O((V+E) log V)`.

---

### 2b. (Single-Source) Longest Paths on DAG

**The problem:** find the longest **simple** paths from a starting vertex `s` to all other vertices.

**Why the general-graph version is hard:** on a general graph with positive weighted edges, the "longest path" problem is **ill-defined** — you could loop around a positive-weight cycle infinitely to make the path arbitrarily long (mirrors the negative-cycle issue in shortest-path problems). The **decision version** of this problem ("does a simple path of total weight ≥ k exist?") is **NP-complete** on general graphs.

**Why it's easy on a DAG:** since a DAG has no cycles, **every path is automatically simple** — there's no possibility of infinite-length exploitation. So the "longest path" problem is well-defined and tractable.

**Solution — a trivial tweak of the SSSP-on-DAG solution:**

> **Multiply all edge weights by `-1`, run the exact same SSSP-on-DAG algorithm, then negate the resulting distances.**

(Finding the *shortest* path in a negated-weight graph is equivalent to finding the *longest* path in the original.)

```cpp
vector<int> longest_path_on_dag(int V, vector<vector<pair<int,int>>>& adj, int source) {
    // negate all edge weights
    vector<vector<pair<int,int>>> negAdj(V);
    for (int u = 0; u < V; u++)
        for (auto& [v, w] : adj[u])
            negAdj[u].push_back({v, -w});

    vector<int> negDist = sssp_on_dag(V, negAdj, source);

    vector<int> longestDist(V);
    for (int u = 0; u < V; u++)
        longestDist[u] = -negDist[u];   // negate back

    return longestDist;
}
```

**Note:** this can actually be **multi-source** — you can start from any vertex with in-degree 0.

### Application — Project Scheduling (PERT)

**Reference:** UVa 00452 - Project Scheduling (Project Evaluation and Review Technique).

Model sub-project dependencies as a DAG, with each vertex weighted by the **time needed to complete that sub-project**. The **shortest possible time to finish the entire project** = the **longest path** in this DAG (the **critical path**), starting from any 0-in-degree vertex.

**Example:** 6 sub-projects. The longest path `0 → 1 → 2 → 4 → 5` with total time `16` determines the minimum time to finish the whole project. To hit this minimum, **every** sub-project along the critical path must be completed on time — any delay along the critical path delays the entire project.

---

### 2c. Counting Paths in DAG

**Reference:** UVa 00988 - Many paths, one destination.

**Problem:** given a DAG representing life choices (birth at vertex `0`, death at vertex `n`), count how many distinct paths lead from birth to death.

**Why this is a DAG:** you can only move **forward in time**, never backward.

### Solution — Bottom-Up

```cpp
vector<long long> countPathsDAG(int V, vector<vector<int>>& adj, int source) {
    // Step 1: topological sort (source will naturally be first)
    vector<bool> visited(V, false);
    vector<int> topoOrder;
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) if (!visited[v]) dfs(v);
        topoOrder.push_back(u);
    };
    for (int u = 0; u < V; u++) if (!visited[u]) dfs(u);
    reverse(topoOrder.begin(), topoOrder.end());

    // Step 2: propagate path counts forward along topological order
    vector<long long> numPaths(V, 0);
    numPaths[source] = 1;

    for (int u : topoOrder) {
        for (int v : adj[u])
            numPaths[v] += numPaths[u];
    }

    return numPaths;   // numPaths[destination] = answer
}
```

**How it works:** `numPaths[0] = 1` (base case — one "path" that is just standing at the start). Process vertices in topological order; for each vertex `u`, propagate its count forward to each neighbor `v` by **adding** (`+=`, not overwriting) — since multiple predecessors may contribute paths to the same `v`.

**Complexity:** `O(V+E)` — each vertex processed once, each edge relaxed once.

---

### 2d. Bottom-Up vs Top-Down Implementations

All three solutions above (shortest paths, longest paths, counting paths on DAG) are **Bottom-Up DP solutions**: start from known base case(s), then use the topological order to propagate correct information forward — never backtracking.

### Top-Down Equivalent (Memoized Recursion)

Using the counting-paths example, define `numPaths(i)` = number of paths from vertex `i` to destination `n`:

$$numPaths(n) = 1 \quad \text{(base case: at the destination, exactly one "path" — staying put)}$$
$$numPaths(i) = \sum_{j \text{ adjacent to } i} numPaths(j)$$

```cpp
#include <vector>
using namespace std;

vector<long long> memo;
vector<bool> computed;
vector<vector<int>> adj;
int destination;

long long numPathsTopDown(int i) {
    if (i == destination) return 1;
    if (computed[i]) return memo[i];

    long long total = 0;
    for (int j : adj[i])
        total += numPathsTopDown(j);

    computed[i] = true;
    return memo[i] = total;
}
```

**Complexity:** also `O(V+E)` — `O(V)` distinct states, each vertex processed once; `O(E)` edges, each visited at most once. Same as the bottom-up approach, just organized via recursion + memoization instead of an explicit topological-order loop.

**Key structural difference:** bottom-up computes values **from source toward destination**; top-down computes values **from destination back toward source** (following the recursive calls backward) — but both reach the identical final answer, since the underlying DAG structure and recurrence are the same.

---

### 2e. Converting a General Graph to a DAG

In harder contest problems, the given graph is **not explicitly a DAG**. However, if we **add one or more extra parameters** to each vertex (expanding the state space), the resulting *augmented* graph can become a DAG — at which point standard DP techniques (top-down or bottom-up) apply directly.

### Worked Example — SPOJ FISHER (Fishmonger)

**Problem:** given `n` cities, available time `t`, and matrices for travel time and tolls between city pairs, find a route from the port (vertex `0`) to the market (vertex `n-1`) that:
- Minimizes total tolls paid, **while**
- Arriving within the allotted time `t` (a **hard constraint** — must be satisfied or there's no valid answer).

**Why plain Dijkstra's fails:** these two requirements (minimize tolls, respect a time budget) are **not independent**. Picking the fastest route might not minimize tolls; picking the cheapest-toll route might blow the time budget. Neither pure "shortest time" nor pure "shortest toll" Dijkstra's run solves this correctly.

**The DAG conversion trick — attach a parameter `timeLeft` to each vertex:**

> Instead of a vertex just being "current city," a vertex becomes the pair `(city, timeLeft)`.

Every time the fishmonger moves from city `cur` to city `X`, we move to modified vertex `(X, timeLeft - travelTime[cur][X])` via an edge weighted by `toll[cur][X]`.

**Why this guarantees a DAG:** `timeLeft` is a **strictly diminishing resource** — every move consumes some in it. Since it can only decrease, there's no way to ever return to a previously visited state — cycles are structurally impossible.

### Code — Top-Down DP on the Augmented State-Space DAG

```cpp
#include <vector>
#include <map>
using namespace std;

const int INF = 1e9;
int n;
vector<vector<int>> travelTime, toll;
map<pair<int,int>, pair<int,int>> memo;   // memo[{cur, timeLeft}] = {tollPaid, timeNeeded}

pair<int,int> dp(int cur, int timeLeft) {
    if (timeLeft < 0) return {INF, INF};          // invalid state, prune
    if (cur == n - 1) return {0, 0};                // reached the market

    auto key = make_pair(cur, timeLeft);
    if (memo.count(key)) return memo[key];

    pair<int,int> ans = {INF, INF};
    for (int X = 0; X < n; X++) {
        if (cur == X) continue;
        auto [tollPaid, timeNeeded] = dp(X, timeLeft - travelTime[cur][X]);
        if (tollPaid + toll[cur][X] < ans.first) {
            ans.first = tollPaid + toll[cur][X];
            ans.second = timeNeeded + travelTime[cur][X];
        }
    }

    return memo[key] = ans;
}

// call dp(0, t) to get the answer
```

**Why Top-Down is convenient here:** we do **not** need to explicitly build the augmented DAG or compute its topological order — the recursion handles this implicitly, only visiting reachable, valid `(city, timeLeft)` states.

**Complexity:** there are only `O(n·t)` distinct states, each computable in `O(n)` (looping over all possible next cities), giving `O(n²·t)` overall — feasible for the given constraints (`n ≤ 50`, `t ≤ 1000`).

---

### 2f. DP as Algorithms on DAG — Revisiting Classic DP Problems

**Key re-framing:** many classic DP problems that "minimize this," "maximize that," or "count something" are secretly computing the **shortest path, longest path, or path count** on an (often implicit) DP-recurrence DAG.

### Coin-Change as Shortest Paths on DAG

**Setup:** `n=2` coin denominations `{1, 5}`, target amount `V=10`. Model each vertex as "current remaining value." Each vertex `v` has (up to) `n=2` unweighted edges to `v-1` and `v-5` (whichever don't go negative).

**Observation:** this is a DAG (values only decrease), with overlapping sub-problems (some values reachable via multiple paths — e.g., both "5 then 5" and "1 five times" reach value 0 from different routes).

**Solution:** find the **shortest path** on this DAG from source `V=10` to target `V=0`. Valid topological order: simply process vertices in **decreasing** order, `{10, 9, 8, ..., 1, 0}`.

Since the graph is unweighted here, plain **BFS** also works (`O(V+E)`) — using Dijkstra's would be correct but overkill for an unweighted DAG.

**Result:** path `10 → 5 → 0` with total weight `2` (2 coins needed) — matching the greedy Coin-Change solution for this particular test case.

### 0-1 Knapsack as Longest Paths on DAG

**Setup:** `n=5` items with values `V={4,2,10,1,2}` and weights `W={12,1,4,1,2}`, capacity `S=15`. Model each vertex as a pair `(id, remainingWeight)`.

- **Always** an edge `(id, remW) → (id+1, remW)` — corresponds to **not taking** item `id`.
- **Sometimes** an edge `(id, remW) → (id+1, remW - W[id])` (if `W[id] ≤ remW`) — corresponds to **taking** item `id`, with edge weight `V[id]`.

**Solution:** find the **longest path** on this DAG from source `(0, 15)` to any target `(5, *)`.

**Answer path:** `(0,15) → (1,15) → (2,14) → (3,10) → (4,9) → (5,7)` with total value `0+2+10+1+2 = 15`.

### Counting Paths — UVa 10943 (How Do You Add?)

For test case `n=3, K=4`, drawing the underlying DAG and **counting the number of paths** in it directly gives the answer: **20** — matching the combinatorial formula `C(n+K-1, K-1)`.

### The General Pattern

| DP Problem Type | Equivalent DAG Problem |
|---|---|
| "Minimize X" | **Shortest path** on the implicit DP-recurrence DAG |
| "Maximize X" | **Longest path** on the implicit DP-recurrence DAG |
| "Count the number of ways" | **Counting paths** in the implicit DP-recurrence DAG |

This DAG-based viewpoint on DP is not commonly emphasized in other textbooks, but it provides a powerful unifying lens: **TSP** ≈ shortest paths on an implicit DAG; **Longest Increasing Subsequence (LIS)** ≈ longest paths on an implicit DAG.

---

## 3. Tree

### Definition

A **Tree** is a special graph with:
- `E = V - 1` (so any `O(V+E)` algorithm on a tree simplifies to `O(V)`)
- No cycle
- Connected
- **Exactly one unique path** between any pair of vertices

**Related terms:**
- Adding one extra edge to a tree creates exactly one cycle — this is called a **Pseudotree**.
- Removing any existing edge **disconnects** the tree.

---

### 3a. Tree Traversal

For a **rooted binary tree**, simpler traversal algorithms exist beyond general DFS/BFS — though they offer no asymptotic speedup (still `O(V)`), just simpler code:

```cpp
struct Node {
    int val;
    Node* left;
    Node* right;
};

void preOrder(Node* v) {
    if (!v) return;
    visit(v);
    preOrder(v->left);
    preOrder(v->right);
}

void inOrder(Node* v) {
    if (!v) return;
    inOrder(v->left);
    visit(v);
    inOrder(v->right);
}

void postOrder(Node* v) {
    if (!v) return;
    postOrder(v->left);
    postOrder(v->right);
    visit(v);
}
```

**Note:** level-order traversal is simply BFS.

---

### 3b. Finding Articulation Points and Bridges in a Tree

**General-graph solution:** Tarjan's `O(V+E)` DFS algorithm with `dfsNum`/`dfsLow` (see Graph Traversal notes).

**Tree simplification:**

> **All edges in a tree are bridges. All internal vertices (degree > 1) are articulation points.**

This is intuitively obvious: since a tree has exactly one path between any two vertices, removing *any* edge necessarily disconnects it (definition of bridge), and removing any non-leaf vertex necessarily strands at least one subtree (definition of articulation point).

Still `O(V)` — we just scan the tree once to count internal vertices — but the code is dramatically simpler than the general Tarjan-based algorithm.

---

### 3c. Single-Source Shortest Paths on a Weighted Tree

**General-graph solution:** Dijkstra's `O((V+E) log V)` or Bellman-Ford `O(V·E)`.

**Tree simplification:**

> Since there's only **one unique path** between any two vertices in a tree, simply **traverse the tree** (BFS or DFS, `O(V)`) to find that unique path. The shortest path weight is just the **sum of edge weights** along it.

```cpp
#include <vector>
using namespace std;

// Find shortest path weight from source to target in a weighted tree
int sssp_on_tree(vector<vector<pair<int,int>>>& treeAdj, int source, int target) {
    vector<int> dist(treeAdj.size(), -1);
    dist[source] = 0;

    vector<int> stack = {source};
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (u == target) return dist[u];
        for (auto& [v, w] : treeAdj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                stack.push_back(v);
            }
        }
    }
    return dist[target];
}
```

**Example:** from vertex `5` to vertex `3` in a sample tree, the unique path `5 → 0 → 1 → 3` has weight `4+2+9 = 15`.

**Complexity:** `O(V)` per query — no priority queue, no repeated relaxation needed.

---

### 3d. All-Pairs Shortest Paths on a Weighted Tree

**General-graph solution:** Floyd-Warshall `O(V³)`.

**Tree simplification:**

> Simply repeat the SSSP-on-tree traversal `V` times, once per source vertex.

**Complexity:** `O(V × V) = O(V²)` — a full order of magnitude faster than Floyd-Warshall's `O(V³)`.

**Even faster (advanced):** using **Lowest Common Ancestor (LCA)** techniques, APSP on a weighted tree can be solved even faster than `O(V²)` (left as an advanced exercise in the original text — Exercise 4.6.2.3*).

---

### 3e. Diameter of a Weighted Tree

**Definition:** the diameter of a graph is the **greatest shortest-path length** between any pair of vertices.

**General-graph solution:** `O(V³)` Floyd-Warshall, plus an additional `O(V²)` scan over all pairs to find the maximum — total `O(V³)`.

**Tree simplification — the "double DFS/BFS" trick:**

> 1. Run DFS/BFS from **any** arbitrary vertex `s` to find the **furthest** vertex `x` from `s`.
> 2. Run DFS/BFS again, this time from `x`, to find the furthest vertex `y` from `x`.
> 3. The **unique path from `x` to `y`** has length equal to the tree's diameter.

```cpp
#include <vector>
using namespace std;

pair<int,int> farthestVertex(vector<vector<pair<int,int>>>& treeAdj, int start) {
    int n = treeAdj.size();
    vector<int> dist(n, -1);
    dist[start] = 0;
    vector<int> stack = {start};
    int farthest = start;

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        if (dist[u] > dist[farthest]) farthest = u;
        for (auto& [v, w] : treeAdj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + w;
                stack.push_back(v);
            }
        }
    }
    return {farthest, dist[farthest]};
}

int treeDiameter(vector<vector<pair<int,int>>>& treeAdj) {
    auto [x, _] = farthestVertex(treeAdj, 0);       // step 1: any start -> find x
    auto [y, diameter] = farthestVertex(treeAdj, x); // step 2: x -> find y (and the diameter)
    return diameter;
}
```

**Why this works (intuition):** this is a classical tree-diameter theorem — starting from *any* vertex and finding the farthest point `x` guarantees `x` is one endpoint of **some** diameter-achieving path (proof left as an exercise — see Exercise 4.6.2.4* in the original text). Repeating from `x` then finds the true opposite endpoint `y`.

**Complexity:** just **two** `O(V)` traversals — dramatically simpler and faster than the general `O(V³)` approach.

**Example:** starting from `s=1`, the furthest vertex found is `x=2`. Starting again from `x=2`, the furthest vertex is `y=5`, with path `2→3→1→0→5` and total length **20** — the tree's diameter.

---

## 4. Bipartite Graph

### Definition Recap

`V` splits into disjoint sets `V1, V2` such that every edge connects a vertex in `V1` to a vertex in `V2`. Bipartite graphs are free of **odd-length cycles**. Note: **a Tree is always Bipartite.**

---

### 4a. Max Cardinality Bipartite Matching (MCBM)

**Motivating problem (Topcoder Open 2009):** given a list of distinct numbers `N`, find every number that can be paired with `N[0]` such that **all** numbers can be simultaneously paired up, with every pair summing to a **prime**.

**Why this is a Bipartite Matching problem:** to get a prime sum from two *distinct* numbers, you need **1 odd + 1 even** (odd+odd or even+even both give an even sum > 2, which can't be prime). So:

> Split numbers into `oddSet` and `evenSet`. Add an edge `i → j` (`i` from oddSet, `j` from evenSet) if `oddSet[i] + evenSet[j]` is prime.

This is now a **Bipartite Graph** — and the question becomes: can every vertex be matched (a **perfect matching**)?

**Solving approach:**
1. If `|oddSet| ≠ |evenSet|`, a complete pairing is impossible — answer is empty.
2. Otherwise, for each candidate `k`, try forcing the match `N[0] ↔ set2[k]`, then run **Max Cardinality Bipartite Matching (MCBM)** on the rest. If the remaining graph achieves a **perfect matching** (`n/2 - 1` more pairs), `set2[k]` is a valid answer.

---

### 4b. The Augmenting Path Algorithm for MCBM

### Key Definitions

- **Free (unmatched) vertex:** a vertex not currently part of any matching.
- **Augmenting path:** a path starting at a free vertex on the **left** set, alternating **free edge, matched edge, free edge, ...**, and ending at a free vertex on the **right** set.

### Berge's Lemma (1957)

> A matching `M` in graph `G` is **maximum** (has the max possible number of edges) **if and only if** there is **no augmenting path** left in `G`.

The augmenting path algorithm is a **direct implementation** of this lemma: repeatedly find and "flip" augmenting paths (swap free ↔ matched status along the path) until none remain.

### Why Flipping an Augmenting Path Increases the Matching by 1

An augmenting path alternates `free, matched, free, matched, ..., free` — it has **one more free edge than matched edge**. Flipping every edge's status (free↔matched) along this path converts all the *free* edges into matched ones and vice versa — net result: **exactly one more** matched edge overall, and both endpoints (previously free) become matched.

### Code

```cpp
#include <vector>
using namespace std;

vector<int> match;   // match[R] = the left vertex matched to right vertex R, or -1
vector<bool> vis;
vector<vector<int>> adj;   // adj[L] = list of right-vertices L connects to

bool augment(int L) {
    if (vis[L]) return false;    // already tried this left vertex in this search, skip
    vis[L] = true;

    for (int R : adj[L]) {
        // R is either free (match[R] == -1), or matched to someone we can re-route
        if (match[R] == -1 || augment(match[R])) {
            match[R] = L;         // flip: R now matched to L
            return true;           // successfully found (and applied) an augmenting path
        }
    }
    return false;   // no augmenting path found from L
}

int maxBipartiteMatching(int totalVertices, int leftSize) {
    match.assign(totalVertices, -1);
    int mcbm = 0;

    for (int L = 0; L < leftSize; L++) {
        vis.assign(leftSize, false);   // reset visited before each new search
        if (augment(L)) mcbm++;
    }

    return mcbm;
}
```

**Trace example:** left set `{1,2}` (0-indexed internally), right set `{3,4}`.

1. Start with free vertex `1`. Algorithm might "greedily" match `1↔3` first (if `3` appears before `4` in `1`'s adjacency list), since `1-3` is already a trivially valid augmenting path.
2. Next, from free vertex `2`: try edge `2-3` — but `3` is already matched to `1`. Recursively try to re-route `1` (`augment(1)` again, but with `vis[3]` semantics guarding against infinite loops): `1` can instead go to `4` (a still-free vertex). So the augmenting path is `2 → 3 → 1 → 4`.
3. **Flip** this path: `2-3` becomes matched, `3-1` becomes free, `1-4` becomes matched. Net result: **2 matchings** (`2↔3` and `1↔4`) — one more than before.

### Complexity

The algorithm repeats `O(E)`-cost DFS-like search up to `V` times (once per free left-vertex) → **`O(V·E)`** overall.

**Applications beyond simple MCBM:** Max Independent Set in Bipartite Graph, Min Vertex Cover in Bipartite Graph, and Min Path Cover on DAG — all reducible to MCBM (covered in Book 2).

---

## 5. Eulerian Graph

### Definitions

- **Eulerian path (technically a *trail*):** a walk that traverses **every edge** exactly once. (A **trail** allows repeated vertices but no repeated edges — unlike a strict "path" which disallows both.)
- **Eulerian tour/circuit:** a *closed* Eulerian path (starts and ends at the same vertex).
- A graph is **Eulerian** if it has an Eulerian tour.

**Contrast with Hamiltonian tour:** a Hamiltonian tour visits every **vertex** exactly once. Despite the superficial similarity, finding a Hamiltonian tour is **NP-hard**, while finding an Eulerian tour is solvable in **polynomial time** — a striking asymmetry.

### Historical Origin — The Königsberg Bridges Problem

Euler's 1736 solution to this problem is one of the founding results of graph theory: can all seven bridges of Königsberg be crossed exactly once in a single trip? Euler proved: **no** — no such trail exists for that particular graph.

---

### 5a. Checking If a Graph Is Eulerian

**Undirected graph:** Eulerian **if and only if**:
1. The graph is **connected**, and
2. **Every vertex has even degree**.

**Why even degree is required (intuition):** a closed trail passing through vertex `u` must use an **even** number of edges incident to `u` — for every edge that enters `u`, another edge must leave to continue the trail (except the very start/end, which coincide in a closed tour).

**Special case — Eulerian path (not necessarily closed):** if **exactly two** vertices have odd degree (and the rest are even), an Eulerian **path** (not a closed tour) exists, starting at one odd-degree vertex and ending at the other.

**Directed graph:** Eulerian **if and only if**:
1. Every vertex has **equal in-degree and out-degree**, and
2. The graph is **connected** (treating edges as undirected for this connectivity check — no need to explicitly compute SCC; simply checking "connected if we ignore direction" is sufficient, since satisfying the degree-balance condition alongside undirected-connectivity guarantees the graph forms one single SCC).

**Directed Eulerian path (not closed):** if exactly one vertex `u` has exactly one *extra* outgoing edge, and exactly one vertex `v` has exactly one *extra* incoming edge (all other vertices balanced), an Eulerian path exists from `u` to `v`.

---

### 5b. Finding an Eulerian Path — Two Algorithms

### Fleury's Algorithm — O(E²)

Starting at an arbitrary vertex, at each step choose the next edge to traverse such that its removal **would not disconnect** the graph — unless it's the *only* remaining edge from the current vertex, in which case take it. This requires re-checking for bridges at every single edge traversal (removed from the shrinking remaining graph), giving `O(E²)` total — relatively slow.

### Hierholzer's Algorithm — O(E) (Preferred)

**Core idea:**
1. Starting from any vertex `u`, find **any** trail through the graph until it returns to `u`. (This is guaranteed to be possible on a Eulerian graph — since every vertex has even degree, you can never get "stuck" anywhere except back at `u`, since for every incoming edge there's a matching outgoing edge.)
2. This gives a **closed trail**, but it might not yet include all edges.
3. Whenever a vertex `v` **within** the current trail still has un-traversed incident edges, find **another** closed trail starting from `v` in the *remaining* graph, then **splice/merge** it into the existing trail at `v`.
4. Repeat until no vertex has any remaining un-traversed edges — the resulting trail is the full Eulerian tour.

**Worked example:** starting trail `ABCDA`. Vertices `A` and `C` still have un-traversed edges. Expand vertex `A`: find closed trail `AGFA`, splice in → `ABCDAGFA` (replacing the visited `A` with `AGFA`). Vertex `F` still has an edge left. Expand `F`: find closed trail `FCEF`, splice in → `ABCDAGFCEFA`. No vertices have remaining edges — done. Final Eulerian tour: **`ABCDAGFCEFA`**.

**Note:** the order in which you choose to expand vertices with leftover edges doesn't affect correctness — any valid choice works, though different choices produce different (equally valid) Eulerian tours.

### Iterative Implementation (Two-Stack Method)

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<int> hierholzer(int N, vector<vector<int>>& adj, int source) {
    vector<int> ans;               // output trail
    vector<int> idx(N, 0);          // next unexplored edge index per vertex
    vector<int> st;                  // current trail stack

    st.push_back(source);

    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)adj[u].size()) {   // u still has an unexplored outgoing edge
            st.push_back(adj[u][idx[u]]);
            idx[u]++;
        } else {
            ans.push_back(u);        // u is fully exhausted, commit it to the trail
            st.pop_back();
        }
    }

    reverse(ans.begin(), ans.end());   // result comes out reversed
    return ans;
}
```

**How it works:**
- `st` holds the **current in-progress trail**.
- Whenever the top vertex `u` of `st` still has an unexplored outgoing edge, push the next neighbor onto `st` (extend the trail).
- Whenever `u` has **no** remaining unexplored edges, it's "done" — pop it from `st` and append it to the final answer `ans`.
- The `reverse()` at the end is needed because vertices get appended to `ans` in the order they're **finished** (post-order-like), similar to the topological sort / SCC finishing-order pattern seen elsewhere in this collection.

**Important:** both `ans` and `st` contain **valid trails at any point in time** during execution — a useful property that can be exploited to find a trail of a specific length if needed.

**Handling undirected graphs:** this implementation is written for **directed** graphs. For undirected graphs, you must explicitly **flag edges as used** (e.g., using a `map`/`set`, or maintaining linked references to bidirectional edge pairs so the reverse copy can be erased in `O(1)`) to avoid traversing the same undirected edge twice (once in each direction).

**Complexity:** `O(E)` — each edge is pushed and popped from the stack exactly once, dramatically better than Fleury's `O(E²)`.

---

## 6. Special Graphs in Programming Contests — Summary

### Relative Popularity

| Special Graph | Contest Frequency | Notes |
|---|---|---|
| **DAG** | Most popular | DP-on-DAG (or DP-on-Tree) is a common IOI task; typically has efficient solutions so input sizes are usually large |
| **Tree** | Very popular | Same reasoning as DAG |
| **Bipartite Graph** | Next most popular | Foundation for Network Flow and Bipartite Matching problems (Book 2); ICPC and IOI contestants should master the augmenting path MCBM algorithm |
| **Eulerian Graph** | Rare (2000–2020 data) | When it *does* appear, it's often a "decider" problem — i.e., pivotal to solving |

### Other Rare Special Graphs (Not Covered in Depth)

| Special Graph | Key Property |
|---|---|
| **Planar Graph** | No `K5` or `K3,3` subgraph (Kuratowski's theorem); 4-colorable; `E = O(V)` |
| **Complete Graph `Kn`** | Maximally dense; connected; a clique with diameter 1 |
| **Forest of Paths** | Disjoint union of simple path graphs |
| **Star Graph** | One central vertex connected to all others, no other edges |
| **Pseudoforest/Pseudotree** | An otherwise-acyclic graph plus exactly one extra edge |

**Practical advice:** when a graph in a problem statement matches one of these rarer special structures, look for ways to exploit that specific structural property to speed up an otherwise-general algorithm.

---

## Summary Table — All Techniques in This Chapter

| Special Graph | Problem | General-Graph Complexity | Special-Graph Complexity |
|---|---|---|---|
| DAG | SSSP | `O((V+E) log V)` (Dijkstra's) | `O(V+E)` |
| DAG | Longest Paths | NP-complete (general graph) | `O(V+E)` |
| DAG | Counting Paths | N/A | `O(V+E)` |
| Tree | Articulation Points/Bridges | `O(V+E)` (Tarjan's) | `O(V)` (trivial: all edges are bridges) |
| Tree | SSSP | `O((V+E) log V)` / `O(VE)` | `O(V)` (unique path traversal) |
| Tree | APSP | `O(V³)` (Floyd-Warshall) | `O(V²)` (repeat SSSP `V` times) |
| Tree | Diameter | `O(V³)` | `O(V)` (double DFS/BFS trick) |
| Bipartite | Max Matching | N/A (general matching is harder) | `O(V·E)` (augmenting path) |
| Eulerian | Existence Check | N/A | `O(V+E)` (degree/connectivity check) |
| Eulerian | Find Eulerian Tour | `O(E²)` (Fleury's) | `O(E)` (Hierholzer's) |

### The Meta-Lesson

Across every special graph in this chapter, the pattern repeats: **recognizing the special structure unlocks a dramatically simpler and/or faster algorithm** than the general-graph solution. This is the single most valuable skill emphasized throughout CP4's graph chapter — graph modeling and structural recognition consistently matter more than memorizing algorithms in isolation.