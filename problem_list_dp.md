# Dynamic Programming Interview Patterns — LeetCode Problem Map

*A pattern-recognition guide for DP coding interviews.*

Just like the graph guide, the goal here isn't to memorize 300 problems — it's to internalize **~15 recurring DP shapes**. Once you can recognize which shape a problem is wearing, the state definition and recurrence write themselves. DP interview questions are almost always **"what is the state, and what are the transitions"** questions in disguise — the coding is the easy part once that's answered.

---

## How to Use This

For each pattern:
1. **Recognition signals** — the phrases/constraints that hint at this pattern.
2. **State definition** — what `dp[i]` (or `dp[i][j]`, etc.) actually represents.
3. **Core recurrence** — the transition, in plain terms.
4. **LeetCode problems** — ordered roughly easy → hard.

---

## Table of Contents

1. [1D Linear DP (Fibonacci-style)](#1-1d-linear-dp-fibonacci-style)
2. [Kadane's / Max Subarray Family](#2-kadanes--max-subarray-family)
3. [0/1 Knapsack](#3-01-knapsack)
4. [Unbounded Knapsack / Coin Change](#4-unbounded-knapsack--coin-change)
5. [Longest Common Subsequence (LCS) Family](#5-longest-common-subsequence-lcs-family)
6. [Longest Increasing Subsequence (LIS) Family](#6-longest-increasing-subsequence-lis-family)
7. [Palindrome DP](#7-palindrome-dp)
8. [Interval DP](#8-interval-dp)
9. [Grid / Path DP](#9-grid--path-dp)
10. [String Matching DP (Edit Distance Family)](#10-string-matching-dp-edit-distance-family)
11. [State Machine DP (Stock Trading Family)](#11-state-machine-dp-stock-trading-family)
12. [Bitmask DP](#12-bitmask-dp)
13. [Digit DP](#13-digit-dp)
14. [Tree DP](#14-tree-dp)
15. [Partition / Subset-Sum Family](#15-partition--subset-sum-family)
16. [Game Theory DP](#16-game-theory-dp)
17. [DP on DAG (Graph-Flavored DP)](#17-dp-on-dag-graph-flavored-dp)
18. [Suggested Study Order](#18-suggested-study-order)

---

## 1. 1D Linear DP (Fibonacci-style)

**Recognition signals:** "number of ways to reach step N," "minimum cost to climb," each state depends only on a **fixed, small window** of previous states.

**State definition:** `dp[i]` = the answer for the first `i` elements / up to position `i`.

**Core recurrence:** `dp[i] = f(dp[i-1], dp[i-2], ...)` — combine a small constant number of prior states.

| # | Problem | Notes |
|---|---|---|
| 1 | Climbing Stairs | The canonical Fibonacci-shaped DP — `dp[i] = dp[i-1] + dp[i-2]` |
| 2 | Min Cost Climbing Stairs | Same shape, minimize instead of count |
| 3 | House Robber | `dp[i] = max(dp[i-1], dp[i-2] + nums[i])` — adjacent-exclusion pattern |
| 4 | House Robber II | Circular version — run House Robber twice (exclude first, exclude last) |
| 5 | Decode Ways | 1D DP with a validity-check branching factor (1 or 2 previous digits) |
| 6 | Fibonacci Number / N-th Tribonacci Number | Direct warm-up |
| 7 | Delete and Earn | Reduces to House Robber after a bucket-sort transformation |

---

## 2. Kadane's / Max Subarray Family

**Recognition signals:** "maximum sum subarray/subsequence," "maximum product," contiguous elements, single pass with a running best.

**State definition:** `dp[i]` = best subarray value **ending exactly at index `i`**.

**Core recurrence:** `dp[i] = max(nums[i], dp[i-1] + nums[i])` — either extend the previous run or start fresh here.

| # | Problem | Notes |
|---|---|---|
| 1 | Maximum Subarray | The template — pure Kadane's |
| 2 | Maximum Product Subarray | Track **both** running max and running min (negatives can flip a min into a max) |
| 3 | Maximum Sum Circular Subarray | Kadane's twice — normal max, and `total - min subarray` |
| 4 | Best Time to Buy and Sell Stock | Kadane's in disguise — track running minimum price seen so far |
| 5 | Maximum Absolute Sum of Any Subarray | Kadane's for both max and min simultaneously |

---

## 3. 0/1 Knapsack

**Recognition signals:** "each item used at most once," "can you partition into two equal-sum subsets," "target sum," "select a subset to maximize/reach exactly X."

**State definition:** `dp[i][w]` = best value achievable using the first `i` items with capacity `w`.

**Core recurrence:** `dp[i][w] = max(dp[i-1][w], dp[i-1][w-weight[i]] + value[i])` — either skip item `i`, or take it.

| # | Problem | Notes |
|---|---|---|
| 1 | Partition Equal Subset Sum | 0/1 Knapsack, boolean version — "can we hit target = sum/2" |
| 2 | Target Sum | 0/1 Knapsack reframed via `+`/`-` sign assignment algebra |
| 3 | Last Stone Weight II | Partition-style 0/1 Knapsack — minimize the difference between two subset sums |
| 4 | Ones and Zeroes | 2D-capacity 0/1 Knapsack (capacity in **both** zeros and ones) |
| 5 | Profitable Schemes | 0/1 Knapsack with 2 constraints (people used, minimum profit) |

---

## 4. Unbounded Knapsack / Coin Change

**Recognition signals:** "unlimited supply," "minimum number of coins," "number of ways to make change," items can be **reused**.

**State definition:** `dp[amount]` = min coins (or number of ways) to form `amount`.

**Core recurrence:** `dp[amount] = min(dp[amount], dp[amount - coin] + 1)` for each coin — the key difference from 0/1 Knapsack is the **iteration order** (coins on the outer loop for counting *combinations*; amount on the outer loop changes it to *permutations*).

| # | Problem | Notes |
|---|---|---|
| 1 | Coin Change | Minimum coins — unbounded knapsack, minimize |
| 2 | Coin Change II | Number of **combinations** — careful loop-order matters here |
| 3 | Combination Sum IV | Number of **permutations** — same values, different loop order than Coin Change II |
| 4 | Perfect Squares | Unbounded knapsack where "coins" = perfect squares |
| 5 | Minimum Cost For Tickets | Unbounded-knapsack-flavored — but indexed by day, with lookback windows (1/7/30 days) |

**Key interview insight:** Coin Change II and Combination Sum IV have **identical recurrences** but swapped loop nesting order — this single swap is one of the most common "gotcha" details interviewers probe on.

---

## 5. Longest Common Subsequence (LCS) Family

**Recognition signals:** two strings/sequences, "common," "shared," "interleaving," "delete minimum characters to make equal."

**State definition:** `dp[i][j]` = answer considering the first `i` characters of string A and first `j` characters of string B.

**Core recurrence:** if `A[i]==B[j]`, `dp[i][j] = dp[i-1][j-1] + 1`; else `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.

| # | Problem | Notes |
|---|---|---|
| 1 | Longest Common Subsequence | The direct template |
| 2 | Delete Operation for Two Strings | `answer = len(A) + len(B) - 2 * LCS(A,B)` |
| 3 | Shortest Common Supersequence | Build the actual supersequence by backtracking through the LCS table |
| 4 | Uncrossed Lines | Literally LCS with different flavor text |
| 5 | Interleaving String | 2D DP, but "does a valid interleaving exist" rather than length-counting |
| 6 | Distinct Subsequences | LCS-shaped table, but counts **ways**, not length |

---

## 6. Longest Increasing Subsequence (LIS) Family

**Recognition signals:** "longest increasing/non-decreasing subsequence," "longest chain," "box stacking," "envelope nesting."

**State definition (O(n²)):** `dp[i]` = length of the LIS **ending exactly at index `i`**.

**Core recurrence (O(n²)):** `dp[i] = max(dp[j] + 1)` for all `j < i` where `nums[j] < nums[i]`.

**Faster O(n log n) version:** maintain a `tails[]` array (patience sorting) and binary search for the insertion point on each new element.

| # | Problem | Notes |
|---|---|---|
| 1 | Longest Increasing Subsequence | The template — know **both** the O(n²) and O(n log n) versions |
| 2 | Number of Longest Increasing Subsequences | Track both `dp[i]` (length) and `count[i]` (ways to achieve that length) |
| 3 | Russian Doll Envelopes | Sort by one dimension, then LIS on the other — classic 2D→1D reduction |
| 4 | Maximum Length of Pair Chain | Sort + LIS-style greedy/DP |
| 5 | Longest Bitonic Subsequence | LIS computed **from both directions**, combine at each index |

---

## 7. Palindrome DP

**Recognition signals:** "palindromic substring/subsequence," "minimum cuts to partition into palindromes," "add minimum characters to make a palindrome."

**State definition:** `dp[i][j]` = `true`/answer for whether/how the substring `s[i..j]` is a palindrome (or related quantity).

**Core recurrence:** `dp[i][j] = (s[i]==s[j]) && dp[i+1][j-1]` — expand from the inside out (fill by increasing substring length).

| # | Problem | Notes |
|---|---|---|
| 1 | Longest Palindromic Substring | `dp[i][j]` boolean table, or the O(n) Manacher's for the optimal solution |
| 2 | Palindromic Substrings (count) | Same table, count `true` entries |
| 3 | Longest Palindromic Subsequence | Same recurrence shape as LCS(`s`, `reverse(s)`) |
| 4 | Palindrome Partitioning II | Min-cuts — combine the palindrome-table with a 1D "min cuts up to index i" DP |
| 5 | Minimum Insertion Steps to Make a String Palindrome | `len(s) - LPS(s)` (Longest Palindromic Subsequence) |

---

## 8. Interval DP

**Recognition signals:** "merge intervals to minimize/maximize cost," "matrix chain multiplication," "burst balloons," process defined over a **range `[i,j]`**, and the optimal split point is unknown.

**State definition:** `dp[i][j]` = best answer for the subrange/subproblem spanning indices `i` to `j`.

**Core recurrence:** `dp[i][j] = min/max over all split points k: dp[i][k] + dp[k+1][j] + cost(i,k,j)` — fill by **increasing interval length**, not by row/column order.

| # | Problem | Notes |
|---|---|---|
| 1 | Matrix Chain Multiplication (not on LeetCode directly, but foundational) | Study this first — the cleanest teaching example of the pattern |
| 2 | Burst Balloons | Interval DP with a clever "what if `k` is the **last** balloon burst in `[i,j]`" reframing |
| 3 | Minimum Cost to Merge Stones | Interval DP with an extra "number of piles merged" dimension |
| 4 | Strange Printer | Interval DP — `dp[i][j]` = min turns to print substring `[i,j]` |
| 5 | Remove Boxes | Interval DP with an extra "count of matching boxes attached" state dimension — a hard example |

---

## 9. Grid / Path DP

**Recognition signals:** 2D grid, "number of paths," "minimum path sum," movement restricted to right/down (or similar), robot on a grid.

**State definition:** `dp[r][c]` = answer for reaching cell `(r,c)` from the start.

**Core recurrence:** `dp[r][c] = f(dp[r-1][c], dp[r][c-1])` — combine from the cells you could have arrived from.

| # | Problem | Notes |
|---|---|---|
| 1 | Unique Paths | Pure counting version, `dp[r][c] = dp[r-1][c] + dp[r][c-1]` |
| 2 | Unique Paths II | Same, with obstacle cells forced to `0` |
| 3 | Minimum Path Sum | Same shape, minimize instead of count |
| 4 | Dungeon Game | Grid DP computed **backwards** (from destination to source) — health can't go below 1 |
| 5 | Cherry Pickup | Two simultaneous agents — state becomes `(step, col1, col2)`, a 3D DP |
| 6 | Triangle | Grid DP on a triangular grid, bottom-up is cleanest |
| 7 | Maximal Square | Grid DP where `dp[r][c]` = side length of largest square ending at `(r,c)` |


---

## 10. String Matching DP (Edit Distance Family)

**Recognition signals:** "convert string A to string B," "minimum operations (insert/delete/replace)," "wildcard/regex matching."

**State definition:** `dp[i][j]` = answer for matching/converting the first `i` characters of A against the first `j` characters of B.

**Core recurrence:** if characters match, `dp[i][j] = dp[i-1][j-1]`; else combine insert/delete/replace options: `dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])`.

| # | Problem | Notes |
|---|---|---|
| 1 | Edit Distance | The direct template — insert/delete/replace |
| 2 | Wildcard Matching | Same table shape, but transitions handle `?`/`*` wildcards |
| 3 | Regular Expression Matching | Similar to Wildcard, but `*` means "zero or more of the **preceding** character" — trickier transitions |
| 4 | One Edit Distance | Simplified check version (constant-space, early-exit) |

---

## 11. State Machine DP (Stock Trading Family)

**Recognition signals:** "buy and sell stock," "at most K transactions," "cooldown period," "transaction fee" — sequential decisions with a small number of discrete **states** (holding vs not holding).

**State definition:** `dp[day][state]` = max profit on this day while in this state (e.g., `state ∈ {holding, not-holding}`, sometimes with a "cooldown" sub-state).

**Core recurrence:** transition between states each day, e.g. `hold[i] = max(hold[i-1], sold[i-1] - price[i])`.

| # | Problem | Notes |
|---|---|---|
| 1 | Best Time to Buy and Sell Stock II | Unlimited transactions — greedy also works, but DP generalizes better |
| 2 | Best Time to Buy and Sell Stock with Cooldown | 3-state machine: hold / sold-today / resting |
| 3 | Best Time to Buy and Sell Stock with Transaction Fee | 2-state machine with a fee subtracted on sell (or buy) |
| 4 | Best Time to Buy and Sell Stock III | At most 2 transactions — state includes a transaction counter |
| 5 | Best Time to Buy and Sell Stock IV | At most K transactions — generalizes III, state = `(day, transactionsUsed, holding?)` |

**Key interview insight:** every stock problem is the **same state machine** with extra dimensions bolted on (a transaction counter, a cooldown flag, a fee). Draw the state diagram first, then the DP table falls out directly.

---

## 12. Bitmask DP

**Recognition signals:** small `n` (typically `n ≤ 20`), "visit all," "assign each," "subset of," Traveling Salesman-flavored, "each item assigned to exactly one of..."

**State definition:** `dp[mask][i]` = best answer having visited/used the set of elements represented by bitmask `mask`, currently at/having last processed element `i`.

**Core recurrence:** `dp[mask | (1<<j)][j] = min/max(dp[mask][i] + cost(i,j))` for each unset bit `j`.

| # | Problem | Notes |
|---|---|---|
| 1 | Partition to K Equal Sum Subsets | `dp[mask]` = can this subset (as a bitmask) be partitioned validly so far |
| 2 | Shortest Path Visiting All Nodes | Textbook TSP-shaped bitmask DP, `dp[mask][node]` |
| 3 | Minimum Cost to Connect Two Groups of Points | Bitmask over one group, DP over assignment cost |
| 4 | Maximum Students Taking Exam | Bitmask per row (seating arrangement), transition row-to-row |
| 5 | Number of Ways to Wear Different Hats to Each Other | Bitmask over **people** (small `n` here), iterate over hats |

---

## 13. Digit DP

**Recognition signals:** "count numbers in range `[L, R]` with property X," constraints on individual **digits** of a number, `R` can be huge (up to `10^9` or more, ruling out brute force iteration).

**State definition:** `dp[position][tight][...extra flags...]` = count of valid completions from this digit position onward.

**Core recurrence:** iterate over each possible digit at the current position (bounded by whether we're still "tight" against the upper limit), recurse to the next position.

| # | Problem | Notes |
|---|---|---|
| 1 | Numbers With Repeated Digits | Classic digit DP with a "used digits" bitmask as extra state |
| 2 | Count Numbers with Unique Digits | Simpler warm-up before the "repeated digits" complement version |
| 3 | Number of Digit One | Digit DP counting occurrences of a specific digit, not just valid-number counts |

**Note:** Digit DP is rarer in interviews than in competitive programming, but shows up occasionally in "count numbers with property X up to N" style questions.

---

## 14. Tree DP

**Recognition signals:** input is a tree, "maximum path sum," "maximum independent set on a tree," "rob houses arranged in a tree," answer depends on subtree aggregation.

**State definition:** typically a **pair** returned from each DFS call, e.g., `(bestIncludingRoot, bestExcludingRoot)`.

**Core recurrence:** combine children's DP results at each node, e.g. `excludeRoot = sum(max(childInclude, childExclude))`, `includeRoot = node.val + sum(childExclude)`.

| # | Problem | Notes |
|---|---|---|
| 1 | House Robber III | The template — tree DP returning `(rob, notRob)` pair per subtree |
| 2 | Binary Tree Maximum Path Sum | Tree DP tracking "best downward path," with a global max updated at each node |
| 3 | Diameter of Binary Tree | Simplified tree DP — return height, track diameter as a side-effect |
| 4 | Longest Univalue Path | Tree DP with a value-matching constraint on the "extend downward" step |
| 5 | Binary Tree Cameras | Greedy + tree DP hybrid — 3-state return value (covered / has camera / needs coverage) |

---

## 15. Partition / Subset-Sum Family

**Recognition signals:** "split into groups," "can you form exactly K subsets," "minimize maximum subset sum," related to but distinct from 0/1 Knapsack (often multiple groups instead of one capacity).

**State definition:** varies — often `dp[mask]` (bitmask, if `n` small) or `dp[i][remainingGroups][currentGroupSum]`.

| # | Problem | Notes |
|---|---|---|
| 1 | Partition Equal Subset Sum | (cross-listed with 0/1 Knapsack, Pattern 3) |
| 2 | Partition to K Equal Sum Subsets | Bitmask DP or backtracking with memoization |
| 3 | Matchsticks to Square | Special case of "K equal sum subsets" with `K=4` |
| 4 | Split Array Largest Sum | Binary search on the answer + greedy feasibility check (DP alternative also exists) |

---

## 16. Game Theory DP

**Recognition signals:** "two players take turns," "optimal play," "can player 1 win/guarantee a score," alternating min/max decisions.

**State definition:** `dp[i][j]` = the best score the **current player** can guarantee from the remaining range `[i,j]`.

**Core recurrence:** `dp[i][j] = max(pick left, pick right)` where picking gives you that value **minus** whatever the opponent then optimally achieves from the remaining range (since it becomes their turn).

| # | Problem | Notes |
|---|---|---|
| 1 | Predict the Winner | The template — interval DP with alternating-turn subtraction |
| 2 | Stone Game | Same shape as Predict the Winner |
| 3 | Stone Game II | Adds a "M" (move-count) state dimension |
| 4 | Can I Win | Bitmask DP (which numbers used) + turn parity |

---

## 17. DP on DAG (Graph-Flavored DP)

**Recognition signals:** "longest/shortest path in a matrix with strict ordering," "count paths," dependencies form a natural acyclic order — this is the same pattern documented in our **Graph** notes collection, listed here for completeness.

**Core technique:** see [`README_special_graphs.md`](./README_special_graphs.md) — Section 2 (DAG: SSSP/Longest Paths/Counting Paths), and [`README_leetcode_patterns.md`](./README_leetcode_patterns.md) — Pattern 13.

| # | Problem | Notes |
|---|---|---|
| 1 | Longest Increasing Path in a Matrix | Grid as implicit DAG; DP = longest path |
| 2 | Out of Boundary Paths | Counting paths in an implicit DAG with a step-budget dimension |
| 3 | Frog Jump | Implicit DAG over `(position, jumpSize)` states |

---

## 18. Suggested Study Order

1. **1D Linear DP** and **Kadane's** — build fluency with the simplest possible state (a single running value) before adding dimensions.
2. **0/1 Knapsack** and **Unbounded Knapsack/Coin Change** — the two "capacity" DP shapes; learn to distinguish them by whether items are reusable, and learn the loop-order subtlety (combinations vs permutations).
3. **Grid/Path DP** — a natural 2D extension of pattern 1, very common as an "easy-medium" warm-up in interviews.
4. **LCS Family** and **String Matching DP** — the two-string 2D DP shape; almost every "compare two strings" question is one of these.
5. **LIS Family** — know both the O(n²) DP and the O(n log n) patience-sorting version; interviewers often ask you to optimize from one to the other.
6. **Palindrome DP** and **Interval DP** — the "fill by increasing range length" mental model; Interval DP especially trips people up until you've drilled it a few times.
7. **State Machine DP** — once comfortable with multi-dimensional DP, the stock-trading family is highly templated and a very common interview topic.
8. **Tree DP** — combine your DFS fluency (from the graph patterns) with DP thinking — subtree aggregation is a distinct but learnable skill.
9. **Bitmask DP**, **Digit DP**, **Game Theory DP**, **Partition family** — more specialized; lower frequency in interviews but common in OA/competitive settings. Learn the *shape*, drill 2-3 problems each, move on.

---

## The One Meta-Skill That Matters Most

Every pattern above reduces to answering **two questions** before writing any code:

1. **What does `dp[...]` represent?** (Be precise — "the best X achievable given constraints Y" — and say it out loud before coding.)
2. **What are the valid transitions into this state, and what's the base case?**

If you can answer both clearly, the code is usually a 10-15 line loop. Most DP interview failures come from skipping straight to code without nailing down the state definition first — practice narrating the state and recurrence out loud before typing anything.