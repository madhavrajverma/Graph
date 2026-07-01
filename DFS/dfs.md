# DFS — Depth First Search

**Topic:** Graph Traversal  
**Type:** Core Algorithm

---

## What is DFS?

Explores graph by going as **deep as possible** before backtracking.  
Uses **Stack / Recursion** (vs BFS which uses Queue).

---

## Recursive Template

```cpp
void dfs(vector<vector<int>>& adj, int u, vector<bool>& visited) {
    visited[u] = true;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (!visited[v])
            dfs(adj, v, visited);
    }
}

// For disconnected graph:
for (int i = 0; i < V; i++)
    if (!visited[i])
        dfs(adj, i, visited);
```

---

## Iterative Template (avoids stack overflow)

```cpp
void dfsIterative(vector<vector<int>>& adj, int start, int V) {
    vector<bool> visited(V, false);
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (int i = adj[u].size() - 1; i >= 0; i--) {
            if (!visited[adj[u][i]])
                st.push(adj[u][i]);
        }
    }
}
```

---

## BFS vs DFS

| | BFS | DFS |
|---|---|---|
| Structure | Queue | Stack/Recursion |
| Order | Level by level | Deep first |
| Shortest path | Yes |  No |
| Memory | O(width) | O(depth) |

---

## When to Use DFS

- Cycle detection
- Topological sort
- Connected components
- Bridges & articulation points
- Strongly connected components (Kosaraju)
- Flood fill
- Tree problems (ancestors, subtrees)
- Backtracking

---

## Complexity

| | Value |
|---|---|
| Time | O(V+E) |
| Space | O(V) |

---

## Common Mistakes

- Mark visited **before** recursive call not after
- DFS finds **a** path not **shortest** path → use BFS for shortest
- For large V → use iterative DFS to avoid stack overflow
- Always loop all nodes for disconnected graphs