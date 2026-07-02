# All-Pairs Shortest Paths (APSP) — Floyd-Warshall Algorithm


---

## Table of Contents

1. [Overview and Motivation](#1-overview-and-motivation)
2. [The Floyd-Warshall Algorithm](#2-the-floyd-warshall-algorithm)
3. [Why Floyd-Warshall Works — The DP Explanation](#3-why-floyd-warshall-works--the-dp-explanation)
4. [Worked Example — Step by Step](#4-worked-example--step-by-step)
5. [Space Optimization](#5-space-optimization)
6. [Other Applications of Floyd-Warshall](#6-other-applications-of-floyd-warshall)
7. [Shortest Paths Algorithm Decision Table](#7-shortest-paths-algorithm-decision-table)
8. [Summary](#8-summary)

---

## 1. Overview and Motivation

### The Problem

**All-Pairs Shortest Paths (APSP):** find the shortest path distance between **every pair** of vertices `(i, j)` in a graph — not just from one source.

### Motivating Example — UVa 11463 (Commandos)

> Given a connected weighted graph with `V ≈ 100` and two vertices `s` and `d`, find the maximum value of `dist[s][i] + dist[i][d]` over all possible intermediate vertices `i`.

This requires knowing shortest-path distances from **every vertex** to **every other vertex** — a full APSP computation, not just a single SSSP.

### Naive Approach: Run SSSP V Times

Since Dijkstra's algorithm computes SSSP from one source in `O((V+E) log V)`, running it once per vertex gives:

$$V \times O((V+E)\log V) = O(V^3 \log V) \text{ if } E = O(V^2)$$

This works, but requires implementing Dijkstra's + looping it `V` times.

### The Alternative: Floyd-Warshall

If `V ≈ 450` or smaller, there's a **much shorter to code** algorithm:

```cpp
// precondition: AM[i][j] contains the weight of edge (i, j)
// or INF if there is no such edge
for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
```

When this terminates, `AM[i][j]` holds the shortest path distance between every pair `(i, j)`.

**This is the entire algorithm — just 4 lines.** It's called **Floyd-Warshall**, invented independently by **Robert W. Floyd** and **Stephen Warshall**.

### Complexity Comparison

| Approach | Complexity (with `E = O(V²)`) |
|---|---|
| `V` calls of Dijkstra's `O((V+E) log V)` | `O(V³ log V)` |
| `V` calls of Bellman-Ford `O(V·E)` | `O(V⁴)` |
| **Floyd-Warshall** | **`O(V³)`** |

Floyd-Warshall is a **Dynamic Programming** algorithm with 3 nested loops, so it clearly runs in `O(V³)`. Because of the cubic complexity, it's only practical for **small graphs (V ≈ 450)** in a contest setting (assuming a ~1 second time limit and ~100M operations budget).

**Key attractiveness in contests:** implementation speed. Four short lines beat writing a full Dijkstra's implementation, especially under time pressure — **if the graph is small enough.**

---

## 2. The Floyd-Warshall Algorithm

### Requirements

- The graph **must** be stored as an **Adjacency Matrix** (not an adjacency list), so that `AM[i][j]` — the weight of edge `(i,j)` — can be accessed and modified in `O(1)`.
- Initialize `AM[i][j] = weight(i,j)` if an edge exists, or `INF` (typically `1e9`) if it doesn't. Also `AM[i][i] = 0` normally (distance from a vertex to itself).

### Code

```cpp
#include <vector>
using namespace std;

void floydWarshall(vector<vector<int>>& AM, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
}
```

### Initialization Example

```cpp
const int INF = 1e9;
int V = 5;
vector<vector<int>> AM(V, vector<int>(V, INF));

for (int i = 0; i < V; i++)
    AM[i][i] = 0;              // distance to self = 0

// then set AM[u][v] = weight for each given edge (u, v)
```

**Why `INF = 1e9` and not `INT_MAX (2³¹ - 1)`?**
If you used `INT_MAX`, then `AM[i][k] + AM[k][j]` could **overflow** (two `INT_MAX` values added together wrap around to a negative number), silently corrupting the algorithm. Using a smaller sentinel like `1e9` ("1 billion") leaves enough headroom that summing two such values (`2e9`) still fits safely within a 32-bit signed integer's range (~2.1 billion), avoiding overflow.

---

## 3. Why Floyd-Warshall Works — The DP Explanation

### The Core Idea

Floyd-Warshall gradually **allows more intermediate vertices** to be used when forming a path from `i` to `j`.

**Definition:** let `sp(i, j, k)` = the shortest path distance from `i` to `j`, using **only vertices `[0..k]`** as allowed intermediate stops.

- **Base case (`k = -1`):** no intermediate vertices allowed at all — only the direct edge counts.
  $$sp(i, j, -1) = \text{weight}(i, j)$$
- **Recurrence:** once we "unlock" vertex `k` as a usable intermediate stop, there are exactly two possibilities for the best path from `i` to `j`:
  1. **Don't use vertex `k`** at all → the best path is whatever it already was: `sp(i, j, k-1)`.
  2. **Do use vertex `k`** as a waypoint → go from `i` to `k`, then `k` to `j`, using only vertices `[0..k-1]` for each leg: `sp(i, k, k-1) + sp(k, j, k-1)`.

$$sp(i,j,k) = \min\big(sp(i,j,k-1),\ sp(i,k,k-1) + sp(k,j,k-1)\big)$$

We compute this for **increasing `k`**, from `k = 0` up to `k = V-1`. By the time `k = V-1`, **all** vertices have been allowed as intermediates, so `sp(i,j,V-1)` is the true shortest path.

### Walking Through the Book's Example

Goal: find `sp(3, 4, 4)` — shortest path from vertex 3 to vertex 4, allowing any of the 5 vertices `{0,1,2,3,4}` as intermediates. Final answer: **3**, via path `3 → 0 → 2 → 4`.

**`k = -1` (direct edges only):**
- `sp(3,4,-1) = 5` (direct edge weight)
- `sp(3,2,-1) = 3`
- `sp(2,4,-1) = 1`
- Note: `sp(3,2,-1) + sp(2,4,-1) = 3 + 1 = 4`, which is still `> 3` — not yet the answer.

**`k = 0` (vertex 0 unlocked as intermediate):**
- `sp(3,4,0) = sp(3,0,-1) + sp(0,4,-1) = 1 + 3 = 4` (improved from 5)
- `sp(3,2,0)` also drops: `sp(3,0,-1) + sp(0,2,-1) = 1 + 1 = 2` (improved from 3)
- `sp(3,1,0)` changes from `∞` down to `3`.

**`k = 1` (vertex 1 also unlocked):**
- No change to `sp(3,2,1)`, `sp(2,4,1)`, or `sp(3,4,1)`.
- Two *other* values change (`sp(0,3,1)`, `sp(2,3,1)`) but these don't affect the `3→4` computation.

**`k = 2` (vertex 2 also unlocked):**
- `sp(3,4,2) = sp(3,2,2) + sp(2,4,2) = 2 + 1 = 3` — **this is the improvement we were waiting for!**

**`k = 3, k = 4`:** `sp(3,4,4)` remains `3` — this is the final, correct answer.

### Formal DP Recurrence

$$D^{-1}_{i,j} = \text{weight}(i,j) \quad \text{(base case)}$$

$$D^{k}_{i,j} = \min\big(D^{k-1}_{i,j},\ D^{k-1}_{i,k} + D^{k-1}_{k,j}\big) \quad \text{for } k \ge 0$$

This must be filled **layer by layer**, in order of increasing `k`, since layer `k` depends entirely on layer `k-1`.

**Example calculation:** to compute `D²₃,₄` (row 3, column 4, at layer `k=2`), look at the minimum of `D¹₃,₄` (not using vertex 2) or `D¹₃,₂ + D¹₂,₄` (routing through vertex 2).

---

## 4. Worked Example — Step by Step

### The Graph

5 vertices `{0,1,2,3,4}`. Direct edges (from the figures in the book):

```
0 → 1 (2)      0 → 3 (6)      2 → 0 (1)
2 → 1 (1)      2 → 4 (1)      3 → 0 (1)
3 → 1 (3)      3 → 2 (3)      3 → 4 (5)
1 → 4 (4)
```

(Exact edge set reconstructed from the described adjacency matrix snapshots — the key relationships that matter for the traced example are `3→0=1`, `0→2=1`, `3→2=3`, `2→4=1`, giving the final shortest path `3→0→2→4 = 1+1+1 = 3`.)

### Initial Adjacency Matrix (`k = -1`, direct edges only)

| | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| **0** | 0 | 2 | 1 | ∞ | 3 |
| **1** | ∞ | 0 | ∞ | 4 | ∞ |
| **2** | ∞ | 1 | 0 | ∞ | 1 |
| **3** | 1 | ∞ | 3 | 0 | 5 |
| **4** | ∞ | ∞ | ∞ | ∞ | 0 |

### After `k = 0` (vertex 0 allowed as intermediate)

| | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| **0** | 0 | 2 | 1 | ∞ | 3 |
| **1** | ∞ | 0 | ∞ | 4 | ∞ |
| **2** | ∞ | 1 | 0 | ∞ | 1 |
| **3** | 1 | **3** | **2** | 0 | **4** |
| **4** | ∞ | ∞ | ∞ | ∞ | 0 |

Changes in row 3: `sp(3,1,0)=3` (via `3→0→1`), `sp(3,2,0)=2` (via `3→0→2`), `sp(3,4,0)=4` (via `3→0→4`).

### After `k = 1` (vertex 1 also allowed)

| | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| **0** | 0 | 2 | 1 | **6** | 3 |
| **1** | ∞ | 0 | ∞ | 4 | ∞ |
| **2** | ∞ | 1 | 0 | **5** | 1 |
| **3** | 1 | 3 | 2 | 0 | 4 |
| **4** | ∞ | ∞ | ∞ | ∞ | 0 |

`sp(0,3,1) = 6` (via `0→1→3`), `sp(2,3,1) = 5` (via `2→1→3`) — neither affects the `3→4` path we care about.

### After `k = 2` (vertex 2 also allowed)

| | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| **0** | 0 | 2 | 1 | 6 | **2** |
| **1** | ∞ | 0 | ∞ | 4 | ∞ |
| **2** | ∞ | 1 | 0 | 5 | 1 |
| **3** | 1 | 3 | 2 | 0 | **3** |
| **4** | ∞ | ∞ | ∞ | ∞ | 0 |

`sp(0,4,2) = 2` (via `0→2→4`), and crucially: `sp(3,4,2) = sp(3,2,2) + sp(2,4,2) = 2 + 1 = 3`. ✅ This is the final shortest distance.

### After `k = 3, k = 4`

No further improvement to `sp(3,4)` — it stabilizes at **3**, confirming the shortest path `3 → 0 → 2 → 4` with total cost `1 + 1 + 1 = 3`.

---

## 5. Space Optimization

### The Naive 3D Approach

A literal translation of the DP recurrence would use a **3-dimensional** array `D[k][i][j]` of size `O(V³)` — one full `V×V` matrix per layer `k`.

### The Optimization

To compute layer `k`, we only ever need the values from layer `k-1`. So we can **drop the `k` dimension entirely** and just update `D[i][j]` "on the fly," reusing the same 2D matrix.

**This works because of a subtle but important detail:** when computing `AM[i][k] + AM[k][j]` during iteration `k`, both `AM[i][k]` and `AM[k][j]` are values that involve vertex `k` itself as an endpoint — and it can be shown that these specific values **don't change during iteration `k`** (i.e., `AM[i][k]` at layer `k` equals `AM[i][k]` at layer `k-1`, since routing `i → k` through `k` itself doesn't create a shorter path). This means it's safe to update the matrix in place without a separate array.

**Result:** Floyd-Warshall only needs **`O(V²)` space**, even though it still runs in `O(V³)` time.

```cpp
// same code as before — already uses O(V^2) space implicitly
for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
```

---

## 6. Other Applications of Floyd-Warshall

Floyd-Warshall's main purpose is APSP, but its `O(V³)` reliability (fixed complexity regardless of graph structure) makes it useful for several other classic problems — **as long as the graph is small**.

### 6a. Solving SSSP on a Small Graph

If you have full APSP information, you automatically have SSSP information from *any* source for free. For small graphs (`V ≲ 450`), it can be **faster to code** to just run the 4-line Floyd-Warshall rather than implement BFS (unweighted) or Dijkstra's/Bellman-Ford (weighted) — even if you only need a single-source answer.

### 6b. Printing the Shortest Paths

Unlike BFS/Dijkstra's/Bellman-Ford (which use a simple 1D parent array), Floyd-Warshall needs a **2D parent matrix** `p[i][j]`, where `p[i][j]` = the last vertex visited before reaching `j` on the shortest path from `i`.

```cpp
#include <vector>
#include <cstdio>
using namespace std;

void floydWarshallWithPath(vector<vector<int>>& AM, vector<vector<int>>& parent, int V) {
    // initialization: p[i][j] = i means "path from i to j currently just starts at i"
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            parent[i][j] = i;

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (AM[i][k] + AM[k][j] < AM[i][j]) {
                    AM[i][j] = AM[i][k] + AM[k][j];
                    parent[i][j] = parent[k][j];   // path now routes through k
                }
}

void printPath(vector<vector<int>>& parent, int i, int j) {
    if (i != j) printPath(parent, i, parent[i][j]);
    printf(" %d", j);
}
```

**Usage:** call `printPath(parent, source, destination)` to print the full path.

### 6c. Transitive Closure — Warshall's Algorithm

**Problem:** given a graph, determine for every pair `(i, j)` whether `j` is reachable from `i`, directly **or indirectly**.

This is a **boolean** variant using bitwise operators (faster than arithmetic):

- `AM[i][j] = 1` (true) if there's a direct edge `i → j`, else `0`.

```cpp
void transitiveClosure(vector<vector<bool>>& AM, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                AM[i][j] = AM[i][j] || (AM[i][k] && AM[k][j]);
}
```

After running, `AM[i][j]` tells you whether `i` can reach `j` at all, via any path (direct or indirect). Complexity: `O(V³)`.

### 6d. MiniMax and MaxiMin Paths

**MiniMax path problem:** find the path between two vertices that **minimizes the maximum edge weight** along the path (useful for e.g. "minimize the worst bottleneck").

```cpp
void miniMax(vector<vector<int>>& AM, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                AM[i][j] = min(AM[i][j], max(AM[i][k], AM[k][j]));
}
```

For the **MaxiMin** variant (maximize the minimum edge weight along the path), simply swap `min`/`max`:

```cpp
void maxiMin(vector<vector<int>>& AM, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                AM[i][j] = max(AM[i][j], min(AM[i][k], AM[k][j]));
}
```

Only practical for `V ≲ 450` due to `O(V³)` complexity.

### 6e. Finding Cycles (Including Negative Cycles) and the Graph's Girth

Floyd-Warshall's fixed `O(V³)` runtime — regardless of what kind of graph is fed in — makes it usable for **cycle detection**, similar to how Bellman-Ford can detect negative cycles in `O(V·E)`.

**Setup:** initialize the main diagonal `AM[i][i] = INF` (not `0`!) before running Floyd-Warshall.

**After running:** `AM[i][i]` now represents the shortest **cyclic path** starting and ending at vertex `i`, using up to `V-1` intermediate vertices.

**Interpretation:**
- If `AM[i][i]` is still `INF` for a given `i` → no cycle passes through `i`.
- If `AM[i][i]` is a **finite non-negative** value → a cycle exists through `i`, and this value is the cost of the cheapest such cycle.
- The overall **cheapest cycle in the graph** (its "girth") is `min(AM[i][i])` over all `i`, considering only non-negative results.
- If `AM[i][i] < 0` for any `i` → **negative cycle detected.** (Because if a "shortest cyclic path" back to itself is negative, traversing it again would make the path even shorter — a contradiction, confirming a true negative cycle.)

### 6f. Finding the Diameter of a Graph

**Diameter:** the *maximum* shortest-path distance between any pair of vertices in the graph.

**Approach:**
1. Run Floyd-Warshall once — `O(V³)` — to get full APSP data in `AM`.
2. Scan all `AM[i][j]` entries for the maximum finite value — `O(V²)`.

```cpp
int findDiameter(vector<vector<int>>& AM, int V) {
    int diameter = 0;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (AM[i][j] != INF)
                diameter = max(diameter, AM[i][j]);
    return diameter;
}
```

Referenced problem: **UVa 01056 — Degrees of Separation** (ICPC World Finals 2006). Only feasible for small graphs (`V ≲ 450`).

### 6g. Finding SCCs (Strongly Connected Components) of a Small Graph

Tarjan's algorithm finds SCCs in `O(V+E)`, but the code is relatively long. For **small graphs**, an alternative:

1. Run Warshall's transitive closure algorithm — `O(V³)` — to get `AM[i][j]` = "is `j` reachable from `i`?" for every pair.
2. Two vertices `i` and `j` belong to the **same SCC** if and only if `AM[i][j] && AM[j][i]` is true (mutually reachable).

```cpp
// after running transitiveClosure(AM, V):
bool sameSCC(vector<vector<bool>>& AM, int i, int j) {
    return AM[i][j] && AM[j][i];
}
```

Referenced problems: UVa 00247 (Calling Circles), UVa 01229 (Sub-dictionary), UVa 10731 (Test).

### 6h. Arbitrage Detection (Finding a Profitable Cycle)

A classic real-world-flavored application: given currency conversion rates, detect if there's a sequence of trades that yields a net profit (a "profitable cycle").

This maps directly onto the **cycle-finding** technique above (Section 6e) — a profitable arbitrage loop corresponds to detecting a favorable cycle using Floyd-Warshall (often after taking logarithms to convert multiplicative rates into additive weights, turning "maximize product of rates" into "find negative-weight cycle" in log-space).

Referenced problem: UVa 00436 — Arbitrage (II).

---

## 7. Shortest Paths Algorithm Decision Table

| Graph Criteria | BFS `O(V+E)` | Dijkstra's `O((V+E) log V)` | Bellman-Ford `O(V·E)` | Floyd-Warshall `O(V³)` |
|---|---|---|---|---|
| **Max feasible size** | `V+E ≈ 100M` | `V+E ≈ 1M` | `V·E ≈ 100M` | `V ≈ 450` |
| **Unweighted graph** | **Best** | Ok | Bad | Bad in general |
| **Weighted graph** | **WA** (wrong answer) | **Best** | Ok | Bad in general |
| **Negative weight (no cycle)** | WA | Modified version: Ok | Ok | Bad in general |
| **Negative cycle detection** | Cannot detect | Cannot detect | **Can detect** | **Can detect** |
| **Small graph (`V ≈ 450`)** | WA if weighted | Overkill | Overkill | **Best** |

*(Assumption: ~100M operations feasible in ≤1 second, single test case.)*

**Key takeaways from the table:**
- For **unweighted** graphs, BFS is unbeatable — don't reach for anything heavier.
- For **weighted, non-negative** graphs, Dijkstra's is the standard best choice.
- The **moment negative weights appear**, Original Dijkstra's gives wrong answers — switch to Modified Dijkstra's or Bellman-Ford/SPFA.
- Only Bellman-Ford and Floyd-Warshall can **detect negative cycles**.
- For **small graphs**, Floyd-Warshall's simplicity (4 lines) makes it the best choice **even for problems that are technically just SSSP** — the coding-time savings outweigh the complexity cost when `V` is small enough.

### Why Floyd-Warshall Shows Up in Contests Despite High Complexity

Two reasons:

1. **Obvious reason:** the problem genuinely needs shortest paths between *many* (or all) pairs of vertices, not just from a single source — this is inherently what Floyd-Warshall/APSP solves.

2. **Less obvious reason:** shortest paths is often just a **sub-problem** inside a larger, more complex problem. Problem authors deliberately keep `V` small (e.g., `V ≈ 450`) specifically so that competitors can use the simple 4-line Floyd-Warshall as a quick sub-routine, rather than needing a full Dijkstra's implementation, freeing up contest time for the harder parts of the problem.

Referenced problems: UVa 10171, UVa 10793, UVa 11463, Kattis - transportationplanning.

---

## 8. Summary

### The Algorithm

```cpp
#include <vector>
using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& AM, int V) {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
}
```

### Key Facts

| Property | Value |
|---|---|
| Time complexity | `O(V³)` |
| Space complexity | `O(V²)` (after dropping the `k` dimension) |
| Required graph representation | Adjacency Matrix |
| Handles negative edges? | ✅ Yes |
| Handles negative cycles? | ✅ Can detect them (diagonal check) |
| Best use case | Small graphs (`V ≲ 450`), or when APSP (not just SSSP) is genuinely needed |

### Applications Beyond APSP

| Application | Technique |
|---|---|
| SSSP on small graph | Just read off row `AM[source][*]` |
| Print shortest paths | 2D parent matrix `p[i][j]`, recursive printing |
| Transitive closure | Boolean version with `\|` and `&&` (Warshall's algorithm) |
| MiniMax / MaxiMin path | Replace `+` with `max`/`min` in the relaxation step |
| Cycle / negative cycle detection | Set diagonal to `INF`, check `AM[i][i]` after running |
| Graph diameter | Max value in the fully-processed `AM` matrix |
| Small-graph SCC detection | `AM[i][j] && AM[j][i]` via transitive closure |
| Arbitrage / profitable cycle detection | Cycle-finding technique in log-transformed rate graph |

### Rule of Thumb

> **If `V ≲ 450`, and the problem needs shortest paths info (from one source, many sources, or all pairs), just use Floyd-Warshall.** The `O(V³)` cost is acceptable at this scale, and the implementation is dramatically shorter than any alternative.

> **If `V` is larger, or the graph is sparse (`E ≪ V²`), fall back to BFS / Dijkstra's / Bellman-Ford depending on edge weight properties (see Section 9 of the SSSP notes / Table 4.4 above).**