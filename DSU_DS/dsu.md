# Disjoint Set Union (DSU / Union-Find) — Complete Notes

> A comprehensive reference from beginner to advanced level.

---

## Table of Contents

1. [Introduction to DSU](#1-introduction-to-dsu)
2. [Motivation](#2-motivation)
3. [Problem Statement](#3-problem-statement)
4. [Basic Terminology](#4-basic-terminology)
5. [Parent Array](#5-parent-array)
6. [Tree Representation](#6-tree-representation)
7. [Make Set Operation](#7-make-set-operation)
8. [Find Operation](#8-find-operation)
9. [Union Operation](#9-union-operation)
10. [Naive DSU Implementation](#10-naive-dsu-implementation)
11. [Time Complexity of Naive DSU](#11-time-complexity-of-naive-dsu)
12. [Path Compression](#12-path-compression)
13. [Union by Rank](#13-union-by-rank)
14. [Union by Size](#14-union-by-size)
15. [Rank vs Size](#15-rank-vs-size)
16. [Path Compression + Union by Rank](#16-path-compression--union-by-rank)
17. [Path Compression + Union by Size](#17-path-compression--union-by-size)
18. [Amortized Time Complexity](#18-amortized-time-complexity)
19. [Why O(α(n))?](#19-why-oαn)
20. [Complete C++ Implementation](#20-complete-c-implementation)
21. [Dry Run Examples](#21-dry-run-examples)
22. [Detecting Cycles](#22-detecting-cycles)
23. [Connected Components](#23-connected-components)
24. [Kruskal's Algorithm](#24-kruskals-algorithm)
25. [Dynamic Connectivity](#25-dynamic-connectivity)
26. [Common Interview Questions](#26-common-interview-questions)
27. [Common Mistakes](#27-common-mistakes)
28. [Competitive Programming Template](#28-competitive-programming-template)
29. [Practice Problems](#29-practice-problems)
30. [Summary](#30-summary)

---

## 1. Introduction to DSU

**Disjoint Set Union (DSU)**, also called **Union-Find**, is a data structure that efficiently manages a collection of **non-overlapping (disjoint) sets**.

It supports two primary operations:
- **Find** — determine which set an element belongs to (by finding its root/representative).
- **Union** — merge two sets into one.

DSU is fundamental in graph algorithms, especially for problems involving **connectivity**, **cycle detection**, and **spanning trees**.

---

## 2. Motivation

Consider `n` elements numbered `0` to `n-1`. Initially, each element is its own group. Over time, we receive queries:

- **"Connect element A and element B"** → merge their groups.
- **"Are A and B in the same group?"** → check if they share the same representative.

A naive approach (e.g., BFS/DFS each time) costs **O(n + m)** per query. DSU handles each operation in **near O(1)** amortized time using two clever optimizations.

---

## 3. Problem Statement

**Given:**
- `n` elements, initially each in its own set.
- A sequence of `union(a, b)` and `find(x)` operations.

**Goal:** Process all operations efficiently.

**Constraints:** Up to `10^5` elements and `10^6` operations in competitive programming.

---

## 4. Basic Terminology

| Term | Meaning |
|------|---------|
| **Element** | An item tracked by DSU (usually an integer `0..n-1`) |
| **Set** | A group of elements; each set is disjoint from others |
| **Representative / Root** | A canonical element identifying a set (the "boss") |
| **Component** | Same as a set in graph context |
| **Rank** | Upper bound on the height of a node's subtree |
| **Size** | Total number of nodes in a set's tree |

---

## 5. Parent Array

The core data structure is a `parent[]` array where:

```
parent[i] = the parent of node i
```

If `parent[i] == i`, then `i` is the **root** of its set.

**Example (5 elements, all isolated):**

```
Index:    0  1  2  3  4
parent:   0  1  2  3  4   ← each node is its own parent
```

---

## 6. Tree Representation

Each set is stored as a **rooted tree**. The root represents the entire set.

```
After union(0,1), union(1,2):

    0
    |
    1
    |
    2

parent = [0, 0, 1, 3, 4]
```

Finding the representative means walking up the tree until you reach the root (`parent[x] == x`).

---

## 7. Make Set Operation

Initialize each element as its own set.

```cpp
void makeSet(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = i;
}
```

- Time: **O(n)**
- After this, there are `n` sets of size 1.

---

## 8. Find Operation

Returns the **root/representative** of the set containing `x`.

### Recursive Find

```cpp
int find(int x) {
    if (parent[x] == x) return x;
    return find(parent[x]);
}
```

### Iterative Find

```cpp
int find(int x) {
    while (parent[x] != x)
        x = parent[x];
    return x;
}
```

Both traverse up the tree until reaching the root. Without optimization, this is **O(depth)** — potentially **O(n)** in the worst case (degenerate chain).

---

## 9. Union Operation

Merges the sets containing `a` and `b`.

```cpp
void unite(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if (ra != rb)
        parent[ra] = rb;  // attach root of a's tree under root of b's tree
}
```

- Find both roots first.
- If they differ, attach one root under the other.
- If they are the same, `a` and `b` are already in the same set — **do nothing**.

---

## 10. Naive DSU Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int parent[MAXN];

void makeSet(int n) {
    for (int i = 0; i < n; i++) parent[i] = i;
}

int find(int x) {
    if (parent[x] == x) return x;
    return find(parent[x]);
}

void unite(int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra != rb) parent[ra] = rb;
}

bool connected(int a, int b) {
    return find(a) == find(b);
}
```

---

## 11. Time Complexity of Naive DSU

| Operation | Worst Case | Example Scenario |
|-----------|-----------|-----------------|
| `makeSet` | O(n) | initialization |
| `find` | **O(n)** | chain: 0→1→2→…→n-1 |
| `unite` | **O(n)** | calls find twice |

**Worst case:** `union(0,1), union(1,2), …, union(n-2, n-1)` creates a chain of depth `n-1`. Each subsequent `find` on element `0` takes `O(n)`.

The two optimizations below bring this down to nearly **O(1)** per operation.

---

## 12. Path Compression

### Intuition

When we call `find(x)` and traverse the path `x → p1 → p2 → … → root`, all nodes on this path **belong to the same set**. So we can make all of them point **directly to the root**, flattening the tree.

### Working

During `find(x)`, after reaching the root, update every node on the path to point directly to the root.

```
Before find(4):        After find(4):
    0                      0
    |                    / | \
    1                   1  2  4
    |
    2
    |
    4

parent[4]=0, parent[2]=0, parent[1]=0
```

### Dry Run

Initial tree (chain): `parent = [0, 0, 1, 2, 3]`

Call `find(4)`:
1. `find(4)` → `parent[4]=3`, recurse.
2. `find(3)` → `parent[3]=2`, recurse.
3. `find(2)` → `parent[2]=1`, recurse.
4. `find(1)` → `parent[1]=0`, recurse.
5. `find(0)` → `parent[0]=0`, return `0`.
6. Unwind: set `parent[1]=0`, `parent[2]=0`, `parent[3]=0`, `parent[4]=0`.

Result: `parent = [0, 0, 0, 0, 0]` — flat tree!

### Implementation

```cpp
// Recursive (most common)
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // path compression
    return parent[x];
}

// Iterative (two-pass)
int find(int x) {
    int root = x;
    while (parent[root] != root) root = parent[root];  // find root
    while (parent[x] != root) {                        // compress path
        int next = parent[x];
        parent[x] = root;
        x = next;
    }
    return root;
}
```

**Effect:** Subsequent `find` calls on nodes in this subtree take **O(1)**.

---

## 13. Union by Rank

### What is Rank?

**Rank** is an upper bound on the **height** of the subtree rooted at a node. It starts at `0` for every node.

```cpp
int rnk[MAXN];  // rank array, init to 0
```

### Why Rank?

In naive union, we always attach `ra` under `rb`. This can create tall trees. Instead, attach the **shorter tree** under the **taller tree** to minimize height growth.

> Key Insight: If both trees have rank `r`, their union has rank `r+1`. Otherwise, the rank stays the same as the taller tree's rank.

### Three Cases

| Case | Condition | Action | Rank change? |
|------|-----------|--------|-------------|
| 1 | `rank[ra] < rank[rb]` | `parent[ra] = rb` | No |
| 2 | `rank[ra] > rank[rb]` | `parent[rb] = ra` | No |
| 3 | `rank[ra] == rank[rb]` | `parent[ra] = rb` (arbitrary) | `rank[rb]++` |

### Detailed Analysis

- Rank only increases in Case 3.
- A node of rank `r` has **at least 2^r nodes** in its subtree (proof by induction).
- Therefore, rank is at most **log₂(n)**.
- This bounds tree height at **O(log n)**.

### Implementation

```cpp
void unite(int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra == rb) return;

    if (rnk[ra] < rnk[rb])    swap(ra, rb);  // ensure ra has >= rank
    parent[rb] = ra;                           // attach shorter under taller
    if (rnk[ra] == rnk[rb])   rnk[ra]++;     // only increase if equal
}
```

---

## 14. Union by Size

### Intuition

Instead of tracking height bounds (rank), track the **actual number of nodes** in each tree. Attach the **smaller tree** under the **larger tree**.

This is often preferred in practice because size is exact and more useful (e.g., for queries about component size).

### Implementation

```cpp
int sz[MAXN];  // size of each component

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}

void unite(int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra == rb) return;

    if (sz[ra] < sz[rb]) swap(ra, rb);  // ra is the larger tree
    parent[rb] = ra;
    sz[ra] += sz[rb];                   // update size of new root
}
```

> **Note:** Only update `sz` for the **root** of the merged set. Other nodes' sizes become stale and irrelevant.

---

## 15. Rank vs Size

| Aspect | Union by Rank | Union by Size |
|--------|--------------|--------------|
| What it tracks | Upper bound on height | Exact node count |
| After path compression | Rank may overestimate height | Size remains accurate |
| Getting component size | Not directly available | `sz[find(x)]` |
| Performance | Identical O(α(n)) | Identical O(α(n)) |
| Practical preference | Slightly simpler | More useful in problems |

**Recommendation:** Use **union by size** in competitive programming since component size is a common query.

---

## 16. Path Compression + Union by Rank

Combining both optimizations gives the best theoretical complexity.

```cpp
struct DSU {
    vector<int> parent, rnk;

    DSU(int n) : parent(n), rnk(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
};
```

---

## 17. Path Compression + Union by Size

```cpp
struct DSU {
    vector<int> parent, sz;

    DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }

    bool connected(int a, int b) { return find(a) == find(b); }
    int size(int x) { return sz[find(x)]; }
};
```

---

## 18. Amortized Time Complexity

| Optimization | Per Operation |
|-------------|--------------|
| None (naive) | O(n) worst |
| Path compression only | O(log n) amortized |
| Union by rank/size only | O(log n) worst |
| **Both combined** | **O(α(n)) amortized** |

For a sequence of `m` operations on `n` elements:

| Optimization | Total Cost |
|-------------|-----------|
| Naive | O(m · n) |
| Path compression only | O(m · log n) |
| Union by rank only | O(m · log n) |
| Both | **O(m · α(n))** |

---

## 19. Why O(α(n))?

**α(n)** is the **inverse Ackermann function** — one of the most slowly growing functions in mathematics.

| n | α(n) |
|---|------|
| 1 | 0 |
| 2–3 | 1 |
| 4–7 | 2 |
| 8–2047 | 3 |
| 2048–A(4,0) | 4 |
| Anything realistic | ≤ 4 |

For all practical values of `n` (up to 10^80), `α(n) ≤ 5`. This means DSU with both optimizations runs in **effectively O(1)** per operation.

**Why?** Path compression flattens trees; union by rank bounds tree growth. Their interaction ensures no node is far from its root for long. The amortized analysis using a potential function (Tarjan, 1975) proves the O(α(n)) bound rigorously.

---

## 20. Complete C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    int components;

    DSU(int n) : parent(n), sz(n, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    // Returns true if a merge happened (a and b were in different sets)
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);  // union by size: a is larger
        parent[b] = a;
        sz[a] += sz[b];
        components--;
        return true;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
    int size(int x)              { return sz[find(x)]; }
    int numComponents()          { return components; }
};

int main() {
    int n = 6;
    DSU dsu(n);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    cout << dsu.connected(0, 2) << "\n";  // 1 (true)
    cout << dsu.connected(0, 3) << "\n";  // 0 (false)
    cout << dsu.size(0)         << "\n";  // 3
    cout << dsu.numComponents() << "\n";  // 3

    return 0;
}
```

---

## 21. Dry Run Examples

### Example: 6 nodes, operations: union(0,1), union(2,3), union(1,3), find(0)

**Initial state:**
```
parent = [0, 1, 2, 3, 4, 5]
sz     = [1, 1, 1, 1, 1, 1]
```

**Step 1: union(0, 1)**
- find(0)=0, find(1)=1 → different sets
- sz[0]=sz[1]=1, no swap; parent[1]=0, sz[0]=2
```
parent = [0, 0, 2, 3, 4, 5]
sz     = [2, 1, 1, 1, 1, 1]
```

**Step 2: union(2, 3)**
- find(2)=2, find(3)=3; parent[3]=2, sz[2]=2
```
parent = [0, 0, 2, 2, 4, 5]
sz     = [2, 1, 2, 1, 1, 1]
```

**Step 3: union(1, 3)**
- find(1)=0 (via parent[1]=0), find(3)=2 (via parent[3]=2)
- sz[0]=sz[2]=2, no swap (a=0); parent[2]=0, sz[0]=4
```
parent = [0, 0, 0, 2, 4, 5]
sz     = [4, 1, 2, 1, 1, 1]
```

**Step 4: find(3) with path compression**
- find(3): parent[3]=2, parent[2]=0 → root=0
- Set parent[3]=0 (path compression)
```
parent = [0, 0, 0, 0, 4, 5]
```

---

## 22. Detecting Cycles

A cycle exists in an undirected graph if and only if we try to `union(a, b)` where `find(a) == find(b)`.

```cpp
bool hasCycle(int n, vector<pair<int,int>>& edges) {
    DSU dsu(n);
    for (auto [u, v] : edges) {
        if (!dsu.unite(u, v))  // already connected → cycle!
            return true;
    }
    return false;
}
```

**Example:**
- Edges: (0,1), (1,2), (2,0)
- union(0,1): merge → ok
- union(1,2): merge → ok
- union(2,0): find(2)=0, find(0)=0 → **cycle detected!**

---

## 23. Connected Components

Count the number of separate groups in a graph.

```cpp
int countComponents(int n, vector<pair<int,int>>& edges) {
    DSU dsu(n);
    for (auto [u, v] : edges)
        dsu.unite(u, v);
    return dsu.numComponents();
}
```

**Find all nodes in a component:**
```cpp
// All nodes x where find(x) == find(target)
vector<int> getComponent(DSU& dsu, int n, int target) {
    vector<int> comp;
    int root = dsu.find(target);
    for (int i = 0; i < n; i++)
        if (dsu.find(i) == root) comp.push_back(i);
    return comp;
}
```

---

## 24. Kruskal's Algorithm

Find the **Minimum Spanning Tree (MST)** of a weighted graph using DSU.

**Algorithm:**
1. Sort all edges by weight.
2. For each edge `(u, v, w)` in sorted order:
   - If `find(u) != find(v)`: add edge to MST, call `union(u, v)`.
   - Else: skip (would form a cycle).
3. Stop when MST has `n-1` edges.

```cpp
struct Edge { int u, v, w; };

int kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](auto& a, auto& b){ return a.w < b.w; });

    DSU dsu(n);
    int mstWeight = 0, edgeCount = 0;

    for (auto& [u, v, w] : edges) {
        if (dsu.unite(u, v)) {
            mstWeight += w;
            edgeCount++;
            if (edgeCount == n - 1) break;  // MST complete
        }
    }
    return mstWeight;  // returns -1 or check edgeCount for disconnected graphs
}
```

**Complexity:** O(m log m) for sorting + O(m · α(n)) for DSU = **O(m log m)** overall.

---

## 25. Dynamic Connectivity

DSU naturally supports **dynamic connectivity** — edges are added over time and we answer "are u and v connected?" queries online.

**Offline dynamic connectivity** (adding AND removing edges) requires more complex techniques (link-cut trees or offline divide-and-conquer), since standard DSU does **not support split/undo** natively.

**DSU with rollback (for offline offline undo):**
```cpp
// Instead of path compression, use union by rank only (rank-based, no compression)
// Store a stack of (node, old_parent, old_rank) for undo
struct DSUWithRollback {
    vector<int> parent, rnk;
    vector<tuple<int,int,int,int>> history;  // (node, old_parent, node2, old_rank)

    DSUWithRollback(int n) : parent(n), rnk(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x];  // NO path compression!
        return x;
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) { history.push_back({-1,-1,-1,-1}); return; }
        if (rnk[a] < rnk[b]) swap(a, b);
        history.push_back({b, parent[b], a, rnk[a]});
        parent[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
    }

    void rollback() {
        auto [b, pb, a, ra] = history.back(); history.pop_back();
        if (b == -1) return;
        parent[b] = pb;
        rnk[a] = ra;
    }
};
```

---

## 26. Common Interview Questions

**Q1: How do you detect a cycle in an undirected graph?**
> For each edge (u,v), if `find(u) == find(v)` before uniting, a cycle exists.

**Q2: What is the time complexity of DSU with both optimizations?**
> O(α(n)) amortized per operation, effectively O(1).

**Q3: Can DSU handle directed graphs?**
> Standard DSU ignores direction. For directed graphs, use Tarjan's SCC or Kosaraju's algorithm instead.

**Q4: What's the difference between union by rank and union by size?**
> Rank is an upper bound on height (doesn't update after path compression); size is the exact node count. Both give O(log n) tree height; size is more useful for answering "component size" queries.

**Q5: Can DSU detect cycles in directed graphs?**
> No. DSU treats edges as undirected. A directed graph needs DFS-based cycle detection.

**Q6: How do you count connected components?**
> Track a counter initialized to `n`; decrement it each time `unite` merges two distinct sets.

**Q7: How do you find the size of a component?**
> Store `sz[]` and return `sz[find(x)]`.

**Q8: What if we need to split a set (remove an element)?**
> Standard DSU doesn't support splits. For deletions, use a tombstone (mark element deleted, re-map to new node) or link-cut trees.

---

## 27. Common Mistakes

**1. Forgetting path compression in find**
```cpp
// ❌ Wrong — no compression
int find(int x) { return parent[x] == x ? x : find(parent[x]); }

// ✅ Correct
int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}
```

**2. Updating size/rank on the wrong node**
```cpp
// ❌ Wrong — updating the node being attached
parent[rb] = ra;
sz[rb] += sz[ra];  // rb is no longer a root!

// ✅ Correct — update the new root
parent[rb] = ra;
sz[ra] += sz[rb];
```

**3. Not checking if find(a) == find(b) before uniting**
```cpp
// ❌ Causes incorrect rank/size updates on self-union
void unite(int a, int b) {
    parent[find(a)] = find(b);
}

// ✅ Correct
void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;   // ← MUST check!
    // ...
}
```

**4. Stack overflow on recursive find for large inputs**
> Use iterative find or increase the stack size. For `n = 10^6` with no path compression, recursive find can overflow.

**5. Querying size on a non-root node**
```cpp
// ❌ Wrong — sz[x] is only meaningful for root x
int compSize = sz[x];

// ✅ Correct
int compSize = sz[find(x)];
```

**6. Off-by-one in node numbering**
> If the problem uses 1-indexed nodes, initialize DSU with `n+1` elements or adjust your indexing.

---

## 28. Competitive Programming Template

```cpp
// Paste-ready DSU template for competitive programming

struct DSU {
    vector<int> p, sz;
    int cc;  // connected components
    
    DSU(int n) : p(n), sz(n, 1), cc(n) {
        iota(p.begin(), p.end(), 0);
    }
    
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b]; cc--;
        return true;
    }
    
    bool same(int a, int b) { return find(a) == find(b); }
    int  size(int x)        { return sz[find(x)]; }
    int  components()       { return cc; }
};
```

**Usage pattern:**
```cpp
int main() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    while (m--) {
        int u, v; cin >> u >> v;
        dsu.unite(u, v);
    }
    // Query
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        cout << (dsu.same(a, b) ? "YES" : "NO") << "\n";
    }
}
```

---

## 29. Practice Problems

### Easy
| Problem | Platform | Key Concept |
|---------|----------|-------------|
| [Number of Provinces](https://leetcode.com/problems/number-of-provinces/) | LeetCode | Connected components |
| [Find if Path Exists in Graph](https://leetcode.com/problems/find-if-path-exists-in-graph/) | LeetCode | Basic connectivity |
| [Redundant Connection](https://leetcode.com/problems/redundant-connection/) | LeetCode | Cycle detection |

### Medium
| Problem | Platform | Key Concept |
|---------|----------|-------------|
| [Accounts Merge](https://leetcode.com/problems/accounts-merge/) | LeetCode | DSU + grouping |
| [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) | LeetCode | Tree validation |
| [Number of Islands II](https://leetcode.com/problems/number-of-islands-ii/) | LeetCode | Dynamic connectivity |
| [Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) | LeetCode | Kruskal's MST |

### Hard
| Problem | Platform | Key Concept |
|---------|----------|-------------|
| [Smallest String With Swaps](https://leetcode.com/problems/smallest-string-with-swaps/) | LeetCode | DSU + sorting |
| [Remove Max Number of Edges](https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/) | LeetCode | Dual DSU |
| [Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/) | LeetCode | Binary search + DSU |
| [Offline Dynamic Connectivity](https://codeforces.com/blog/entry/15890) | Codeforces | DSU with rollback |
| [Roads not only in Berland](https://codeforces.com/problemset/problem/25/D) | Codeforces | Kruskal + DSU |

---

## 30. Summary

```
DSU in a nutshell
─────────────────────────────────────────────────────────────────
  Data:    parent[] (+ rank[] or sz[])
  Init:    parent[i] = i  for all i
  Find:    walk up to root; compress path on the way back
  Union:   attach smaller/shorter tree under larger/taller root
─────────────────────────────────────────────────────────────────
  Complexity with both optimizations: O(α(n)) ≈ O(1) per op
─────────────────────────────────────────────────────────────────
  Applications:
    • Cycle detection in undirected graphs
    • Connected components (static and dynamic)
    • Kruskal's Minimum Spanning Tree
    • Offline dynamic connectivity
    • Grouping / clustering problems
─────────────────────────────────────────────────────────────────
  Key rules:
    1. Always path-compress in find()
    2. Always union by rank or size
    3. Check find(a)==find(b) before merging
    4. Update sz/rank on the new root only
    5. Use find(x) to query sz — not x directly
─────────────────────────────────────────────────────────────────
```

### Complexity Cheat Sheet

| Configuration | find | unite | Space |
|--------------|------|-------|-------|
| Naive | O(n) | O(n) | O(n) |
| Path compression only | O(log n) amortized | O(log n) | O(n) |
| Union by rank/size only | O(log n) | O(log n) | O(n) |
| **Both (optimal)** | **O(α(n))** | **O(α(n))** | **O(n)** |

---

