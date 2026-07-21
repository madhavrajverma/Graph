# Master Interview Pattern Map — LeetCode (Non-Graph, Non-DP)

*A pattern-recognition guide covering every major non-graph, non-DP interview pattern.*

*(Graph patterns → [`README_leetcode_patterns.md`](./README_leetcode_patterns.md). DP patterns → [`README_dp_patterns.md`](./README_dp_patterns.md).)*

The philosophy is identical to the other two guides: don't memorize hundreds of problems in isolation — internalize **~27 recurring shapes**. Once you can name the pattern a problem is wearing, the approach is templated; only the fiddly details change. This guide spans roughly **300+ problems** across every classic non-graph, non-DP pattern tested in interviews.

---

## How to Use This

For each pattern:
1. **Recognition signals** — the phrases/constraints that hint at this pattern.
2. **Core idea** — the one-sentence mental model.
3. **LeetCode problems** — ordered roughly easy → hard.

---

## Table of Contents

1. [Two Pointers](#1-two-pointers)
2. [Sliding Window](#2-sliding-window)
3. [Fast & Slow Pointers / Linked List](#3-fast--slow-pointers--linked-list)
4. [Merge Intervals](#4-merge-intervals)
5. [Cyclic Sort](#5-cyclic-sort)
6. [Monotonic Stack](#6-monotonic-stack)
7. [Monotonic Queue / Sliding Window Extremes](#7-monotonic-queue--sliding-window-extremes)
8. [Binary Search (Classic)](#8-binary-search-classic)
9. [Binary Search on the Answer](#9-binary-search-on-the-answer)
10. [Top K Elements / Heap](#10-top-k-elements--heap)
11. [Two Heaps](#11-two-heaps)
12. [K-Way Merge](#12-k-way-merge)
13. [Backtracking](#13-backtracking)
14. [Greedy](#14-greedy)
15. [Bit Manipulation](#15-bit-manipulation)
16. [Math & Number Theory](#16-math--number-theory)
17. [Trie](#17-trie)
18. [Binary Tree Traversal & Recursion](#18-binary-tree-traversal--recursion)
19. [Binary Search Tree (BST) Specific](#19-binary-search-tree-bst-specific)
20. [Design (Data Structures)](#20-design-data-structures)
21. [Prefix Sum / Difference Array](#21-prefix-sum--difference-array)
22. [Matrix-Specific Patterns](#22-matrix-specific-patterns)
23. [String Manipulation](#23-string-manipulation)
24. [Sweep Line / Advanced Intervals](#24-sweep-line--advanced-intervals)
25. [Union-Find (Non-Graph Uses)](#25-union-find-non-graph-uses)
26. [Divide and Conquer](#26-divide-and-conquer)
27. [Segment Tree / Binary Indexed Tree (Fenwick Tree)](#27-segment-tree--binary-indexed-tree-fenwick-tree)
28. [Suggested Study Order](#28-suggested-study-order)

---

## 1. Two Pointers

**Recognition signals:** sorted array, "pair that sums to X," "remove duplicates in place," comparing elements from both ends or two different indices moving independently.

**Core idea:** maintain two indices that move toward each other (or at different speeds) to avoid an `O(n²)` nested loop.

| # | Problem | Notes |
|---|---|---|
| 1 | Two Sum II - Input Array Is Sorted | The template — pointers from both ends |
| 2 | Valid Palindrome | Two pointers converging inward with a skip-invalid-char rule |
| 3 | Remove Duplicates from Sorted Array | Two pointers, one reading one writing |
| 4 | Move Zeroes | Same read/write pointer idea |
| 5 | Container With Most Water | Two pointers + greedy "move the shorter wall" argument |
| 6 | 3Sum | Fix one element, two-pointer the rest of the sorted array |
| 7 | 3Sum Closest | Same as 3Sum, track closest instead of exact match |
| 8 | 4Sum | Nested 3Sum, two fixed elements + two pointers |
| 9 | Sort Colors (Dutch National Flag) | Three pointers (low/mid/high) partitioning |
| 10 | Trapping Rain Water | Two pointers tracking running max from each side |
| 11 | Backspace String Compare | Two pointers moving backward through both strings |
| 12 | Boats to Save People | Two pointers + greedy pairing (lightest with heaviest) |
| 13 | Squares of a Sorted Array | Two pointers from both ends, fill result from the back |
| 14 | Valid Triangle Number | Two pointers per fixed largest side, count valid pairs |
| 15 | Partition Labels | Two-pointer-flavored interval merging via last-occurrence tracking |

---

## 2. Sliding Window

**Recognition signals:** "longest/shortest substring/subarray with property X," contiguous elements, a window that expands and shrinks.

**Core idea:** maintain a window `[left, right]`; expand `right` to include more, shrink `left` when a constraint is violated — never re-scan from scratch.

| # | Problem | Notes |
|---|---|---|
| 1 | Maximum Average Subarray I | Fixed-size window — the simplest warm-up |
| 2 | Longest Substring Without Repeating Characters | Variable window + hashmap of last-seen index |
| 3 | Minimum Size Subarray Sum | Variable window, shrink while sum condition still holds |
| 4 | Longest Repeating Character Replacement | Window + "majority count" tracking, shrink when replacements exceed budget |
| 5 | Permutation in String | Fixed window + frequency-map comparison |
| 6 | Find All Anagrams in a String | Same as above, collect all valid window starts |
| 7 | Minimum Window Substring | Variable window + "have I covered all required chars" tracking |
| 8 | Longest Substring with At Most K Distinct Characters | Variable window + frequency map, shrink when distinct count exceeds K |
| 9 | Fruit Into Baskets | Same shape as "at most K distinct" with K=2 |
| 10 | Subarrays with K Different Integers | "At most K" minus "at most K-1" trick |
| 11 | Max Consecutive Ones III | Window with a flip-budget constraint |
| 12 | Sliding Window Maximum | Window + monotonic deque (cross-listed in Pattern 7) |
| 13 | Longest Substring with At Least K Repeating Characters | Divide-and-conquer or sliding window with a distinct-char-count outer loop |
| 14 | Grumpy Bookstore Owner | Fixed window applied to a "convert this segment" gain calculation |
| 15 | Subarray Product Less Than K | Variable window on a running product |
| 16 | Count Number of Nice Subarrays | "At most K odd numbers" minus "at most K-1" trick |
| 17 | Minimum Number of K Consecutive Bit Flips | Sliding window + difference-array-style lazy propagation |
| 18 | Sliding Window Median | Window + two-heap or ordered structure for the median |

---

## 3. Fast & Slow Pointers / Linked List

**Recognition signals:** linked list, "detect a cycle," "find the middle," "Nth node from the end," "reverse in groups."

**Core idea:** two pointers moving at different speeds through a linked structure reveal cycles, midpoints, and offsets without needing a second pass or extra storage.

| # | Problem | Notes |
|---|---|---|
| 1 | Middle of the Linked List | Slow/fast pointer, slow lands on the middle when fast reaches the end |
| 2 | Linked List Cycle | Floyd's cycle detection — fast/slow pointers meet iff a cycle exists |
| 3 | Linked List Cycle II | Extends Cycle I — find the actual cycle **start** node |
| 4 | Happy Number | Floyd's cycle detection applied to a numeric sequence, not a list |
| 5 | Remove Nth Node From End of List | Two pointers with a fixed `N` gap |
| 6 | Reverse Linked List | The fundamental in-place pointer-reversal template |
| 7 | Reverse Linked List II | Reverse only a sub-range `[left, right]` |
| 8 | Reverse Nodes in k-Group | Reverse in fixed-size chunks, recursively/iteratively |
| 9 | Swap Nodes in Pairs | Special case of k-Group reversal with k=2 |
| 10 | Palindrome Linked List | Find middle (fast/slow) + reverse second half + compare |
| 11 | Merge Two Sorted Lists | Two-pointer merge, foundational for K-Way Merge later |
| 12 | Add Two Numbers | Simultaneous pointer traversal + carry propagation |
| 13 | Copy List with Random Pointer | Interleaving trick or hashmap-based cloning |
| 14 | Intersection of Two Linked Lists | Two pointers, switch lists at the end to equalize length difference |
| 15 | Rotate List | Find length, connect tail to head, cut at new break point |

---

## 4. Merge Intervals

**Recognition signals:** list of `[start, end]` ranges, "merge overlapping," "insert a new interval," "meeting rooms," schedule conflicts.

**Core idea:** sort by start time, then greedily merge/compare each interval against the last one kept.

| # | Problem | Notes |
|---|---|---|
| 1 | Merge Intervals | The direct template — sort, then merge overlapping |
| 2 | Insert Interval | Merge a new interval into an already-sorted, non-overlapping list |
| 3 | Non-overlapping Intervals | Greedy — sort by **end** time, count minimum removals |
| 4 | Meeting Rooms | Sort by start, check for any overlap |
| 5 | Meeting Rooms II | Min heap of end times, or sweep-line of +1/-1 events |
| 6 | Interval List Intersections | Two-pointer walk across two sorted interval lists |
| 7 | Employee Free Time | Merge all intervals across employees, find the gaps |
| 8 | Minimum Number of Arrows to Burst Balloons | Sort by end, greedy — same shape as Non-overlapping Intervals |
| 9 | Car Pooling | Sweep-line / difference array over pickup and dropoff events |
| 10 | My Calendar I / II / III | Interval overlap tracking — brute force, then double-booking counter, then sweep-line for max overlap |

---

## 5. Cyclic Sort

**Recognition signals:** array of `n` numbers in range `[1,n]` or `[0,n-1]`, "find the missing/duplicate number," constant extra space required.

**Core idea:** since values map directly to valid index positions, repeatedly swap each element to its "correct" index — one pass, `O(1)` space.

| # | Problem | Notes |
|---|---|---|
| 1 | Missing Number | Cyclic sort or sum-formula trick |
| 2 | Find All Numbers Disappeared in an Array | Cyclic sort, or negative-marking trick |
| 3 | Find the Duplicate Number | Cyclic sort, or Floyd's cycle detection (treat array as an implicit linked list) |
| 4 | Find All Duplicates in an Array | Negative-marking variant of cyclic sort |
| 5 | First Missing Positive | Cyclic sort — place each value `v` at index `v-1` if in range |
| 6 | Set Mismatch | Cyclic sort, spot the index that's wrong |
| 7 | Couples Holding Hands | Cyclic-sort-flavored — greedily fix mismatched pairs in place |
| 8 | K-th Missing Positive Number | Binary search alternative, but cyclic-sort mental model helps recognize the structure |

---

## 6. Monotonic Stack

**Recognition signals:** "next greater/smaller element," "daily temperatures," histogram/rectangle problems, "remove characters to make the smallest/largest result."

**Core idea:** maintain a stack that's always increasing or decreasing; pop elements that violate the order as you scan, since they can never be the answer for future elements once a "better" one is seen.

| # | Problem | Notes |
|---|---|---|
| 1 | Next Greater Element I | The template — monotonic decreasing stack |
| 2 | Next Greater Element II | Circular array — iterate twice through the array |
| 3 | Daily Temperatures | Stack storing indices, not values |
| 4 | Largest Rectangle in Histogram | Stack of increasing bar heights, pop-and-compute-area on violation |
| 5 | Maximal Rectangle | Reduce to "Largest Rectangle in Histogram" row by row |
| 6 | Trapping Rain Water | Monotonic stack alternative to the two-pointer solution |
| 7 | Remove Duplicate Letters | Monotonic stack + "can I still use this char later" check |
| 8 | Remove K Digits | Monotonic increasing stack, pop while it helps minimize the result |
| 9 | 132 Pattern | Monotonic stack tracking a candidate "3" while scanning from the right |
| 10 | Sum of Subarray Minimums | Monotonic stack to find, for each element, its contribution range |
| 11 | Online Stock Span | Monotonic stack storing (price, span) pairs |
| 12 | Asteroid Collision | Stack simulating collisions, pop while the top is "destroyed" |
| 13 | Car Fleet | Sort by position, monotonic stack of arrival times |
| 14 | Basic Calculator | Stack for parsing nested parentheses/signs |
| 15 | Decode String | Stack for parsing nested bracket structure `k[encoded]` |

---

## 7. Monotonic Queue / Sliding Window Extremes

**Recognition signals:** "maximum/minimum in every window of size K," need the extreme value of a sliding window in `O(1)` amortized.

**Core idea:** a double-ended queue that stays monotonic — pop from the back while new elements are "better," pop from the front when elements fall outside the window.

| # | Problem | Notes |
|---|---|---|
| 1 | Sliding Window Maximum | The direct template — monotonic decreasing deque of indices |
| 2 | Shortest Subarray with Sum at Least K | Monotonic deque on **prefix sums**, not raw values |
| 3 | Constrained Subsequence Sum | DP + monotonic deque to maintain the max over a sliding window of DP values |
| 4 | Jump Game VI | Same DP + monotonic deque combo as above |
| 5 | Sliding Window Median | Two heaps (Pattern 11) is more common, but a balanced BST/monotonic structure also works |
| 6 | Maximum of Minimum Values in All Subarrays | Related to Monotonic Stack (Pattern 6) but framed as sliding-window extremes across all window sizes |

---

## 8. Binary Search (Classic)

**Recognition signals:** sorted (or rotated-sorted) array, `O(log n)` requirement, "find target/first/last occurrence," "find peak."

**Core idea:** repeatedly halve the search space using a monotonic condition on the array.

| # | Problem | Notes |
|---|---|---|
| 1 | Binary Search | The absolute template |
| 2 | Search Insert Position | Binary search returning insertion index on miss |
| 3 | First Bad Version | Binary search on a monotonic predicate (API call) |
| 4 | Find First and Last Position of Element in Sorted Array | Two binary searches — leftmost and rightmost bound |
| 5 | Search in Rotated Sorted Array | Binary search with an extra "which half is sorted" check |
| 6 | Search in Rotated Sorted Array II | Same, with duplicate-handling edge case |
| 7 | Find Minimum in Rotated Sorted Array | Binary search for the rotation pivot |
| 8 | Find Peak Element | Binary search using local slope comparison |
| 9 | Search a 2D Matrix | Treat the 2D matrix as a flattened 1D sorted array |
| 10 | Search a 2D Matrix II | Staircase search (not binary search per se, but same "sorted structure" family) |
| 11 | Find K Closest Elements | Binary search for the optimal window start |
| 12 | Single Element in a Sorted Array | Binary search exploiting pair-index parity |
| 13 | Peak Index in a Mountain Array | Binary search, simplified "Find Peak Element" |
| 14 | Median of Two Sorted Arrays | Binary search on the smaller array's partition point |
| 15 | Time Based Key-Value Store | Binary search over a per-key sorted timestamp list |
| 16 | Find the Duplicate Number (binary search variant) | Binary search on **value range**, not index — cross-listed with Pattern 5 |
| 17 | Count of Smaller Numbers After Self | Binary search on a Fenwick Tree / BIT of seen values (cross-listed with Pattern 27) |
| 18 | H-Index II | Binary search on a monotonic citation condition |
| 19 | Kth Smallest Element in a Sorted Matrix | Binary search on the **value**, count how many elements are ≤ mid |
| 20 | Random Pick with Weight | Binary search over a prefix-sum array |

---

## 9. Binary Search on the Answer

**Recognition signals:** "minimize the maximum," "maximize the minimum," "what is the smallest X such that condition holds," the answer itself is a **number to search for**, not an index.

**Core idea:** guess an answer `mid`, write an `O(n)` (or better) feasibility check for "is `mid` achievable?", then binary search over the answer space using that check as the monotonic predicate.

| # | Problem | Notes |
|---|---|---|
| 1 | Koko Eating Bananas | Binary search on eating speed, feasibility = total hours ≤ H |
| 2 | Capacity To Ship Packages Within D Days | Binary search on capacity, feasibility = days needed ≤ D |
| 3 | Split Array Largest Sum | Binary search on max-subarray-sum, feasibility = number of splits needed ≤ K |
| 4 | Minimum Number of Days to Make m Bouquets | Binary search on day count, feasibility = can we make m bouquets by then |
| 5 | Magnetic Force Between Two Balls | Binary search on minimum distance, feasibility = can we place all balls with ≥ this gap |
| 6 | Divide Chocolate | Same shape as Split Array Largest Sum, framed as maximize-the-minimum |
| 7 | Aggressive Cows (classic, various judges) | The canonical "maximize the minimum gap" binary-search-on-answer problem |
| 8 | Smallest Divisor Given a Threshold | Binary search on divisor, feasibility = sum of ceil-divisions ≤ threshold |
| 9 | Path With Maximum Minimum Value | Binary search on the answer + BFS/DFS feasibility (or the Dijkstra-variant from our Graph notes) |
| 10 | Swim in Rising Water | Binary search on water level + BFS/DFS feasibility (cross-listed with Graph MiniMax pattern) |

---

## 10. Top K Elements / Heap

**Recognition signals:** "K largest/smallest/most frequent," "kth element," don't need a full sort, just the top/bottom K.

**Core idea:** maintain a heap of size K; for "K largest," use a **min-heap** (evict the smallest when the heap exceeds size K) — counter-intuitive but essential to remember.

| # | Problem | Notes |
|---|---|---|
| 1 | Kth Largest Element in an Array | Min-heap of size K, or Quickselect for O(n) average |
| 2 | Kth Largest Element in a Stream | Persistent min-heap of size K, updated per insertion |
| 3 | Top K Frequent Elements | Frequency map + min-heap of size K (or bucket sort for O(n)) |
| 4 | Top K Frequent Words | Same as above + lexicographic tie-breaking |
| 5 | K Closest Points to Origin | Max-heap of size K by distance |
| 6 | Kth Smallest Element in a Sorted Matrix | Min-heap seeded with first row/column, pop-and-push traversal |
| 7 | Find K Pairs with Smallest Sums | Min-heap seeded with initial candidate pairs |
| 8 | Sort Characters By Frequency | Frequency map + max-heap (or bucket sort) |
| 9 | Task Scheduler | Max-heap by remaining frequency + cooldown queue |
| 10 | Reorganize String | Max-heap by frequency, greedily place the most frequent char, avoiding adjacent repeats |
| 11 | Ugly Number II | Min-heap (or three-pointer DP) generating candidates in order |
| 12 | Super Ugly Number | Same as Ugly Number II, generalized to K primes |
| 13 | Furthest Building You Can Reach | Min-heap tracking which "ladder" uses to convert to "bricks" |
| 14 | Last Stone Weight | Max-heap, repeatedly smash the two heaviest stones |
| 15 | Distant Barcodes | Max-heap by frequency, greedily interleave placements |

---

## 11. Two Heaps

**Recognition signals:** "median of a data stream," need to track both a lower half and upper half of a dataset dynamically.

**Core idea:** a max-heap for the lower half, a min-heap for the upper half, kept balanced in size — the median is always accessible at the top of one (or both) heaps.

| # | Problem | Notes |
|---|---|---|
| 1 | Find Median from Data Stream | The direct template |
| 2 | Sliding Window Median | Two heaps + lazy deletion for elements leaving the window |
| 3 | IPO | Max-heap of profits, min-heap (or sorted list) of capital requirements |
| 4 | Maximize Capital | (Same problem as IPO on some platforms) |
| 5 | Median of a Row Wise Sorted Matrix | Binary-search alternative, but conceptually related to the "balance two halves" idea |
| 6 | Minimize Deviation in Array | Max-heap with a transformation rule (halve/double) applied greedily |

---

## 12. K-Way Merge

**Recognition signals:** "merge K sorted lists/arrays," "smallest range covering elements from K lists."

**Core idea:** a min-heap seeded with the first element of each list; repeatedly pop the smallest, push the next element from that same list.

| # | Problem | Notes |
|---|---|---|
| 1 | Merge Two Sorted Lists | The K=2 base case |
| 2 | Merge k Sorted Lists | The direct template, min-heap of size K |
| 3 | Kth Smallest Element in a Sorted Matrix | K-way merge across matrix rows (cross-listed with Pattern 10) |
| 4 | Smallest Range Covering Elements from K Lists | Min-heap + track the current max across all lists, shrink range greedily |
| 5 | Find K Pairs with Smallest Sums | K-way-merge flavored heap expansion (cross-listed with Pattern 10) |
| 6 | Merge Sorted Array | The simplest in-place two-pointer merge (K=2, no heap needed) |

---

## 13. Backtracking

**Recognition signals:** "generate all," "all possible combinations/permutations/subsets," "solve the puzzle" (Sudoku, N-Queens), explicit constraint satisfaction.

**Core idea:** build a solution incrementally; at each step try every valid choice, recurse, then **undo** the choice (backtrack) before trying the next one.

| # | Problem | Notes |
|---|---|---|
| 1 | Subsets | The template — include/exclude at each index |
| 2 | Subsets II | Same, with duplicate-skipping logic |
| 3 | Permutations | Template — swap-based or "used[]" array based |
| 4 | Permutations II | Same, with duplicate-skipping via sorting first |
| 5 | Combinations | Choose K from N, prune via remaining-count check |
| 6 | Combination Sum | Reuse allowed — don't advance the index on a successful pick |
| 7 | Combination Sum II | No reuse + duplicate-skipping |
| 8 | Combination Sum III | Combination Sum with a fixed K-length constraint |
| 9 | Generate Parentheses | Backtracking with an "open ≤ close" validity constraint |
| 10 | Letter Combinations of a Phone Number | Backtracking over a fixed digit-to-letters mapping |
| 11 | Word Search | Backtracking on a grid with a visited-marking/unmarking pattern |
| 12 | Word Search II | Word Search + Trie for efficient multi-word pruning |
| 13 | N-Queens | Backtracking + column/diagonal conflict tracking |
| 14 | N-Queens II | Same, just count solutions instead of returning them |
| 15 | Sudoku Solver | Backtracking + row/col/box constraint checking |
| 16 | Palindrome Partitioning | Backtracking + palindrome-check pruning at each cut |
| 17 | Restore IP Addresses | Backtracking over 4 segments with validity constraints |
| 18 | Partition to K Equal Sum Subsets | Backtracking with memoization (cross-listed with DP Pattern 15) |

---

## 14. Greedy

**Recognition signals:** "minimum number of," "maximum number of," a locally-optimal choice provably leads to a globally-optimal solution, often paired with sorting first.

**Core idea:** make the choice that looks best **right now**, without reconsidering — valid only when the problem has the "greedy-choice property" (often provable via an exchange argument).

| # | Problem | Notes |
|---|---|---|
| 1 | Jump Game | Greedy — track the furthest reachable index |
| 2 | Jump Game II | Greedy — track current window's farthest reach, count jumps |
| 3 | Gas Station | Greedy — if total gas ≥ total cost, a valid start exists; track running deficit |
| 4 | Candy | Two-pass greedy (left-to-right, then right-to-left) |
| 5 | Assign Cookies | Sort both arrays, greedily match smallest cookie to smallest sufficient child |
| 6 | Non-overlapping Intervals | (Cross-listed with Pattern 4) — sort by end, greedy count |
| 7 | Minimum Number of Arrows to Burst Balloons | (Cross-listed with Pattern 4) |
| 8 | Queue Reconstruction by Height | Sort by height descending, greedily insert at the "k" position |
| 9 | Task Scheduler | (Cross-listed with Pattern 10) — greedy + heap |
| 10 | Partition Labels | (Cross-listed with Pattern 1) — greedy interval merge |
| 11 | Boats to Save People | (Cross-listed with Pattern 1) |
| 12 | Two City Scheduling | Sort by cost difference, greedily assign |
| 13 | Minimum Platforms (classic, various judges) | Sort arrivals/departures, sweep-line greedy counting |
| 14 | Reorganize String | (Cross-listed with Pattern 10) |
| 15 | Best Time to Buy and Sell Stock II | Greedy — sum all positive day-to-day deltas |
| 16 | Lemonade Change | Greedy bill-making with a preference for using larger bills first |
| 17 | Remove Duplicate Letters | (Cross-listed with Pattern 6) — greedy + monotonic stack |
| 18 | Minimum Add to Make Parentheses Valid | Greedy balance-counter pass |

---

## 15. Bit Manipulation

**Recognition signals:** "without using extra space," "find the single/unique number," XOR properties, "count set bits," "power of two."

**Core idea:** exploit properties like `x ^ x = 0`, `x & (x-1)` clears the lowest set bit, and bit shifts to solve problems without arithmetic overflow or extra memory.

| # | Problem | Notes |
|---|---|---|
| 1 | Single Number | XOR all elements — pairs cancel out |
| 2 | Single Number II | Bit-counting per position (mod 3), or digital-logic trick |
| 3 | Single Number III | XOR everything, then split by a distinguishing bit |
| 4 | Number of 1 Bits | `n & (n-1)` repeatedly clears the lowest set bit |
| 5 | Counting Bits | DP + bit trick: `dp[i] = dp[i >> 1] + (i & 1)` |
| 6 | Power of Two | `n & (n-1) == 0` check |
| 7 | Power of Four | Power-of-two check + bit-position parity check |
| 8 | Reverse Bits | Bit-by-bit shift and accumulate |
| 9 | Bitwise AND of Numbers Range | Shift both bounds right until they match (common prefix) |
| 10 | Sum of Two Integers (no `+`/`-`) | XOR for sum, AND+shift for carry, loop until no carry |
| 11 | Missing Number | XOR-based alternative (cross-listed with Pattern 5) |
| 12 | Maximum XOR of Two Numbers in an Array | Trie over bit representations, greedily maximize from MSB down |

---

## 16. Math & Number Theory

**Recognition signals:** primes, GCD/LCM, modular arithmetic, combinatorics, "how many ways," direct mathematical formulas rather than search.

**Core idea:** recognize a closed-form or well-known algorithm (Sieve of Eratosthenes, Euclidean GCD, fast exponentiation) instead of brute-forcing.

| # | Problem | Notes |
|---|---|---|
| 1 | Count Primes | Sieve of Eratosthenes |
| 2 | Greatest Common Divisor of Strings | GCD applied to string "repetition units" |
| 3 | Fraction to Recurring Decimal | Long division simulation + cycle detection via remainder tracking |
| 4 | Pow(x, n) | Fast exponentiation (binary exponentiation) |
| 5 | Sqrt(x) | Binary search or Newton's method |
| 6 | Excel Sheet Column Number / Title | Base-26 conversion (careful: it's 1-indexed, not standard base conversion) |
| 7 | Roman to Integer / Integer to Roman | Direct symbol-value mapping + greedy subtraction |
| 8 | Happy Number | (Cross-listed with Pattern 3) — cycle detection on a numeric sequence |
| 9 | Ugly Number | Repeated division by 2, 3, 5 |
| 10 | Water and Jug Problem | Bézout's identity / GCD divisibility check |
| 11 | Random Pick with Weight | (Cross-listed with Pattern 8) — prefix sum + binary search |
| 12 | Permutation Sequence | Factorial number system (combinatorial direct construction, no brute-force generation) |

---

## 17. Trie

**Recognition signals:** "prefix," "autocomplete," "word dictionary," repeated prefix lookups across many words.

**Core idea:** a tree where each path from root represents a prefix; enables `O(L)` prefix/word lookups regardless of dictionary size (`L` = word length).

| # | Problem | Notes |
|---|---|---|
| 1 | Implement Trie (Prefix Tree) | The foundational data structure — build this first |
| 2 | Design Add and Search Words Data Structure | Trie + wildcard (`.`) DFS search |
| 3 | Word Search II | Trie + grid backtracking (cross-listed with Pattern 13) |
| 4 | Replace Words | Trie lookup for shortest matching prefix (root word) |
| 5 | Maximum XOR of Two Numbers in an Array | Trie over bits (cross-listed with Pattern 15) |
| 6 | Longest Word in Dictionary | Trie + DFS/BFS ensuring every prefix is also a valid word |
| 7 | Search Suggestions System | Trie (or sorted-array binary search) for prefix-based suggestions |
| 8 | Palindrome Pairs | Trie of reversed words + palindrome-check optimization |

---

## 18. Binary Tree Traversal & Recursion

**Recognition signals:** binary tree input, "traverse," "validate," "serialize," recursive structure with a natural base case at `null`.

**Core idea:** recursive DFS (pre/in/post-order) or iterative BFS (level order); most tree problems reduce to "what do I compute at this node, given what my children return?"

| # | Problem | Notes |
|---|---|---|
| 1 | Binary Tree Inorder/Preorder/Postorder Traversal | Foundational — know both recursive and iterative (stack-based) versions |
| 2 | Binary Tree Level Order Traversal | BFS with level-size tracking |
| 3 | Binary Tree Zigzag Level Order Traversal | BFS + alternating direction per level |
| 4 | Maximum Depth of Binary Tree | Simplest recursive template |
| 5 | Balanced Binary Tree | Recursive height check with early-exit on imbalance |
| 6 | Symmetric Tree | Recursive mirror-comparison of two subtrees |
| 7 | Same Tree | Recursive structural + value equality |
| 8 | Invert Binary Tree | Recursive swap of left/right children |
| 9 | Path Sum / Path Sum II | Recursive DFS with running sum, backtrack the path list |
| 10 | Validate Binary Search Tree | Recursive DFS passing down valid `(min, max)` bounds |
| 11 | Lowest Common Ancestor of a Binary Tree | Recursive — return the node itself if found in either subtree |
| 12 | Construct Binary Tree from Preorder and Inorder Traversal | Recursive split using inorder-index lookup |
| 13 | Serialize and Deserialize Binary Tree | Preorder DFS with null markers |
| 14 | Flatten Binary Tree to Linked List | Recursive/Morris-traversal in-place restructuring |
| 15 | Populating Next Right Pointers in Each Node | BFS level-linking, or O(1)-space recursive linking using already-set pointers |
| 16 | Binary Tree Right Side View | BFS, take the last node per level (or DFS with depth-first-seen tracking) |
| 17 | Count Complete Tree Nodes | Binary search exploiting complete-tree structure — better than O(n) |
| 18 | Vertical Order Traversal of a Binary Tree | DFS/BFS + coordinate bucketing, sort within buckets |

---

## 19. Binary Search Tree (BST) Specific

**Recognition signals:** explicitly a BST (not just any binary tree), "kth smallest," "closest value," ordering property can be exploited.

**Core idea:** an inorder traversal of a BST yields elements in **sorted order** — many BST problems reduce to exploiting this fact instead of a generic tree traversal.

| # | Problem | Notes |
|---|---|---|
| 1 | Validate Binary Search Tree | (Cross-listed with Pattern 18) |
| 2 | Kth Smallest Element in a BST | Inorder traversal, stop at the kth visit |
| 3 | Insert into a Binary Search Tree | Recursive descent following BST ordering |
| 4 | Delete Node in a BST | Recursive descent + successor/predecessor replacement on deletion |
| 5 | Convert Sorted Array to Binary Search Tree | Recursive midpoint selection for balance |
| 6 | Convert BST to Greater Tree | Reverse-inorder traversal with running sum |
| 7 | Lowest Common Ancestor of a BST | Exploit ordering — no need for full tree search like generic LCA |
| 8 | Two Sum IV - Input is a BST | Inorder traversal + two-pointer, or BST + hashset |
| 9 | Recover Binary Search Tree | Inorder traversal, find the two swapped nodes via out-of-order detection |
| 10 | Range Sum of BST | Pruned recursive traversal exploiting BST bounds |

---

## 20. Design (Data Structures)

**Recognition signals:** "design a data structure that supports...," explicit list of required operations and their target time complexities.

**Core idea:** combine known data structures (hashmap + linked list, hashmap + array, two heaps, etc.) to hit the required complexity for **every** operation simultaneously.

| # | Problem | Notes |
|---|---|---|
| 1 | LRU Cache | Hashmap + doubly linked list — the classic design template |
| 2 | LFU Cache | Hashmap + frequency buckets (each bucket itself an LRU-style list) |
| 3 | Design HashMap / HashSet | Bucket array + chaining — build the primitive from scratch |
| 4 | Min Stack | Auxiliary stack (or encoded value trick) tracking running minimum |
| 5 | Implement Queue using Stacks | Two stacks, amortized O(1) via lazy transfer |
| 6 | Implement Stack using Queues | Single/double queue with rotation trick |
| 7 | Design Circular Queue / Deque | Fixed-size array + modular index arithmetic |
| 8 | Insert Delete GetRandom O(1) | Array + hashmap of value→index, swap-with-last on delete |
| 9 | Design Twitter | Hashmap of user timelines + heap-based feed merge (ties to K-Way Merge) |
| 10 | All O`one Data Structure | Doubly linked list of frequency "buckets" + hashmap |
| 11 | Design Snake Game | Deque for snake body + hashset for O(1) collision checks |
| 12 | Time Based Key-Value Store | (Cross-listed with Pattern 8) — hashmap of sorted (timestamp, value) lists |

---

## 21. Prefix Sum / Difference Array

**Recognition signals:** "range sum query," "number of subarrays with sum X," repeated range queries/updates over a fixed array.

**Core idea:** precompute cumulative sums so any range sum becomes an `O(1)` lookup (`prefix[j] - prefix[i-1]`); for range **updates**, use a difference array instead (mark `+val` at start, `-val` after end).

| # | Problem | Notes |
|---|---|---|
| 1 | Range Sum Query - Immutable | The foundational template |
| 2 | Range Sum Query 2D - Immutable | 2D prefix sum |
| 3 | Subarray Sum Equals K | Prefix sum + hashmap counting occurrences of `prefix - k` |
| 4 | Continuous Subarray Sum | Prefix sum + modular arithmetic + hashmap of remainders |
| 5 | Subarray Sums Divisible by K | Same modular-remainder-hashmap trick as above |
| 6 | Product of Array Except Self | Prefix product from the left, suffix product from the right |
| 7 | Corporate Flight Bookings | Difference array over flight ranges |
| 8 | Car Pooling | (Cross-listed with Pattern 4) — difference array over pickup/dropoff |
| 9 | Range Addition | Direct difference-array template |
| 10 | Maximum Size Subarray Sum Equals k | Prefix sum + hashmap of first-seen index per prefix value |

---

## 22. Matrix-Specific Patterns

**Recognition signals:** 2D grid manipulation not covered by flood fill/graph patterns — rotation, spiral traversal, in-place transformation.

**Core idea:** careful index arithmetic; many of these are about **simulating** a described process precisely rather than a "clever" algorithmic insight.

| # | Problem | Notes |
|---|---|---|
| 1 | Rotate Image | In-place rotation via transpose + reverse (or layer-by-layer swap) |
| 2 | Spiral Matrix | Boundary-tracking simulation (top/bottom/left/right shrinking) |
| 3 | Spiral Matrix II | Same simulation, but generating values instead of reading them |
| 4 | Set Matrix Zeroes | Use first row/column as in-place markers to achieve O(1) extra space |
| 5 | Game of Life | In-place simulation using extra encoding bits to track old/new state simultaneously |
| 6 | Diagonal Traverse | Direction-flipping simulation along diagonals |
| 7 | Valid Sudoku | Row/column/box constraint checking with bitmasks or hashsets |
| 8 | Search a 2D Matrix II | (Cross-listed with Pattern 8) — staircase search |
| 9 | Toeplitz Matrix | Simple diagonal-comparison check |
| 10 | Rotting Oranges | (Cross-listed with Graph Pattern 3 — Multi-Source BFS) |

---

## 23. String Manipulation

**Recognition signals:** parsing, encoding/decoding, pattern matching not covered by DP (KMP-style or simulation-based rather than a 2D DP table).

**Core idea:** varies widely — often simulation, careful state-machine parsing, or a classical string algorithm (KMP, Rabin-Karp, Z-function).

| # | Problem | Notes |
|---|---|---|
| 1 | Implement strStr() | Naive scan, or KMP for O(n+m) guaranteed |
| 2 | Longest Common Prefix | Simple horizontal/vertical scan |
| 3 | Group Anagrams | Hashmap keyed by sorted-string or char-frequency signature |
| 4 | Valid Anagram | Frequency-count comparison |
| 5 | String to Integer (atoi) | Careful state-machine parsing (sign, digits, overflow, whitespace) |
| 6 | Zigzag Conversion | Simulate row assignment with a direction-flipping index |
| 7 | Multiply Strings | Manual digit-by-digit multiplication + carry propagation |
| 8 | Basic Calculator II | Stack-based expression evaluation respecting operator precedence |
| 9 | Compare Version Numbers | Split + segment-by-segment numeric comparison |
| 10 | Text Justification | Greedy word-packing per line + careful space distribution |
| 11 | Repeated Substring Pattern | KMP failure-function trick, or simple `(s+s)` containment check |
| 12 | Shortest Palindrome | KMP on `s + separator + reverse(s)` |
| 13 | Find All Anagrams in a String | (Cross-listed with Pattern 2) |
| 14 | Encode and Decode Strings | Length-prefix encoding scheme (handles arbitrary characters safely) |
| 15 | Minimum Window Substring | (Cross-listed with Pattern 2) |

---

## 24. Sweep Line / Advanced Intervals

**Recognition signals:** "maximum overlap at any point," events with start/end times, skyline-style silhouette problems.

**Core idea:** convert each interval into two **events** (a `+1` at start, a `-1` at end), sort all events by position, then sweep through accumulating the running count/state.

| # | Problem | Notes |
|---|---|---|
| 1 | Meeting Rooms II | (Cross-listed with Pattern 4) — sweep-line event counting |
| 2 | The Skyline Problem | Sweep-line + multiset/heap of active building heights |
| 3 | Car Pooling | (Cross-listed with Pattern 21) — sweep-line via difference array |
| 4 | My Calendar III | Sweep-line (or ordered map) tracking maximum simultaneous bookings |
| 5 | Number of Flowers in Full Bloom | Sweep-line via sorted start/end arrays + binary search per query |
| 6 | Employee Free Time | (Cross-listed with Pattern 4) |
| 7 | Data Stream as Disjoint Intervals | Ordered structure (TreeMap-equivalent) merging on insertion |
| 8 | Falling Squares | Sweep-line/segment-tree tracking max height over overlapping ranges |

---

## 25. Union-Find (Non-Graph Uses)

**Recognition signals:** grouping/merging queries **not** phrased as an explicit graph, "are these in the same group," dynamic connectivity over abstract entities (strings, coordinates, equations).

**Core idea:** identical machinery to the Union-Find used for MST (see the Graph notes), but applied to non-graph-flavored groupings.

*(Full implementation details and the core Union-Find class are in [`README_mst.md`](./README_mst.md) — this section only lists the **non-graph-framed** applications.)*

| # | Problem | Notes |
|---|---|---|
| 1 | Number of Islands II | Union-Find for dynamic (online) connectivity as land is added |
| 2 | Accounts Merge | Union-Find keyed by string identity |
| 3 | Satisfiability of Equality Equations | Union-Find with a two-pass equal/not-equal trick |
| 4 | Smallest String With Swaps | Union-Find groups indices, sort characters within each group |
| 5 | Most Stones Removed with Same Row or Column | Union-Find by shared row/column, answer = `stones - components` |
| 6 | Redundant Connection | (Cross-listed with Graph Pattern 5/6) |
| 7 | Sentence Similarity II | Union-Find over word-equivalence classes |
| 8 | Evaluate Division | Weighted Union-Find (or Floyd-Warshall — cross-listed with Graph Pattern 10) |

---

## 26. Divide and Conquer

**Recognition signals:** "count inversions," problems solvable by splitting in half, solving each half independently, and combining — distinct from DP because sub-problems **don't overlap**.

**Core idea:** split the problem into independent halves, solve each recursively, then do the (often non-trivial) work of **combining** the two results.

| # | Problem | Notes |
|---|---|---|
| 1 | Merge Sort (as a building block) | The foundational D&C algorithm — know it cold |
| 2 | Count of Smaller Numbers After Self | Merge-sort-based inversion counting |
| 3 | Reverse Pairs | Merge-sort-based, counting a relaxed inversion condition (`i<j, nums[i] > 2*nums[j]`) |
| 4 | Different Ways to Add Parentheses | D&C over operator positions, combine all sub-results |
| 5 | Maximum Subarray (D&C variant) | Split at midpoint, handle the "crossing" case explicitly (also solvable by Kadane's, Pattern 2) |
| 6 | The Skyline Problem (D&C variant) | Merge two skylines the same way merge-sort merges two sorted halves |
| 7 | Kth Largest Element in an Array (Quickselect) | D&C partition-based selection, O(n) average |
| 8 | Median of Two Sorted Arrays | (Cross-listed with Pattern 8) — D&C via binary search partitioning |

---

## 27. Segment Tree / Binary Indexed Tree (Fenwick Tree)

**Recognition signals:** "range query **and** range/point update," repeated queries where a simple prefix-sum array isn't enough because **updates** also need to be fast.

**Core idea:** a tree structure supporting both point-update and range-query in `O(log n)` — Fenwick Tree (BIT) is simpler to code for sums; Segment Tree is more general (supports min/max/gcd/custom merge operations too).

| # | Problem | Notes |
|---|---|---|
| 1 | Range Sum Query - Mutable | The direct template — BIT or Segment Tree for point-update + range-sum-query |
| 2 | Range Sum Query 2D - Mutable | 2D BIT/Segment Tree |
| 3 | Count of Smaller Numbers After Self | BIT over compressed value ranks (cross-listed with Pattern 8/26) |
| 4 | Count of Range Sum | BIT/Segment Tree over prefix sums, or merge-sort-based D&C |
| 5 | My Calendar III | Segment Tree tracking max overlap (cross-listed with Pattern 24) |
| 6 | Falling Squares | Segment Tree with lazy propagation for range-max-update queries |

---

## 28. Suggested Study Order

1. **Two Pointers** and **Sliding Window** — the two most foundational array patterns; almost every array interview question borrows from one of these.
2. **Binary Search (Classic)** — a small, precise template that shows up constantly; drill the exact boundary conditions (`<=` vs `<`, `mid` rounding) until they're automatic.
3. **Fast & Slow Pointers / Linked List** — a self-contained skill set; drill until reversal and cycle detection are muscle memory.
4. **Merge Intervals** and **Sweep Line** — closely related; master intervals before moving to the sweep-line generalization.
5. **Monotonic Stack** and **Monotonic Queue** — a distinctive but highly reusable idea (next-greater-element family); usually a "click" moment once you see 2-3 examples.
6. **Top K / Heap**, **Two Heaps**, **K-Way Merge** — group these together; they all lean on the same heap primitive with different framing.
7. **Backtracking** — the combinatorial-generation workhorse; master the "choose, explore, un-choose" template before tackling constraint-heavy variants (N-Queens, Sudoku).
8. **Greedy** — harder to systematize than other patterns since correctness proofs vary; build intuition by studying the exchange-argument reasoning behind each solved example.
9. **Binary Search on the Answer** — a satisfying "aha" pattern once Binary Search (Classic) is solid; always pair with writing the feasibility-check function first.
10. **Bit Manipulation**, **Math & Number Theory**, **Trie** — lower frequency individually, but each has a small number of "must-know" template problems.
11. **Binary Tree Traversal**, **BST-specific**, **Design** — foundational for any role; Design especially rewards having built LRU Cache and Min Stack from scratch at least once.
12. **Prefix Sum / Difference Array**, **Matrix-Specific**, **String Manipulation** — practical, frequently-tested "glue" patterns; not conceptually hard, but easy to fumble on edge cases under interview pressure.
13. **Union-Find (Non-Graph)**, **Divide and Conquer**, **Segment Tree/BIT** — the most "advanced" tier here; typically reserved for harder interviews or later rounds, but each is a highly reusable tool once learned.

---

## Cross-Reference — Full Pattern Collection

| Domain | Guide |
|---|---|
| Graph patterns (traversal, shortest path, MST, DAG, bipartite, Eulerian, etc.) | [`README_leetcode_patterns.md`](./problem_list_graph.md) |
| Dynamic Programming patterns (knapsack, LCS, LIS, interval DP, bitmask DP, etc.) | [`README_dp_patterns.md`](./problem_list_dp.md) |
| Everything else (this guide) | `README_master_patterns.md` |

Together, these three guides span the near-total surface area of what shows up in technical coding interviews.