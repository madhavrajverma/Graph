# SSSP on Weighted Graphs — Dijkstra's & Bellman-Ford

---

## 1. Why BFS Fails on Weighted Graphs

BFS assumes every edge costs the same, so "fewest edges" = "cheapest." On a **weighted graph**, this breaks: a path with more edges can still have less total weight than a path with fewer edges.

**Example:** shortest path from vertex 0 to vertex 3 is **not** the direct edge `0 → 3` (weight 7), but the detour `0 → 1 → 3` with total weight `2 + 3 = 5`.

This is why we need **Dijkstra's algorithm** for graphs with non-negative edge weights.

---

## 2. Dijkstra's Algorithm — Original Version

### Core Idea

- `dist[s] = 0`, `dist[u] = ∞` for all other vertices.
- Maintain a **sorted set** of `(dist[u], u)` pairs, ordered by non-decreasing distance.
- Insert all `V` vertices upfront — `O(V log V)`.
- Repeatedly:
  1. Pop the pair with smallest `dist[u]` — this vertex is now finalized.
  2. **Relax** every neighbor `v` of `u`: `dist[v] = min(dist[v], dist[u] + weight(u,v))`.
  3. If improved, update that vertex's position in the set.

### The Implementation Detail

Standard binary-heap priority queues (`std::priority_queue`, Java `PriorityQueue`, Python `heapq`) have **no decrease-key** operation — you can't update a key after inserting it.

**Workaround:** use `std::set<pair<int,int>>` (a balanced BST) instead. "Updating" a value means:
1. **Erase** the old `(dist[v], v)` pair — `O(log V)`.
2. **Insert** the new, lower pair — `O(log V)`.

### Code

```cpp
#include <vector>
#include <set>
using namespace std;

vector<int> dijkstraOriginal(int V, vector<vector<pair<int,int>>>& adj, int source) {
    const int INF = 1e9;
    vector<int> dist(V, INF);
    dist[source] = 0;

    set<pair<int,int>> pq;                     // (distance, vertex)
    for (int u = 0; u < V; u++)
        pq.insert({dist[u], u});

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());

        for (auto& [v, w] : adj[u]) {
            if (dist[u] + w >= dist[v]) continue;   // not an improvement
            pq.erase({dist[v], v});                 // remove stale entry
            dist[v] = dist[u] + w;                  // relax
            pq.insert({dist[v], v});                // insert updated entry
        }
    }
    return dist;
}
```

`adj[u]` holds `(neighbor, weight)` pairs — a standard weighted adjacency list.

### Step-by-Step Example

Graph: `0→1 (2)`, `0→2 (6)`, `0→3 (7)`, `1→3 (3)`, `1→4 (6)`, `2→4 (1)`, `3→4 (5)`. Source `s = 0`.

| Step | Popped `(d,u)` | Action | Set after |
|---|---|---|---|
| 1 | init | `dist[0]=0`, rest `∞` | `{(0,0),(∞,1),(∞,2),(∞,3),(∞,4)}` |
| 2 | `(0,0)` | relax → `dist[1]=2, dist[2]=6, dist[3]=7` | `{(2,1),(6,2),(7,3),(∞,4)}` |
| 3 | `(2,1)` | relax → `dist[3]=min(7,2+3)=5`, `dist[4]=8` | `{(5,3),(6,2),(8,4)}` — edge `0→3` no longer on shortest-path tree |
| 4 | `(5,3)` | try `5+5=10` vs `dist[4]=8` → no improvement | `{(6,2),(8,4)}` — edge `3→4` not on tree |
| 5 | `(6,2)` | relax → `dist[4]=min(8,6+1)=7` | `{(7,4)}` — edge `1→4` not on tree |
| 6 | `(7,4)` | nothing left to relax | `{}` — done |

**Final:** `dist = [0, 2, 6, 5, 7]`, shortest-path tree edges: `0→1`, `0→2`, `1→3`, `2→4`.

### Complexity

`O((V + E) log V)`
- `V` vertices enqueued/dequeued once each.
- At most `E` distance updates, each an `O(log V)` set operation.
- (Note: `O(log E) = O(log V²) = O(2·log V) = O(log V)`, so bounding by `V` or `E` doesn't matter.)

---

## 3. Dijkstra's Algorithm — Modified Version

### Why a Modified Version?

For those using a standard heap-based priority queue with no decrease-key support (e.g. Python's `heapq`, or if you'd rather avoid `std::set`).

### Core Idea — Lazy Deletion

Dijkstra's only ever **lowers** `dist[u]`, never raises it. Exploit this one-directional property:

- Start the priority queue with just `(0, source)`.
- Every successful relaxation **pushes a new pair** `(newDist, v)` — the older, inferior pair already in the queue is **left alone**, not removed.
- When popping `(d, u)`: **if `d > dist[u]`, this entry is stale — skip it.** Otherwise process `u` normally.

This means the same vertex can have multiple copies sitting in the queue, but only the one matching the true `dist[u]` ever gets processed — the rest are filtered out lazily.

### Code

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<int> dijkstraModified(int V, vector<vector<pair<int,int>>>& adj, int source) {
    const int INF = 1e9;
    vector<int> dist(V, INF);
    dist[source] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;              // stale entry, skip

        for (auto& [v, w] : adj[u]) {
            if (dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
    return dist;
}
```

### Step-by-Step Example (same graph)

| Step | Popped `(d,u)` | Action | Heap after |
|---|---|---|---|
| 1 | init | `dist[0]=0` | `{(0,0)}` |
| 2 | `(0,0)` | relax → `dist[1]=2, dist[2]=6, dist[3]=7` | `{(2,1),(6,2),(7,3)}` |
| 3 | `(2,1)` | relax → `dist[3]=5, dist[4]=8` | `{(5,3),(6,2),(7,3),(8,4)}` — 2 copies of vertex 3 |
| 4 | `(5,3)` | `5+5=10` vs `dist[4]=8` → no improvement | `{(6,2),(7,3),(8,4)}` |
| 5 | `(6,2)` | relax → `dist[4]=7` | `{(7,3),(7,4),(8,4)}` — 2 copies of vertex 4 |
| 6 | `(7,3)` | **stale** (`7 > dist[3]=5`) → skip (actual deletion happens here) | `{(7,4),(8,4)}` |
| 6b | `(7,4)` | process normally, nothing changes | `{(8,4)}` |
| 6c | `(8,4)` | **stale** (`8 > dist[4]=7`) → skip | `{}` — done |

Same final result: `dist = [0, 2, 6, 5, 7]`.

### Complexity

Still `O((V + E) log V)` on non-negative weighted graphs:
- Each vertex is processed exactly once (when its true minimal distance is popped).
- The queue may temporarily hold up to `O(E)` stale items, but since `log E = O(log V)`, each push/pop is still `O(log V)`.

---

## 4. Original vs. Modified Dijkstra's — Comparison

| Aspect | Original (`set`) | Modified (`priority_queue`) |
|---|---|---|
| Data structure | Balanced BST | Binary heap |
| Initial queue size | All `V` vertices | Just `1` (source) |
| Update mechanism | Erase old pair + insert new | Lazy deletion (push new, ignore stale on pop) |
| Duplicate entries? | Never | Yes — multiple stale copies possible |
| Complexity (non-negative weights) | `O((V+E) log V)` | `O((V+E) log V)` |
| Python compatibility | No built-in balanced BST | Works fine with `heapq` |
| Behavior on negative edges | **Undefined behavior** (erasing an already-removed pair) | **Works correctly**, just slower |

---

## 5. SSSP Variants — Applicability to Weighted Graphs

All the unweighted-graph variants (Section 4.4.2) still apply here:

| Variant | Works on weighted graphs? |
|---|---|
| SSSDSP (early termination on target `t`) |  Yes, but **only on non-negative weighted graphs** |
| SDSP (transpose graph trick) |  Yes |
| MSSP (multi-source, enqueue all with dist 0) |  Yes |
| Shortest Path Reconstruction (parent pointers) | Yes |
| 0/1-weighted graph | Solvable with Dijkstra's too (slower than BFS+deque) |

---

## 6. SSSP with Negative Weights (No Negative Cycle)

### Why Original Dijkstra's Fails

The greedy strategy assumes a *finalized* (popped) vertex's distance can never improve later. **This requires non-negative weights.** A negative edge discovered *after* a vertex is finalized can retroactively create a shorter path — but the algorithm never revisits that vertex.

**Concrete failure example:** the wrong path `0→1→3→4` (value 6) gets finalized for vertex 4 before the correct path `0→2→3→4` (using a `-10` weight edge, giving total 3) is discovered. Vertex 4 never learns about the correction — **wrong answer**.

**Crash risk:** with `std::set`, trying to `pq.erase(pq.find({dist[3], 3}))` when that pair was already removed/updated returns `pq.end()`, and erasing `end()` is **undefined behavior**.

### Why Modified Dijkstra's Still Works (Just Slower)

Since it never erases old entries — only inserts new ones and lazily filters stale ones — a vertex **can be reprocessed** multiple times as better paths are found later, even after being "finalized" once. This lets negative-edge corrections propagate correctly, and the shortest paths eventually become correct.

**Caveat:** the SSSDSP early-termination trick (stop as soon as target `t` is popped) **does not work safely** on such graphs.

### The Exponential Blowup Risk

On specially crafted graphs with negative edges but **no negative cycle** — e.g. a chain of "diamond/triangle" gadgets — Modified Dijkstra's may explore **all 2^k possible paths** from source to sink before settling on the correct answer, because each new negative-edge discovery reopens previously finalized vertices.

- Each additional triangle gadget (2 more vertices, 3 more edges) **doubles the runtime**.
- **Modified Dijkstra's can be made to run in exponential time** on such adversarial graphs.

This is why, when negative edges are possible, we switch to a fundamentally different algorithm: **Bellman-Ford**.

---

## 7. Bellman-Ford Algorithm

### When to Use It

General-purpose SSSP for graphs that **may contain negative edges, possibly even negative cycles**.

*Invented by Richard Bellman (also the pioneer of Dynamic Programming) and Lester Ford Jr. (co-inventor of the Ford-Fulkerson max-flow method).*

### Core Idea

> **Relax all `E` edges (in any order), `V - 1` times.**

- After pass 1: all vertices 1 edge away from `s` have correct distances.
- After pass 2: all vertices reachable within 2 edges are correct.
- After `V-1` passes: since any simple shortest path has at most `V-1` edges, **all shortest paths are correctly computed** (assuming no negative cycle).

### Basic Code

```cpp
#include <vector>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<pair<int,int>>>& adj, int source) {
    const int INF = 1e9;
    vector<int> dist(V, INF);
    dist[source] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;             // important check
            for (auto& [v, w] : adj[u]) {
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }
    return dist;
}
```

### Complexity

- `O(V³)` on an adjacency matrix (enumerating all edges costs `O(V²)` per pass).
- `O(V·E)` on an adjacency list or edge list.

Both are (much) slower than Dijkstra's `O((V+E) log V)` — the main reason Bellman-Ford isn't used unless negative weights force it.

### Optimized Version — Early Termination

Add a boolean flag: if a full pass produces **no** successful relaxation, stop immediately — no further pass will find anything new either. This makes the practical time complexity `O(k·V)` where `k` is the actual number of iterations needed (still `O(V)` worst case).

```cpp
#include <vector>
using namespace std;

struct BellmanFordResult {
    vector<int> dist;
    bool hasNegativeCycle;
};

BellmanFordResult bellmanFordOptimized(int V, vector<vector<pair<int,int>>>& adj, int source) {
    const int INF = 1e9;
    vector<int> dist(V, INF);
    dist[source] = 0;

    for (int i = 0; i < V - 1; i++) {
        bool modified = false;                        // optimization
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;              // important check
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w >= dist[v]) continue;  // not improving, skip
                dist[v] = dist[u] + w;                 // relax operation
                modified = true;                       // optimization
            }
        }
        if (!modified) break;                          // optimization
    }

    // one more pass to check for negative cycles
    bool hasNegativeCycle = false;
    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;
        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {               // should be false
                hasNegativeCycle = true;               // if true => negative cycle
            }
        }
    }

    return {dist, hasNegativeCycle};
}
```

### Detecting Negative Cycles

**Key theorem:** after `V-1` passes, if there's no negative cycle, no further relaxation should be possible.

> **If a relaxation still succeeds on an extra pass, the graph must contain a negative cycle.**

**Example:** cycle `1 → 2 → 3 → 1` with weights `15 + 0 + (-42) = -27` (a negative cycle).
- After 1 pass: `dist[1]=72`, `dist[2]=dist[3]=114`.
- After `V-1=5` passes: `dist[1]=-36`, `dist[2]=dist[3]=6` — Bellman-Ford stops here (by pass count).
- But we can **still** relax: `dist[2] = -36 + 15 = -21`, lower than the current `6` — proving a negative cycle exists.

**Why this matters:** vertices reachable from a negative cycle have **ill-defined** shortest paths — you can traverse the cycle infinitely to push the "shortest path" toward `-∞`. Vertices *not* reachable from the negative cycle still have valid, correct distances.

---

## 8. Bellman-Ford-Moore Algorithm (SPFA)

### Motivation

A known **queue-based improvement** over standard Bellman-Ford that eliminates a lot of redundant relaxation work. Discovered by Moore (1957) and independently by Bellman (1958). In the Chinese CS community, known as **SPFA** (Shortest Path Faster Algorithm, published by Duan Fanding in 1994) — though the "faster" label is potentially misleading, since it's not theoretically or empirically faster than Dijkstra's in general.

### Core Idea

Only re-process vertices whose `dist[]` was **just improved** — similar to BFS, but a vertex can be **re-enqueued multiple times** if its distance keeps improving.

**Two extra data structures:**
1. A queue of vertices waiting to be (re-)processed.
2. A boolean array to quickly check whether a vertex is currently already in the queue (avoids duplicate entries).

### Code

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<int> spfa(int V, vector<vector<pair<int,int>>>& adj, int source) {
    const int INF = 1e9;
    vector<int> dist(V, INF);
    vector<bool> inQueue(V, false);

    dist[source] = 0;
    queue<int> q;
    q.push(source);
    inQueue[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;                            // pop from queue

        for (auto& [v, w] : adj[u]) {
            if (dist[u] + w >= dist[v]) continue;       // not improving, skip
            dist[v] = dist[u] + w;                      // relax operation
            if (!inQueue[v]) {                          // v not already in queue
                q.push(v);
                inQueue[v] = true;
            }
        }
    }
    return dist;
}
```

### Complexity

True complexity is hard to analyze in general — runs in `O(k·E)` where `k` depends on the input graph. Worst case `k = O(V)`, matching standard Bellman-Ford's `O(V·E)`. In practice, per the authors' testing on UVa/Kattis problems, SPFA can be as fast as a good Dijkstra's implementation.

### Handling Negative Weights & Cycles

- Works correctly on graphs with negative edges, as long as **no negative cycle is reachable from the source**.
- If a negative cycle **is** reachable, pure SPFA **never terminates** — vertices along the cycle keep re-entering the queue forever.
- Can be slightly modified (similar to Bellman-Ford's check) to detect negative cycles in `O(V·E)`.

**Also used as:** a subroutine in Min-Cost Max-Flow (MCMF) algorithms.

---

## 9. Complexity Summary

| Algorithm | Complexity | Handles negative edges? | Handles negative cycles? |
|---|---|---|---|
| Original Dijkstra's (`set`) | `O((V+E) log V)` | ❌ Undefined behavior | ❌ |
| Modified Dijkstra's (`priority_queue` + lazy deletion) | `O((V+E) log V)` on non-negative; can degrade to **exponential** on adversarial negative-weight graphs | ✅ (slower, no negative cycle) | ❌ Infinite loop |
| Bellman-Ford | `O(V·E)` (or `O(V³)` with adjacency matrix) | ✅ | ✅ (detects them) |
| Bellman-Ford-Moore (SPFA) | `O(k·E)`, worst case `O(V·E)` | ✅ | Can be modified to detect |

---

## 10. Rule of Thumb

1. **Non-negative weights?** → Use Dijkstra's, `O((V+E) log V)`.
2. **Might have negative edges (no negative cycle)?** → Use Bellman-Ford or SPFA, `O(V·E)`.
3. **Need to detect a negative cycle?** → Use Bellman-Ford's extra verification pass.
4. **Complete graph (`E = O(V²)`) with non-negative weights?** → Skip the priority queue; use a simple `O(V)` linear scan per iteration to find the minimum-distance unvisited vertex, giving `O(V²)` overall instead of `O(V² log V)`.

*In practice, Dijkstra's `O((V+E) log V)` is a safe default most of the time, since the `log V` overhead rarely matters — but the moment negative weights are possible, you must switch away from Dijkstra's.*

---

## 11. Graph Modeling Example: Full Tank Problem

**Reference:** Kattis `fulltank` / UVa 11367 — *Full Tank?*

**Problem:** Given a weighted road network between cities, a fuel price `p[i]` at each city, and a car with fuel tank capacity `c`, find the cheapest trip from city `s` to city `e`. The car uses 1 unit of fuel per unit distance, starting with an empty tank.

**Why plain Dijkstra on the road graph fails:** the relevant state isn't just "current city" — it's **(current city, current fuel level)**, since whether a road is traversable depends on current fuel (no mid-road refueling).

**The modeling trick — build a State-Space graph:**
- Each vertex becomes a pair `(location, fuel)`.
- If `V ≤ 1000` and `c ≤ 100`, the state-space graph explodes to `V × c = 100,000` vertices.
- **Two edge types:**
  - **0-weight edge:** `(x, fuel_x) → (y, fuel_x - length(x,y))` — driving from `x` to `y`, if enough fuel.
  - **`p[x]`-weight edge:** `(x, fuel_x) → (x, fuel_x + 1)` — refueling by 1 unit at `x` (capped at `c`).
- Source vertex: `(s, 0)`. Target vertices: `(e, any fuel level 0..c)`.
- Run **Dijkstra's** on this state-space graph.

**Lesson:** many contest problems disguise a state-space SSSP problem inside what looks like a plain weighted-graph problem. Recognizing when the vertex definition needs to be **expanded with extra state** is a core competitive programming skill.

---

## 12. Reference Table — Classic Variants

| Variant Name | UVa | Kattis |
|---|---|---|
| SSSP on Unweighted Graph, Basic | 00336 | conquestcampaign |
| SSSP on Weighted Graph, Basic | 10986 | shortestpath1 |
| SSSP on Negative Cycle Graph, Basic | 00558 | shortestpath3 |
| SSSP on Implicit Graph, Unweighted | 10653 | grid |
| SSSP on Implicit Graph, Weighted | 00929 | blockcrusher |
| Single-Source Single-Destination SP | 01148 | flowerytrails |
| Single-Destination SP | 01112 | detour |
| Multi-Sources SP | 13127 | firestation |
| With shortest path reconstruction | 11049 | detour |
| On 0/1-Weighted Graph | 11573 | showroom |
| Basic State-Space Search | 10150 | fulltank |

**Observation:** roughly half of contest SSSP problems are on unweighted graphs (BFS suffices). Very few involve negative weights/cycles requiring Bellman-Ford. Most "real" weighted problems just need Dijkstra's.

---

## Key Exercises to Think About

- **4.4.3.1:** What if `set<pair<int,int>>` needs to store two different vertices that happen to have the same `dist` value? *(No issue — the pair `(dist, vertex)` is still unique as long as vertex IDs differ, since `set` compares pairs lexicographically.)*
- **4.4.3.2:** Can Modified Dijkstra's use a max-heap `priority_queue` (default in C++) without an explicit `greater<>` comparator? *(Hint: negate distances before pushing, similar to the trick used in Kruskal's algorithm implementation.)*
- **4.4.3.3:** What happens if the `if (d > dist[u]) continue;` check is removed from Modified Dijkstra's? *(Stale entries would get reprocessed unnecessarily — wasted work, and potentially incorrect relaxation attempts using outdated distances.)*
- **4.4.3.5:** On a complete graph (`E = O(V²)`), Dijkstra's runs in `O(V² log V)`. How to make it `O(V²)` instead? *(Avoid the priority queue — do an `O(V)` linear scan for the minimum-distance unvisited vertex each iteration.)*
- **4.4.4.1:** Why does relaxing all `E` edges `V-1` times guarantee correct SSSP values? *(Proof by induction on path length: after `k` passes, all shortest paths using at most `k` edges are correctly computed.)*

---

## Quick-Reference Summary

| Algorithm | Best for | Complexity |
|---|---|---|
| Original Dijkstra's (`set`) | Non-negative weights | `O((V+E) log V)` |
| Modified Dijkstra's (`priority_queue`) | Non-negative weights, Python-friendly | `O((V+E) log V)` |
| Bellman-Ford | Possible negative weights/cycles | `O(V·E)` |
| Bellman-Ford-Moore (SPFA) | Possible negative weights (no cycle), often fast in practice | `O(k·E)`, worst `O(V·E)` |