# Graph Interview Patterns — LeetCode Problem Map

*A pattern-recognition guide for graph coding interviews*

The goal of this README isn't to give you 200 random problems — it's to teach you **10-12 recurring patterns**. Once you can recognize which pattern a problem is wearing as a disguise, the actual coding becomes mechanical. Interview graph questions are graph modeling questions first, and algorithm-execution questions second.


| Node Type         | Adjacency Structure                                  | Example           |
| ----------------- | ----------------------------------------------------- | ----------------- |
| `int`             | `vector<vector<int>>`                                | Course Schedule   |
| `char`            | `unordered_map<char, vector<char>>`                  | Alien Dictionary  |
| `string`          | `unordered_map<string, vector<string>>`              | Word Ladder       |
| `pair<int,int>`   | `map<pair<int,int>, vector<pair<int,int>>>`          | Coordinate Graph  |
| `string` + weight | `unordered_map<string, vector<pair<string,double>>>` | Evaluate Division |
 
---

## How to Use This

For each pattern:
1. **Recognition signals** — the phrases/constraints in a problem statement that hint at this pattern.
2. **Core technique** — which of our notes files covers the underlying algorithm.
3. **LeetCode problems** — ordered roughly easy → hard, so you can drill a pattern progressively.

---

## Table of Contents

1. [Basic DFS/BFS Traversal & Connected Components](#1-basic-dfsbfs-traversal--connected-components)
2. [Grid / Flood Fill (Implicit Graph)](#2-grid--flood-fill-implicit-graph)
3. [Multi-Source BFS](#3-multi-source-bfs)
4. [Topological Sort (Dependency Ordering)](#4-topological-sort-dependency-ordering)
5. [Cycle Detection](#5-cycle-detection)
6. [Union-Find / MST](#6-union-find--mst)
7. [Dijkstra's / Weighted Shortest Path](#7-dijkstras--weighted-shortest-path)
8. [0/1 BFS](#8-01-bfs)
9. [Bellman-Ford (Negative Weights / K-Stops)](#9-bellman-ford-negative-weights--k-stops)
10. [Floyd-Warshall / All-Pairs](#10-floyd-warshall--all-pairs)
11. [Bipartite Graph / 2-Coloring](#11-bipartite-graph--2-coloring)
12. [Strongly Connected Components & Bridges](#12-strongly-connected-components--bridges)
13. [DP on DAG (Implicit Graph Memoization)](#13-dp-on-dag-implicit-graph-memoization)
14. [MiniMax / MaxiMin / Bottleneck Path](#14-minimax--maxiMin--bottleneck-path)
15. [Eulerian Path/Circuit](#15-eulerian-pathcircuit)
16. [Tree-Specific Patterns](#16-tree-specific-patterns)
17. [Word Ladder / BFS on Implicit Word Graph](#17-word-ladder--bfs-on-implicit-word-graph)
18. [Suggested Study Order](#18-suggested-study-order)

---

## 1. Basic DFS/BFS Traversal & Connected Components

**Recognition signals:** "count islands/groups/regions," "are these connected," "clone this graph," "given `n` nodes and edges, find components."

**Core technique:** [`README_graph_traversal.md`](./README_graph_traversal.md) — Sections 2–4 (DFS, BFS, Connected Components).

| # | Problem | Notes |
|---|---|---|
| 1 | Number of Islands | Grid CC, the canonical starting point |
| 2 | Number of Provinces | CC on adjacency matrix |
| 3 | Find if Path Exists in Graph | Basic DFS/BFS/Union-Find reachability |
| 4 | Clone Graph | DFS/BFS + hashmap of visited→clone |
| 5 | Number of Connected Components in an Undirected Graph | Union-Find or DFS |
| 6 | Employee Importance | Tree-shaped DFS/BFS aggregation |
| 7 | All Paths From Source to Target | DFS backtracking on DAG |
| 8 | Keys and Rooms | DFS/BFS reachability check |
| 9 | Reorder Routes to Make All Paths Lead to the City Zero | DFS with edge-direction tracking |
| 10 | Time Needed to Inform All Employees | Tree DFS with propagation time |

---

## 2. Grid / Flood Fill (Implicit Graph)

**Recognition signals:** 2D grid, "connected region," "surrounded regions," "largest area," 4-directional or 8-directional movement.

**Core technique:** [`README_graph_traversal.md`](./README_graph_traversal.md) — Section 5 (Flood Fill).

| # | Problem | Notes |
|---|---|---|
| 1 | Flood Fill | Direct application, the template problem |
| 2 | Max Area of Island | Flood fill + size tracking |
| 3 | Island Perimeter | Flood fill variant, counts boundary edges |
| 4 | Number of Islands II | Flood fill + Union-Find (dynamic connectivity) |
| 5 | Surrounded Regions | Flood fill from border inward (reverse thinking) | this is the important pattern reverse thinkin 
-  Number of Enclaves 

| 6 | Pacific Atlantic Water Flow | Flood fill from **two** sets of sources, then intersect |
| 7 | Making A Large Island | Flood fill + component-size memoization, then try flipping each `0` |
| 8 | Count Sub Islands | Flood fill with a validity constraint |

---

## 3. Multi-Source BFS

**Recognition signals:** "nearest X from any of these sources," "distance to nearest 0/thief/exit," multiple starting points given simultaneously.

**Core technique:** [`README_sssp.md`](./README_sssp.md) — Section 2c (MSSP: enqueue all sources upfront with distance 0).

| # | Problem | Notes |
|---|---|---|
| 1 | 01 Matrix | Distance from every cell to nearest `0` — textbook MSSP |
| 2 | Rotting Oranges | All rotten oranges are sources; BFS layer = minutes elapsed |
| 3 | Walls and Gates | Distance from every empty room to nearest gate |
| 4 | As Far from Land as Possible | MSSP from all land cells, find max resulting distance |
| 5 | Shortest Distance from All Buildings | MSSP for each building, accumulate distances |
| 6 | Find the Safest Path in a Grid | MSSP (safeness) **combined with** MaxiMin (Pattern 14) — see our MST notes worked example |

---

## 4. Topological Sort (Dependency Ordering)

**Recognition signals:** "prerequisites," "must be completed before," "build order," "task scheduling with dependencies," "compilation order."

**Core technique:** [`README_topological_sort.md`](./README_topological_sort.md) — both DFS-based and Kahn's algorithm.

| # | Problem | Notes |
|---|---|---|
| 1 | Course Schedule | Cycle detection + topo feasibility (Kahn's is cleanest) |
| 2 | Course Schedule II | Same as above, but output the actual order |
| 3 | Alien Dictionary | Build edges from adjacent word comparisons, then topo sort |
| 4 | Minimum Height Trees | "Peel layers" — a BFS/Kahn's variant from tree leaves inward |
| 5 | Sequence Reconstruction | Topo sort + uniqueness check at each step |
| 6 | Parallel Courses | Kahn's algorithm, track "rounds"/layers |
| 7 | Sort Items by Groups Respecting Dependencies | Two-level topological sort (groups, then items within groups) |
| 8 | Course Schedule III | Topo sort **plus** greedy/heap scheduling — hybrid pattern |

---

## 5. Cycle Detection

**Recognition signals:** "is this valid," "detect a cycle," "will this deadlock," "redundant connection."

**Core technique:** [`README_graph_traversal.md`](./README_graph_traversal.md) — Section 7 (3-state DFS edge classification), plus Union-Find as an alternative for undirected graphs.

| # | Problem | Notes |
|---|---|---|
| 1 | Redundant Connection | Undirected cycle detection via Union-Find (find the edge that first creates a cycle) |
| 2 | Redundant Connection II | Directed version — trickier, requires handling two candidate edges |
| 3 | Course Schedule | Directed cycle detection (3-state DFS: white/gray/black) |
| 4 | Graph Valid Tree | Undirected: `E == V-1` **and** fully connected **and** no cycle |
| 5 | Find Eventual Safe States | Reverse cycle detection — find nodes that never lead into a cycle |

---

## 6. Union-Find / MST

**Recognition signals:** "minimum cost to connect all," "group/merge queries," "dynamic connectivity," "friend circles," "accounts merge."

**Core technique:** [`README_mst.md`](./README_mst.md) — full Kruskal's with Union-Find implementation.

| # | Problem | Notes |
|---|---|---|
| 1 | Number of Provinces | Union-Find as CC-counter |
| 2 | Accounts Merge | Union-Find keyed by string identity (emails) |
| 3 | Min Cost to Connect All Points | Classic MST (Kruskal's or Prim's) on a complete Manhattan-distance graph |
| 4 | Connecting Cities With Minimum Cost | Direct Kruskal's/Prim's application |
| 5 | Redundant Connection | Union-Find, first edge causing a cycle |
| 6 | Number of Operations to Make Network Connected | Count "extra" edges vs number of components needed |
| 7 | Satisfiability of Equality Equations | Union-Find with a two-pass (equal-first, then check not-equal) trick |
| 8 | Optimize Water Distribution in a Village | MST with a virtual "super-source" vertex (well cost = edge to source) |
| 9 | Swim in Rising Water | MST-flavored — "MaxiMin"-style: binary search **or** Kruskal's-with-early-stop, see Pattern 14 |
| 10 | The Earliest Moment When Everyone Become Friends | Union-Find + track when the group count reaches 1 |

---

## 7. Dijkstra's / Weighted Shortest Path

**Recognition signals:** "minimum cost/time path," positive edge weights, "cheapest," non-negative weighted edges.

**Core technique:** [`README_sssp.md`](./README_sssp.md) — Sections 4–5 (Original & Modified Dijkstra's).

| # | Problem | Notes |
|---|---|---|
| 1 | Network Delay Time | Textbook single-source Dijkstra's |
| 2 | Path With Maximum Probability | Dijkstra's variant — **multiply** probabilities instead of summing, use a max-heap |
| 3 | Cheapest Flights Within K Stops | Dijkstra's **doesn't directly apply** cleanly due to the K-stop constraint — see Pattern 9 (Bellman-Ford is the safer fit) |
| 4 | Path with Minimum Effort | Dijkstra's variant — MiniMax (minimize the maximum edge weight along the path), see Pattern 14 |
| 5 | Swim in Rising Water | Dijkstra's variant — MiniMax on a grid |
| 6 | Number of Ways to Arrive at Destination | Dijkstra's + counting paths that tie for shortest (DP layered on top) |
| 7 | Minimum Cost to Make at Least One Valid Path in a Grid | 0/1-BFS or Dijkstra's — grid where "wrong direction" costs 1 |

---

## 8. 0/1 BFS

**Recognition signals:** edge/action costs are **only** 0 or 1 (e.g., "changing direction costs 1, going straight is free"; "breaking a wall costs 1").

**Core technique:** [`README_sssp.md`](./README_sssp.md) — Section 3 (0/1-BFS with deque).

| # | Problem | Notes |
|---|---|---|
| 1 | Minimum Cost to Make at Least One Valid Path in a Grid | Following the grid's pre-drawn arrow = 0 cost; going against it = 1 cost |
| 2 | Shortest Path in a Grid with Obstacles Elimination | Adjacent pattern (state includes "obstacles removed so far") — technically BFS-on-expanded-state, but conceptually related |
| 3 | Open the Lock | Not strictly 0/1-weighted, but same deque/BFS mental model on an implicit state graph |
| 4 | 3286. Find a Safe Walk Through a Grid | very Good Problem 



---

## 9. Bellman-Ford (Negative Weights / K-Stops)

**Recognition signals:** "at most K stops/edges," "at most K transactions," negative weights possible, "K hops."

**Core technique:** [`README_sssp.md`](./README_sssp.md) — Section 7 (Bellman-Ford: relax all edges, bounded number of passes).

| # | Problem | Notes |
|---|---|---|
| 1 | Cheapest Flights Within K Stops | **The** canonical LeetCode Bellman-Ford problem — run exactly `K+1` relaxation passes, not `V-1` |
| 2 | Network Delay Time | Also solvable via Bellman-Ford (though Dijkstra's is the better fit since weights are non-negative) |

**Key interview insight:** whenever a shortest-path problem adds a **hop-count limit** ("at most K stops"), plain Dijkstra's breaks (it greedily finalizes vertices without tracking hop count) — the fix is either **bounded Bellman-Ford** (exactly `K+1` relaxation rounds) or Dijkstra's with **state expanded to `(vertex, hopsUsed)`**.

---

## 10. Floyd-Warshall / All-Pairs

**Recognition signals:** small `V` (`≤ 400` or so), "for every pair," "find the city with the fewest reachable neighbors," repeated shortest-path queries.

**Core technique:** [`README_apsp.md`](./README_apsp.md) — full Floyd-Warshall + applications.

| # | Problem | Notes |
|---|---|---|
| 1 | Find the City With the Smallest Number of Neighbors at a Threshold Distance | Direct Floyd-Warshall, then scan rows |
| 2 | Course Schedule IV (Prerequisite queries) | Floyd-Warshall-style transitive closure (boolean version — Warshall's algorithm) |
| 3 | Evaluate Division | Floyd-Warshall-style all-pairs on a **weighted** graph where "weight" = ratio (multiply instead of add along paths) |

---

## 11. Bipartite Graph / 2-Coloring

**Recognition signals:** "can this be split into two groups," "no two adjacent/conflicting," "possible bipartition," "dislike pairs."

**Core technique:** [`README_graph_traversal.md`](./README_graph_traversal.md) — Section 6 (Bipartite Check via modified BFS).

| # | Problem | Notes |
|---|---|---|
| 1 | Is Graph Bipartite? | Direct 2-coloring BFS/DFS |
| 2 | Possible Bipartition | Same pattern, "dislike" edges instead of raw adjacency |
| 3 | Flower Planting With No Adjacent | Greedy coloring — related family, not strictly bipartite but same "coloring" mental model |

---

## 12. Strongly Connected Components & Bridges

**Recognition signals:** "critical connections," "single point of failure," directed graph + "mutually reachable," "network resilience."

**Core technique:** [`README_graph_traversal.md`](./README_graph_traversal.md) — Sections 8–9 (Articulation Points/Bridges, Kosaraju's/Tarjan's SCC).

| # | Problem | Notes |
|---|---|---|
| 1 | Critical Connections in a Network | Direct application of the `dfsNum`/`dfsLow` bridge-finding algorithm |
| 2 | Number of Provinces | (Simpler CC version, listed here for contrast with SCC) |

**Note:** LeetCode has relatively few pure SCC problems (Tarjan's/Kosaraju's) — it's more commonly tested at the "articulation points/bridges" level, or folded into harder graph-modeling problems.

---

## 13. DP on DAG (Implicit Graph Memoization)

**Recognition signals:** "longest increasing path," "count the number of ways," memoized recursion where states form a natural dependency order (no cycles).

**Core technique:** [`README_special_graphs.md`](./README_special_graphs.md) — Section 2 (DAG: SSSP/Longest Paths/Counting Paths).

| # | Problem | Notes |
|---|---|---|
| 1 | Longest Increasing Path in a Matrix | Grid as implicit DAG (edges only go to strictly-larger neighbors); DP = longest path on DAG |
| 2 | Course Schedule III | Ordering + greedy, related to DAG scheduling |
| 3 | Unique Paths III | Backtracking on implicit grid-DAG with a "visit every cell" constraint |
| 4 | Out of Boundary Paths | Counting paths in an implicit DAG (with a step-budget dimension), same idea as our Counting-Paths section |
| 5 | Cherry Pickup | Two-agent DP that's structurally longest-path-on-DAG with expanded state |

---

## 14. MiniMax / MaxiMin / Bottleneck Path

**Recognition signals:** "minimize the maximum," "maximize the minimum," "safest path," "path with least effort," "widest path."

**Core technique:** [`README_mst.md`](./README_mst.md) — Section 8 (both the MST-based method and the Dijkstra-variant/"widest path" method).

| # | Problem | Notes |
|---|---|---|
| 1 | Path With Minimum Effort | MiniMax — minimize the max absolute height difference along the path |
| 2 | Swim in Rising Water | MiniMax on a grid — minimize the max "elevation" you must cross |
| 3 | Find the Safest Path in a Grid | MaxiMin — maximize the min "safeness"; combines with Multi-Source BFS (Pattern 3) |
| 4 | Path with Maximum Probability | A "MaxiProduct" variant — same modified-Dijkstra's shape, but multiplying instead of taking min/max |

**Key interview insight:** the instant you see "minimize the worst edge" or "maximize the weakest link" language, reach for the **modified Dijkstra's** template: propagate a running bottleneck value instead of a sum, flip the heap direction, flip the relaxation comparison.

---

## 15. Eulerian Path/Circuit

**Recognition signals:** "use every ticket/flight/domino exactly once," "reconstruct the itinerary," "visit every edge."

**Core technique:** [`README_special_graphs.md`](./README_special_graphs.md) — Section 5 (Hierholzer's Algorithm).

| # | Problem | Notes |
|---|---|---|
| 1 | Reconstruct Itinerary | The canonical Eulerian-path LeetCode problem — Hierholzer's algorithm, with lexicographic tie-breaking |
| 2 | Valid Arrangement of Pairs | Directed Eulerian path existence + construction |

---

## 16. Tree-Specific Patterns

**Recognition signals:** input is explicitly a tree (`n` nodes, `n-1` edges), "diameter," "unique path between any two nodes."

**Core technique:** [`README_special_graphs.md`](./README_special_graphs.md) — Section 3 (Tree: traversal, SSSP/APSP shortcuts, diameter via double-BFS).

| # | Problem | Notes |
|---|---|---|
| 1 | Diameter of Binary Tree | Simple recursive version (DFS height) |
| 2 | Diameter of N-Ary Tree | Same recursive idea, generalized |
| 3 | Tree Diameter (general weighted tree) | The **double-BFS/DFS** trick from our Special Graphs notes |
| 4 | Minimum Height Trees | Related to diameter — the center(s) of the diameter path are the answer |
| 5 | Sum of Distances in Tree | Rerooting technique — DFS twice (once down, once "rerooting" up) |
| 6 | Binary Tree Maximum Path Sum | DFS returning "best downward path," tracked globally |

---

## 17. Word Ladder / BFS on Implicit Word Graph

**Recognition signals:** "transform word A to word B one letter at a time," "each intermediate step must be a valid word."

**Core technique:** [`README_graph_traversal.md`](./README_graph_traversal.md) (BFS fundamentals) applied to an **implicit** graph where vertices are words and edges are one-letter transformations.

| # | Problem | Notes |
|---|---|---|
| 1 | Word Ladder | Plain BFS — shortest transformation sequence length |
| 2 | Word Ladder II | BFS to find shortest length, **then** DFS/backtrack to reconstruct all shortest paths |
| 3 | Minimum Genetic Mutation | Structurally identical to Word Ladder, different alphabet/domain |

---

## 18. Suggested Study Order

If you're prepping systematically, tackle patterns in this order — each builds on skills from the previous:

1. **Basic DFS/BFS Traversal** and **Grid/Flood Fill** — build fluency with the core traversal loop and visited-tracking before anything else.
2. **Multi-Source BFS** — a one-line tweak on plain BFS (push all sources upfront), but a very common "aha" moment in interviews.
3. **Cycle Detection** and **Topological Sort** — these two are tightly linked (Kahn's algorithm essentially *is* a cycle-detection-capable topo sort).
4. **Union-Find / MST** — a completely different toolkit (no priority queue needed), but reused constantly for connectivity-style problems.
5. **Dijkstra's** — once comfortable with a priority-queue-based greedy relaxation loop, most "weighted shortest path" interview questions become templated.
6. **0/1 BFS** and **Bellman-Ford** — natural extensions of Dijkstra's for edge cases (only 0/1 weights; hop-count limits or negative weights).
7. **MiniMax/MaxiMin** — recognize this as "Dijkstra's, but replace `+` with `min`/`max`" — a very common "twist" interviewers add to a base Dijkstra's question.
8. **Floyd-Warshall** — only needed when you spot small `V` + "all pairs" — otherwise this is rarely the right tool in an interview setting (too slow for large inputs).
9. **Bipartite Check**, **SCC/Bridges**, **DP-on-DAG**, **Eulerian Path**, **Tree-specific tricks** — more specialized; recognize the trigger phrases above, but these appear less frequently than patterns 1–7.

---

## Cross-Reference — Notes in This Collection

| Pattern | Full Explanation |
|---|---|
| Traversal, Flood Fill, Multi-Source BFS, Bipartite, Cycle Check, SCC/Bridges | [`README_graph_traversal.md`](./README_graph_traversal.md) |
| Topological Sort, Kahn's Algorithm | [`README_topological_sort.md`](./README_topological_sort.md) |
| Union-Find, Kruskal's, Prim's, MiniMax/MaxiMin (both methods) | [`README_mst.md`](./README_mst.md) |
| BFS/0-1-BFS/Dijkstra's/Bellman-Ford/SPFA | [`README_sssp.md`](./README_sssp.md) |
| Floyd-Warshall, Transitive Closure, All-Pairs | [`README_apsp.md`](./README_apsp.md) |
| DAG-as-DP, Tree shortcuts, Eulerian Path (Hierholzer's) | [`README_special_graphs.md`](./README_special_graphs.md) |