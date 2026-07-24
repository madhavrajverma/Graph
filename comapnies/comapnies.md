# Rigorous 3-Month DSA Placement Preparation Plan
### Target Companies: Visa | Arista Networks | Qualcomm | Samsung R&D Noida | C-DOT

> **Part 1 of the full prep series — DSA only.** This is the rigorous, 3-month version: ~260 problems across 20 topics, organized into a 12-week plan. Once you clear this, we'll do Part 2 (CS Fundamentals: OS/CN/DBMS — critical for Arista/Qualcomm/Samsung/C-DOT), Part 3 (Aptitude), Part 4 (HR/Behavioral), Part 5 (Company-specific mocks).

## How to use this list
1. Don't jump to the solution. Attempt every problem for 20–25 min minimum first.
2. Read the **Hint** only if stuck.
3. After solving, explain your approach out loud in under 60 seconds — this is exactly what interviews test.
4. **⭐ = highest frequency** across these 5 companies — never skip these even if short on time.
5. Re-solve every ⭐ problem at least twice: once when you first learn it, once in your final revision week (Week 12).
6. Keep a personal log: date solved, time taken, whether you needed the hint. Revisit anything that took >30 min or needed a hint after 2 weeks (spaced repetition).

## Company pattern notes
- **Visa**: Arrays, Strings, HashMaps, LinkedList, Trees, OOP Design (LRU Cache, Parking Lot, Twitter design).
- **Arista Networks**: Bit Manipulation, Trie, Graphs (routing-like: Dijkstra, Union-Find), Stack/Queue, 1 Hard problem expected.
- **Qualcomm**: Arrays, Bit Manipulation, Recursion, LinkedList, memory-efficient/in-place solutions, sometimes C/C++ pointer questions.
- **Samsung R&D Noida**: Balanced across all topics — Trees, Graphs, DP, Strings; 2 DSA + 1 CS fundamentals question per round is common.
- **C-DOT**: Classical DSA (sorting, searching, recursion, basic-medium DP), more "explain your approach" conceptual style than pure speed-coding.

---

## 12-Week Roadmap

| Week | Focus | Goal |
|------|-------|------|
| 1 | Arrays & Strings basics + Sorting/Searching fundamentals | Build muscle memory on array manipulation, master binary search template |
| 2 | Two Pointers, Sliding Window, Hashing | Comfortable converting brute force O(n²) → O(n) |
| 3 | Linked List (all variants) | Pointer manipulation without bugs, first-try |
| 4 | Stack & Queue + Monotonic stack patterns | Recognize monotonic stack use-cases instantly |
| 5 | Recursion & Backtracking | Comfortable writing recursive tree of choices |
| 6 | Trees (Binary Tree/BST) | DFS/BFS traversal variants, tree construction problems |
| 7 | Heaps + Trie | Priority queue intuition, prefix tree design |
| 8 | Graphs Part 1 (BFS/DFS/Topo Sort) | Confident with graph traversal & cycle detection |
| 9 | Graphs Part 2 (Union-Find, Dijkstra, MST) | Weighted graph algorithms |
| 10 | Dynamic Programming Part 1 (1D + 2D DP) | Identify DP state and transition quickly |
| 11 | Dynamic Programming Part 2 (Knapsack variants, Advanced) + Greedy + Bit Manipulation | Handle DP-hard problems, greedy proofs |
| 12 | Full Revision + Mock Interviews + OOD/Design | Timed mock rounds, weak-area drilling |

---

## Table of Contents
1. [Sorting & Searching Fundamentals](#1-sorting--searching-fundamentals)
2. [Arrays & Strings](#2-arrays--strings)
3. [Two Pointers & Sliding Window](#3-two-pointers--sliding-window)
4. [Hashing](#4-hashing)
5. [Linked List](#5-linked-list)
6. [Stack & Queue](#6-stack--queue)
7. [Recursion & Backtracking](#7-recursion--backtracking)
8. [Binary Search (Advanced)](#8-binary-search-advanced)
9. [Trees (Binary Tree / BST)](#9-trees-binary-tree--bst)
10. [Heap / Priority Queue](#10-heap--priority-queue)
11. [Trie](#11-trie)
12. [Graphs Part 1 — Traversal & Topological Sort](#12-graphs-part-1--traversal--topological-sort)
13. [Graphs Part 2 — Union-Find, Shortest Path, MST](#13-graphs-part-2--union-find-shortest-path-mst)
14. [Dynamic Programming Part 1 — 1D & 2D](#14-dynamic-programming-part-1--1d--2d)
15. [Dynamic Programming Part 2 — Knapsack & Advanced](#15-dynamic-programming-part-2--knapsack--advanced)
16. [Greedy](#16-greedy)
17. [Bit Manipulation](#17-bit-manipulation)
18. [String Algorithms (Advanced)](#18-string-algorithms-advanced)
19. [Math & Number Theory](#19-math--number-theory)
20. [Design / OOP Questions](#20-design--oop-questions)
21. [Final Revision — Top 30 Starred](#21-final-revision--top-30-starred)

---

## 1. Sorting & Searching Fundamentals
*(Week 1 — C-DOT loves asking you to implement these from scratch)*

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 1 | Merge Sort (implement from scratch) | Medium | C-DOT, Samsung | https://leetcode.com/problems/sort-an-array/ | Divide array into halves recursively, merge two sorted halves using a temp array. |
| 2 | Quick Sort (implement from scratch) | Medium | C-DOT, Qualcomm | https://leetcode.com/problems/sort-an-array/ | Pick a pivot, partition array around it (Lomuto or Hoare scheme), recurse on both sides. |
| 3 | Sort Colors (Dutch National Flag) ⭐ | Medium | Visa, Arista | https://leetcode.com/problems/sort-colors/ | Three pointers: low, mid, high — swap based on whether `nums[mid]` is 0, 1, or 2. |
| 4 | Kth Largest Element (Quickselect) ⭐ | Medium | All 5 companies | https://leetcode.com/problems/kth-largest-element-in-an-array/ | Quickselect: partition like quicksort but recurse only into the side containing the k-th index. |
| 5 | Merge Sorted Array | Easy | Visa | https://leetcode.com/problems/merge-sorted-array/ | Fill from the back — compare the largest remaining elements of both arrays first. |
| 6 | Search a 2D Matrix | Medium | Samsung | https://leetcode.com/problems/search-a-2d-matrix/ | Treat 2D matrix as a flattened sorted 1D array; binary search using `mid / cols` and `mid % cols`. |
| 7 | Find First and Last Position of Element in Sorted Array ⭐ | Medium | All 5 companies | https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/ | Two separate binary searches — one biased to find leftmost occurrence, one for rightmost. |
| 8 | Search Insert Position | Easy | C-DOT | https://leetcode.com/problems/search-insert-position/ | Standard binary search; return `lo` when the element isn't found (that's the insert position). |

---

## 2. Arrays & Strings

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 9 | Two Sum ⭐ | Easy | Visa, Samsung, C-DOT | https://leetcode.com/problems/two-sum/ | HashMap storing `value → index`; check `target - current` before inserting. |
| 10 | Best Time to Buy and Sell Stock ⭐ | Easy | Visa, Qualcomm | https://leetcode.com/problems/best-time-to-buy-and-sell-stock/ | Track min price so far and max profit so far in one pass. |
| 11 | Best Time to Buy and Sell Stock II | Medium | Visa | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/ | Greedily add up every positive day-to-day price difference. |
| 12 | Best Time to Buy and Sell Stock III | Hard | Visa | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/ | DP with 4 states: buy1, sell1, buy2, sell2 — track best value for each state across the array. |
| 13 | Move Zeroes | Easy | Arista, Qualcomm | https://leetcode.com/problems/move-zeroes/ | Two-pointer: one tracks position to place next non-zero element. |
| 14 | Product of Array Except Self ⭐ | Medium | Visa, Samsung | https://leetcode.com/problems/product-of-array-except-self/ | Prefix product array + suffix product array; reuse output array for O(1) extra space. |
| 15 | Merge Intervals ⭐ | Medium | Visa, Samsung | https://leetcode.com/problems/merge-intervals/ | Sort by start time, merge overlapping intervals in a single pass. |
| 16 | Insert Interval | Medium | Visa | https://leetcode.com/problems/insert-interval/ | Three phases: add all intervals ending before new one starts, merge overlapping ones, add the rest. |
| 17 | Rotate Array | Medium | Qualcomm, Arista | https://leetcode.com/problems/rotate-array/ | Reverse whole array, then reverse first k and remaining n-k elements separately. |
| 18 | Rotate Image | Medium | Samsung | https://leetcode.com/problems/rotate-image/ | Transpose the matrix, then reverse each row (for 90° clockwise rotation). |
| 19 | Set Matrix Zeroes | Medium | Samsung | https://leetcode.com/problems/set-matrix-zeroes/ | Use first row/column of matrix itself as markers for O(1) space. |
| 20 | Spiral Matrix | Medium | Samsung, C-DOT | https://leetcode.com/problems/spiral-matrix/ | Maintain 4 boundaries (top, bottom, left, right), shrink after traversing each side. |
| 21 | Longest Common Prefix | Easy | C-DOT, Visa | https://leetcode.com/problems/longest-common-prefix/ | Compare characters column by column, or horizontal scan using first string as reference. |
| 22 | Valid Anagram | Easy | Visa, Samsung | https://leetcode.com/problems/valid-anagram/ | Frequency count with a 26-size array or HashMap. |
| 23 | Group Anagrams ⭐ | Medium | Visa, Samsung | https://leetcode.com/problems/group-anagrams/ | Sort each string as canonical key, group in a HashMap. |
| 24 | Longest Substring Without Repeating Characters ⭐ | Medium | All 5 companies | https://leetcode.com/problems/longest-substring-without-repeating-characters/ | Sliding window + HashSet/HashMap tracking last seen index of each char. |
| 25 | String Compression | Medium | Qualcomm | https://leetcode.com/problems/string-compression/ | Two pointers — read pointer and write pointer, count consecutive chars in place. |
| 26 | Reverse Words in a String | Medium | Arista | https://leetcode.com/problems/reverse-words-in-a-string/ | Split by whitespace, trim extras, reverse word list, join back. |
| 27 | Zigzag Conversion | Medium | Samsung | https://leetcode.com/problems/zigzag-conversion/ | Simulate row placement using a direction flag that flips at top/bottom rows. |
| 28 | Maximum Subarray (Kadane's) ⭐ | Easy | All 5 companies | https://leetcode.com/problems/maximum-subarray/ | `curr_sum = max(num, curr_sum + num)`, track global max. |
| 29 | Maximum Subarray Circular | Medium | Arista | https://leetcode.com/problems/maximum-sum-circular-subarray/ | Answer is either normal Kadane's max, or `totalSum - minSubarraySum` (using inverted Kadane's). |
| 30 | Next Permutation | Medium | Qualcomm, Arista | https://leetcode.com/problems/next-permutation/ | Find rightmost `i` where `nums[i]<nums[i+1]`, find rightmost element > `nums[i]` to its right, swap, reverse suffix. |
| 31 | First Missing Positive ⭐ | Hard | Qualcomm, Arista | https://leetcode.com/problems/first-missing-positive/ | Place each value `v` (1≤v≤n) at index `v-1` via in-place swapping, then scan for first mismatch. |
| 32 | Pascal's Triangle | Easy | C-DOT | https://leetcode.com/problems/pascals-triangle/ | Each row built from previous: `row[j] = prev[j-1] + prev[j]`. |
| 33 | Majority Element (Boyer-Moore) | Easy | Qualcomm | https://leetcode.com/problems/majority-element/ | Boyer-Moore voting: increment a counter for candidate, decrement for others, reset candidate at 0. |

---

## 3. Two Pointers & Sliding Window

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 34 | Valid Palindrome | Easy | C-DOT | https://leetcode.com/problems/valid-palindrome/ | Two pointers from both ends, skip non-alphanumeric characters, compare lowercase. |
| 35 | Container With Most Water ⭐ | Medium | Visa, Arista | https://leetcode.com/problems/container-with-most-water/ | Two pointers from both ends; move the one with smaller height inward. |
| 36 | 3Sum ⭐ | Medium | All 5 companies | https://leetcode.com/problems/3sum/ | Sort array, fix one element, two-pointer on rest for pairs summing to `-nums[i]`. |
| 37 | 4Sum | Medium | Samsung | https://leetcode.com/problems/4sum/ | Sort array, fix two elements with nested loops, two-pointer on remaining range. |
| 38 | Trapping Rain Water ⭐ | Hard | Arista, Qualcomm | https://leetcode.com/problems/trapping-rain-water/ | Precompute left-max/right-max arrays; water[i] = `min(leftMax[i],rightMax[i]) - height[i]`. Or two-pointer O(1) space. |
| 39 | Minimum Size Subarray Sum | Medium | Samsung | https://leetcode.com/problems/minimum-size-subarray-sum/ | Sliding window: expand right, shrink left while sum≥target, track min window length. |
| 40 | Longest Repeating Character Replacement | Medium | Visa | https://leetcode.com/problems/longest-repeating-character-replacement/ | Sliding window tracking max frequency char count; shrink if `windowLen - maxFreq > k`. |
| 41 | Sliding Window Maximum ⭐ | Hard | Arista, Samsung | https://leetcode.com/problems/sliding-window-maximum/ | Monotonic decreasing deque storing indices; front is always the max. |
| 42 | Find All Anagrams in a String | Medium | Visa | https://leetcode.com/problems/find-all-anagrams-in-a-string/ | Fixed-size sliding window comparing frequency counts vs pattern. |
| 43 | Minimum Window Substring ⭐ | Hard | Visa, Samsung | https://leetcode.com/problems/minimum-window-substring/ | Sliding window with a "need" and "have" frequency map; shrink window once all chars satisfied. |
| 44 | Sort Array By Parity | Easy | C-DOT | https://leetcode.com/problems/sort-array-by-parity/ | Two pointers from both ends, swap odd/even similar to Dutch flag idea. |

---

## 4. Hashing

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 45 | Subarray Sum Equals K ⭐ | Medium | All 5 companies | https://leetcode.com/problems/subarray-sum-equals-k/ | Prefix sum + HashMap of prefix sum frequencies; check `prefixSum - k`. |
| 46 | Top K Frequent Elements ⭐ | Medium | Visa, Samsung | https://leetcode.com/problems/top-k-frequent-elements/ | Frequency HashMap + min-heap of size k, or bucket sort by frequency. |
| 47 | Longest Consecutive Sequence ⭐ | Medium | Arista, Qualcomm | https://leetcode.com/problems/longest-consecutive-sequence/ | HashSet of all numbers; only start counting from numbers whose `num-1` isn't present. |
| 48 | Isomorphic Strings | Easy | C-DOT | https://leetcode.com/problems/isomorphic-strings/ | Two HashMaps for bidirectional character mapping consistency. |
| 49 | Contains Duplicate II | Easy | Qualcomm | https://leetcode.com/problems/contains-duplicate-ii/ | HashMap of last seen index; check `i - lastIndex <= k`. |
| 50 | Design HashMap | Easy | Visa, Arista | https://leetcode.com/problems/design-hashmap/ | Array of buckets (linked lists), own hash function via modulo. |
| 51 | Ransom Note | Easy | C-DOT | https://leetcode.com/problems/ransom-note/ | Frequency count of magazine letters, decrement while building ransom note, fail if any go negative. |
| 52 | Two Sum II - Input Array Is Sorted | Easy | Qualcomm | https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/ | Since sorted, use two pointers instead of a HashMap for O(1) space. |
| 53 | 4Sum II | Medium | Samsung | https://leetcode.com/problems/4sum-ii/ | Store all pairwise sums of first two arrays in a HashMap, look up complements from the other two. |

---

## 5. Linked List

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 54 | Reverse Linked List ⭐ | Easy | All 5 companies | https://leetcode.com/problems/reverse-linked-list/ | Iteratively track `prev, curr, next` pointers, reverse links one at a time. |
| 55 | Reverse Linked List II | Medium | Qualcomm | https://leetcode.com/problems/reverse-linked-list-ii/ | Find node before position `left`, reverse the sublist in place, reconnect both ends. |
| 56 | Linked List Cycle ⭐ | Easy | All 5 companies | https://leetcode.com/problems/linked-list-cycle/ | Floyd's slow/fast pointer — if they meet, there's a cycle. |
| 57 | Linked List Cycle II | Medium | Qualcomm, Arista | https://leetcode.com/problems/linked-list-cycle-ii/ | After slow/fast meet, reset one to head, move both one step; they meet at cycle start. |
| 58 | Merge Two Sorted Lists ⭐ | Easy | Visa, Samsung | https://leetcode.com/problems/merge-two-sorted-lists/ | Dummy node, compare heads, attach smaller each time. |
| 59 | Merge k Sorted Lists ⭐ | Hard | Visa, Samsung | https://leetcode.com/problems/merge-k-sorted-lists/ | Min-heap holding the head of each list, or divide-and-conquer pairwise merging. |
| 60 | Remove Nth Node From End of List | Medium | C-DOT | https://leetcode.com/problems/remove-nth-node-from-end-of-list/ | Two pointers with a gap of n nodes; when fast reaches end, slow is just before target. |
| 61 | Add Two Numbers | Medium | Qualcomm | https://leetcode.com/problems/add-two-numbers/ | Simulate digit-by-digit addition with carry, build new list node by node. |
| 62 | Copy List with Random Pointer ⭐ | Medium | Arista, Samsung | https://leetcode.com/problems/copy-list-with-random-pointer/ | Interleave cloned nodes with originals, fix random pointers, detach the two lists. |
| 63 | Reorder List | Medium | Samsung | https://leetcode.com/problems/reorder-list/ | Find middle (slow/fast), reverse second half, merge two halves alternately. |
| 64 | Palindrome Linked List | Easy | C-DOT | https://leetcode.com/problems/palindrome-linked-list/ | Find middle, reverse second half, compare both halves node by node. |
| 65 | Intersection of Two Linked Lists | Easy | Visa | https://leetcode.com/problems/intersection-of-two-linked-lists/ | Two pointers — redirect to other list's head when one reaches end; they meet at intersection. |
| 66 | Rotate List | Medium | Qualcomm | https://leetcode.com/problems/rotate-list/ | Connect tail to head (circular), find new tail at `(n - k%n - 1)`, break the link there. |
| 67 | Odd Even Linked List | Medium | Samsung | https://leetcode.com/problems/odd-even-linked-list/ | Maintain two separate chains (odd-indexed, even-indexed) then connect odd tail to even head. |
| 68 | Flatten a Multilevel Doubly Linked List | Medium | Arista | https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/ | DFS/stack — when a `child` pointer is found, recursively flatten it and splice it in before continuing `next`. |
| 69 | Design Linked List | Medium | Qualcomm | https://leetcode.com/problems/design-linked-list/ | Implement get/addAtHead/addAtTail/addAtIndex/deleteAtIndex manually with a dummy head node for simplicity. |

---

## 6. Stack & Queue

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 70 | Valid Parentheses ⭐ | Easy | All 5 companies | https://leetcode.com/problems/valid-parentheses/ | Push opening brackets to a stack; on closing bracket, pop and check match. |
| 71 | Min Stack ⭐ | Medium | Visa, Arista | https://leetcode.com/problems/min-stack/ | Second stack tracking min at each state, or store pairs (value, currentMin). |
| 72 | Evaluate Reverse Polish Notation | Medium | Qualcomm | https://leetcode.com/problems/evaluate-reverse-polish-notation/ | Stack; push numbers, pop two and apply operator on encountering one, push result. |
| 73 | Daily Temperatures ⭐ | Medium | Arista, Samsung | https://leetcode.com/problems/daily-temperatures/ | Monotonic decreasing stack of indices; pop and compute distance when warmer temp found. |
| 74 | Next Greater Element I & II | Easy/Medium | Arista | https://leetcode.com/problems/next-greater-element-i/ | Monotonic stack traversed right to left (circular traversal for II). |
| 75 | Largest Rectangle in Histogram ⭐ | Hard | Arista, Qualcomm | https://leetcode.com/problems/largest-rectangle-in-histogram/ | Monotonic increasing stack of indices; pop and compute area using popped height when smaller bar found. |
| 76 | Maximal Rectangle | Hard | Samsung | https://leetcode.com/problems/maximal-rectangle/ | Treat each row as a histogram base (heights built from consecutive 1s), apply Largest Rectangle in Histogram per row. |
| 77 | Implement Queue using Stacks | Easy | C-DOT | https://leetcode.com/problems/implement-queue-using-stacks/ | Two stacks — one for enqueue, one for dequeue; transfer only when dequeue stack is empty. |
| 78 | Implement Stack using Queues | Easy | C-DOT | https://leetcode.com/problems/implement-stack-using-queues/ | Use one queue; after pushing new element, rotate the queue so new element moves to front. |
| 79 | LRU Cache ⭐ | Medium | Visa, Arista, Samsung | https://leetcode.com/problems/lru-cache/ | HashMap (O(1) lookup) + Doubly Linked List (O(1) insert/delete at both ends). |
| 80 | Basic Calculator II | Medium | Qualcomm | https://leetcode.com/problems/basic-calculator-ii/ | Stack-based approach tracking the last operator seen; push/pop for `*` and `/` precedence handling. |
| 81 | Remove All Adjacent Duplicates in String | Easy | C-DOT | https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/ | Stack — push char; if it matches stack top, pop instead of pushing. |
| 82 | Decode String | Medium | Samsung | https://leetcode.com/problems/decode-string/ | Two stacks (or one stack of pairs) tracking counts and partial strings, push on `[`, pop and build on `]`. |
| 83 | Asteroid Collision | Medium | Arista | https://leetcode.com/problems/asteroid-collision/ | Stack simulation — push right-moving asteroids; on left-moving, resolve collisions by comparing sizes with stack top. |

---

## 7. Recursion & Backtracking

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 84 | Subsets ⭐ | Medium | All 5 companies | https://leetcode.com/problems/subsets/ | Branch into "include"/"exclude" at each index (standard backtracking template). |
| 85 | Subsets II | Medium | Visa | https://leetcode.com/problems/subsets-ii/ | Sort input first, skip duplicate elements at the same recursion depth to avoid duplicate subsets. |
| 86 | Permutations ⭐ | Medium | Qualcomm, Samsung | https://leetcode.com/problems/permutations/ | Swap-based backtracking, or a `used[]` boolean array. |
| 87 | Permutations II | Medium | Samsung | https://leetcode.com/problems/permutations-ii/ | Sort input, skip duplicate values at same recursion level using a `used[]` array check. |
| 88 | Combination Sum | Medium | Visa | https://leetcode.com/problems/combination-sum/ | Backtrack allowing reuse of same element; move to next index only after exhausting current. |
| 89 | Combination Sum II | Medium | Visa | https://leetcode.com/problems/combination-sum-ii/ | Sort input, skip duplicates at same recursion depth, each element used at most once. |
| 90 | Word Search | Medium | Samsung, Arista | https://leetcode.com/problems/word-search/ | DFS from every cell, mark visited temporarily, backtrack after exploring all 4 directions. |
| 91 | N-Queens | Hard | Qualcomm | https://leetcode.com/problems/n-queens/ | Place one queen per row, maintain sets for used columns/diagonals for fast pruning. |
| 92 | Generate Parentheses ⭐ | Medium | Visa, C-DOT | https://leetcode.com/problems/generate-parentheses/ | Recursion tracking open/close counts; add ')' only if `close < open`. |
| 93 | Palindrome Partitioning | Medium | Samsung | https://leetcode.com/problems/palindrome-partitioning/ | Backtrack trying every palindromic prefix, recurse on remaining substring. |
| 94 | Sudoku Solver | Hard | Qualcomm | https://leetcode.com/problems/sudoku-solver/ | Backtrack cell by cell, try digits 1-9, validate row/col/box before placing, undo on failure. |
| 95 | Letter Combinations of a Phone Number | Medium | Visa | https://leetcode.com/problems/letter-combinations-of-a-phone-number/ | Recursive backtracking mapping each digit to its letters, building string one digit at a time. |
| 96 | Restore IP Addresses | Medium | C-DOT | https://leetcode.com/problems/restore-ip-addresses/ | Backtrack trying segment lengths 1-3 at each of the 4 positions, validate range 0-255. |

---

## 8. Binary Search (Advanced)

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 97 | Binary Search (basic) | Easy | All 5 companies | https://leetcode.com/problems/binary-search/ | Standard `lo, hi, mid` template — must be automatic before your interview. |
| 98 | Search in Rotated Sorted Array ⭐ | Medium | All 5 companies | https://leetcode.com/problems/search-in-rotated-sorted-array/ | Determine which half is sorted, then decide which half the target could lie in. |
| 99 | Search in Rotated Sorted Array II | Medium | Qualcomm | https://leetcode.com/problems/search-in-rotated-sorted-array-ii/ | Same as above, but when `nums[lo]==nums[mid]==nums[hi]`, shrink both ends by 1 (handles duplicates). |
| 100 | Find Minimum in Rotated Sorted Array | Medium | Qualcomm | https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/ | Compare `mid` with `hi`; if `nums[mid]>nums[hi]` min is in right half, else left half (inclusive of mid). |
| 101 | Median of Two Sorted Arrays ⭐ | Hard | Visa, Samsung | https://leetcode.com/problems/median-of-two-sorted-arrays/ | Binary search partition point on smaller array so left/right half sizes and values balance. |
| 102 | Koko Eating Bananas ⭐ | Medium | Arista | https://leetcode.com/problems/koko-eating-bananas/ | Binary search on the answer (eating speed); check feasibility with a helper for each candidate speed. |
| 103 | Capacity To Ship Packages Within D Days | Medium | Qualcomm | https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/ | Binary search on capacity between max(weights) and sum(weights); simulate days needed each time. |
| 104 | Find Peak Element | Medium | C-DOT | https://leetcode.com/problems/find-peak-element/ | Binary search — move toward the side with the larger neighbor. |
| 105 | Split Array Largest Sum | Hard | Samsung | https://leetcode.com/problems/split-array-largest-sum/ | Binary search on the answer (max subarray sum); check feasibility of splitting into ≤m parts under that cap. |
| 106 | Allocate Minimum Number of Pages (GfG classic) | Hard | C-DOT | https://www.geeksforgeeks.org/allocate-minimum-number-pages/ | Binary search on the answer (max pages per student); same pattern as Split Array Largest Sum. |

---

## 9. Trees (Binary Tree / BST)

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 107 | Maximum Depth of Binary Tree | Easy | All 5 companies | https://leetcode.com/problems/maximum-depth-of-binary-tree/ | `1 + max(depth(left), depth(right))`. |
| 108 | Invert Binary Tree ⭐ | Easy | Visa, Arista | https://leetcode.com/problems/invert-binary-tree/ | Recursively swap left and right children at every node. |
| 109 | Diameter of Binary Tree ⭐ | Easy | All 5 companies | https://leetcode.com/problems/diameter-of-binary-tree/ | At each node, diameter = `leftHeight+rightHeight`; track global max while computing height. |
| 110 | Balanced Binary Tree | Easy | Samsung | https://leetcode.com/problems/balanced-binary-tree/ | Return -1 sentinel from height function if any subtree already unbalanced (early exit). |
| 111 | Binary Tree Level Order Traversal ⭐ | Medium | All 5 companies | https://leetcode.com/problems/binary-tree-level-order-traversal/ | BFS with a queue; process one level at a time tracking queue size each iteration. |
| 112 | Binary Tree Zigzag Level Order Traversal | Medium | Samsung | https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/ | Same BFS, reverse alternate levels before adding to result. |
| 113 | Validate Binary Search Tree ⭐ | Medium | All 5 companies | https://leetcode.com/problems/validate-binary-search-tree/ | Pass down a valid (min,max) range recursively; or in-order traversal checking strictly increasing. |
| 114 | Lowest Common Ancestor of a Binary Tree ⭐ | Medium | Visa, Samsung | https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/ | Recurse left/right; if both return non-null, current node is the LCA. |
| 115 | Lowest Common Ancestor of a BST | Medium | Qualcomm | https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/ | Use BST property: both smaller→go left, both larger→go right, else current is LCA. |
| 116 | Kth Smallest Element in a BST | Medium | C-DOT | https://leetcode.com/problems/kth-smallest-element-in-a-bst/ | In-order traversal gives sorted order; stop at the k-th visited node. |
| 117 | Binary Tree Right Side View | Medium | Arista | https://leetcode.com/problems/binary-tree-right-side-view/ | BFS taking last node per level; or DFS (right first) tracking max depth seen. |
| 118 | Construct Binary Tree from Preorder and Inorder Traversal ⭐ | Medium | Samsung, Visa | https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/ | First preorder element is root; find its inorder index to split left/right ranges recursively. |
| 119 | Serialize and Deserialize Binary Tree ⭐ | Hard | Arista, Samsung | https://leetcode.com/problems/serialize-and-deserialize-binary-tree/ | Preorder DFS with a null-marker (e.g. "#"), split by comma to deserialize recursively. |
| 120 | Path Sum II | Medium | Samsung | https://leetcode.com/problems/path-sum-ii/ | DFS maintaining current path list; add to result at a matching leaf, then backtrack. |
| 121 | Binary Tree Maximum Path Sum ⭐ | Hard | Visa, Samsung | https://leetcode.com/problems/binary-tree-maximum-path-sum/ | At each node compute max single-branch gain (clip negatives to 0) for parent use, but track global max using both branches. |
| 122 | Convert Sorted Array to Binary Search Tree | Easy | C-DOT | https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/ | Pick middle element as root recursively, recurse on left/right subarrays. |
| 123 | Populating Next Right Pointers in Each Node | Medium | Arista | https://leetcode.com/problems/populating-next-right-pointers-in-each-node/ | Use already-connected `next` pointers of the current level to connect the next level in O(1) space. |
| 124 | Vertical Order Traversal of a Binary Tree | Hard | Samsung | https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/ | BFS/DFS tracking (column, row, value) tuples; group by column, sort by row then value. |

---

## 10. Heap / Priority Queue

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 125 | Kth Largest Element in an Array ⭐ | Medium | All 5 companies | https://leetcode.com/problems/kth-largest-element-in-an-array/ | Min-heap of size k; top of heap is the answer. Or Quickselect for O(n) average. |
| 126 | Kth Largest Element in a Stream | Easy | Qualcomm | https://leetcode.com/problems/kth-largest-element-in-a-stream/ | Maintain a min-heap of size k across the entire stream; top is always the k-th largest. |
| 127 | Find Median from Data Stream ⭐ | Hard | Arista, Samsung | https://leetcode.com/problems/find-median-from-data-stream/ | Max-heap for lower half, min-heap for upper half, balance sizes after each insert. |
| 128 | Task Scheduler | Medium | Qualcomm | https://leetcode.com/problems/task-scheduler/ | Greedy with max-heap on frequency, or formula `(maxFreq-1)*(n+1) + count of max-freq tasks`. |
| 129 | K Closest Points to Origin | Medium | Samsung | https://leetcode.com/problems/k-closest-points-to-origin/ | Max-heap of size k based on distance, or Quickselect. |
| 130 | Reorganize String | Medium | Visa | https://leetcode.com/problems/reorganize-string/ | Max-heap by frequency; always place the most frequent char that isn't the same as the previous placed char. |
| 131 | Merge k Sorted Lists (revisit) | Hard | Visa | https://leetcode.com/problems/merge-k-sorted-lists/ | See #59. |
| 132 | Ugly Number II | Medium | C-DOT | https://leetcode.com/problems/ugly-number-ii/ | Maintain three pointers for multiples of 2, 3, 5 (DP approach), or use a min-heap. |

---

## 11. Trie

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 133 | Implement Trie (Prefix Tree) ⭐ | Medium | Arista, Samsung | https://leetcode.com/problems/implement-trie-prefix-tree/ | Each node holds a HashMap/array of 26 children + `isEnd` boolean flag. |
| 134 | Design Add and Search Words Data Structure | Medium | Arista | https://leetcode.com/problems/design-add-and-search-words-data-structure/ | Trie + DFS for wildcard `.` — try all children when `.` encountered. |
| 135 | Word Search II | Hard | Samsung | https://leetcode.com/problems/word-search-ii/ | Build a Trie of all words, DFS the grid while traversing the Trie simultaneously to prune early. |
| 136 | Longest Word in Dictionary | Medium | Arista | https://leetcode.com/problems/longest-word-in-dictionary/ | Insert all words into a Trie, then DFS keeping track of the longest path where every prefix is a valid word end. |
| 137 | Maximum XOR of Two Numbers in an Array | Medium | Qualcomm, Arista | https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/ | Build a binary Trie of bits (MSB to LSB); for each number greedily try the opposite bit to maximize XOR. |

---

## 12. Graphs Part 1 — Traversal & Topological Sort

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 138 | Number of Islands ⭐ | Medium | All 5 companies | https://leetcode.com/problems/number-of-islands/ | DFS/BFS from every unvisited land cell, mark visited, count traversal starts. |
| 139 | Max Area of Island | Medium | Samsung | https://leetcode.com/problems/max-area-of-island/ | Same as above but track area of each DFS/BFS component, keep max. |
| 140 | Clone Graph | Medium | Arista | https://leetcode.com/problems/clone-graph/ | DFS/BFS with HashMap mapping original node → cloned node to avoid re-cloning/cycles. |
| 141 | Course Schedule ⭐ | Medium | All 5 companies | https://leetcode.com/problems/course-schedule/ | Detect cycle in directed graph via Topological Sort (Kahn's BFS or DFS with recursion stack). |
| 142 | Course Schedule II | Medium | Arista, Qualcomm | https://leetcode.com/problems/course-schedule-ii/ | Same as above, return actual topological order via Kahn's BFS with in-degree array. |
| 143 | Pacific Atlantic Water Flow | Medium | Samsung | https://leetcode.com/problems/pacific-atlantic-water-flow/ | Reverse thinking — DFS from ocean borders inward, find cells reachable from both oceans. |
| 144 | Rotting Oranges | Medium | Samsung, Visa | https://leetcode.com/problems/rotting-oranges/ | Multi-source BFS from all initially rotten oranges simultaneously, track time level by level. |
| 145 | Word Ladder ⭐ | Hard | Arista | https://leetcode.com/problems/word-ladder/ | BFS treating each word as a node; generate neighbors by changing one letter, use word set for O(1) lookup. |
| 146 | Surrounded Regions | Medium | Samsung | https://leetcode.com/problems/surrounded-regions/ | DFS/BFS from border 'O's first to mark safe regions, flip all remaining unmarked 'O's to 'X'. |
| 147 | Walls and Gates | Medium | Arista | https://www.lintcode.com/problem/663/ | Multi-source BFS starting from all gates simultaneously, fill distances level by level. |
| 148 | Bipartite Graph Check | Medium | Qualcomm | https://leetcode.com/problems/is-graph-bipartite/ | BFS/DFS 2-coloring — if a neighbor has the same color as current node, graph isn't bipartite. |
| 149 | All Paths From Source to Target | Medium | C-DOT | https://leetcode.com/problems/all-paths-from-source-to-target/ | DFS with backtracking, since it's a DAG no visited-check needed, just track current path. |

---

## 13. Graphs Part 2 — Union-Find, Shortest Path, MST

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 150 | Graph Valid Tree | Medium | C-DOT | https://leetcode.com/problems/graph-valid-tree/ | Valid tree needs exactly n-1 edges and no cycles — use Union-Find or DFS for connectivity+cycle check. |
| 151 | Number of Connected Components in an Undirected Graph | Medium | Qualcomm | https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/ | Union-Find (DSU) — count distinct roots after processing all edges. |
| 152 | Redundant Connection | Medium | Arista | https://leetcode.com/problems/redundant-connection/ | Union-Find — the edge connecting two already-connected nodes is the redundant one. |
| 153 | Accounts Merge | Medium | Visa | https://leetcode.com/problems/accounts-merge/ | Union-Find on emails — union all emails belonging to the same account, then group by root parent. |
| 154 | Number of Provinces | Medium | Samsung | https://leetcode.com/problems/number-of-provinces/ | Union-Find on the adjacency matrix, or simple DFS/BFS counting connected components. |
| 155 | Network Delay Time ⭐ | Medium | Arista, Qualcomm | https://leetcode.com/problems/network-delay-time/ | Dijkstra's algorithm from source node; answer is max value in shortest-distance array. |
| 156 | Cheapest Flights Within K Stops | Medium | Qualcomm | https://leetcode.com/problems/cheapest-flights-within-k-stops/ | Modified Bellman-Ford — relax edges only k+1 times, using a distances copy each iteration. |
| 157 | Path With Minimum Effort | Medium | Arista | https://leetcode.com/problems/path-with-minimum-effort/ | Dijkstra's variant where "distance" is the max absolute height difference along a path, not sum. |
| 158 | Min Cost to Connect All Points ⭐ | Medium | Arista, Qualcomm | https://leetcode.com/problems/min-cost-to-connect-all-points/ | Minimum Spanning Tree — Prim's algorithm (with a min-heap) or Kruskal's (sort edges + Union-Find). |
| 159 | Alien Dictionary | Hard | Samsung | https://leetcode.com/problems/alien-dictionary/ | Build a graph of character-ordering constraints from adjacent word pairs, topological sort it. |
| 160 | Swim in Rising Water | Hard | Arista | https://leetcode.com/problems/swim-in-rising-water/ | Dijkstra's variant — priority queue by max elevation seen so far along the path. |
| 161 | Evaluate Division | Medium | Qualcomm | https://leetcode.com/problems/evaluate-division/ | Build a weighted graph from equations, DFS/BFS multiplying edge weights along the path for each query. |

---

## 14. Dynamic Programming Part 1 — 1D & 2D

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 162 | Climbing Stairs ⭐ | Easy | All 5 companies | https://leetcode.com/problems/climbing-stairs/ | Fibonacci: `dp[i]=dp[i-1]+dp[i-2]`. |
| 163 | Min Cost Climbing Stairs | Easy | Qualcomm | https://leetcode.com/problems/min-cost-climbing-stairs/ | `dp[i] = cost[i] + min(dp[i-1], dp[i-2])`. |
| 164 | House Robber ⭐ | Medium | Visa, Samsung | https://leetcode.com/problems/house-robber/ | `dp[i]=max(dp[i-1], dp[i-2]+nums[i])`. |
| 165 | House Robber II | Medium | Samsung | https://leetcode.com/problems/house-robber-ii/ | Circular array — solve House Robber I twice (excluding first house, excluding last house), take max. |
| 166 | Longest Increasing Subsequence ⭐ | Medium | Visa, Qualcomm | https://leetcode.com/problems/longest-increasing-subsequence/ | O(n²) DP first, then optimize with patience sorting + binary search on a tails array. |
| 167 | Longest Common Subsequence ⭐ | Medium | All 5 companies | https://leetcode.com/problems/longest-common-subsequence/ | 2D DP: `dp[i][j]=dp[i-1][j-1]+1` if chars match, else `max(dp[i-1][j], dp[i][j-1])`. |
| 168 | Edit Distance ⭐ | Hard | Samsung, Visa | https://leetcode.com/problems/edit-distance/ | 2D DP over insert/delete/replace operations at each character mismatch. |
| 169 | Word Break | Medium | Visa | https://leetcode.com/problems/word-break/ | `dp[i]`=true if some `dp[j]` is true and `s[j:i]` is in the dictionary. |
| 170 | Unique Paths | Medium | C-DOT | https://leetcode.com/problems/unique-paths/ | `dp[i][j]=dp[i-1][j]+dp[i][j-1]` — first row/col are all 1. |
| 171 | Unique Paths II (with obstacles) | Medium | C-DOT | https://leetcode.com/problems/unique-paths-ii/ | Same as above but set `dp[i][j]=0` at any obstacle cell. |
| 172 | Minimum Path Sum | Medium | Samsung | https://leetcode.com/problems/minimum-path-sum/ | Same grid DP pattern but take min instead of sum. |
| 173 | Decode Ways | Medium | Qualcomm | https://leetcode.com/problems/decode-ways/ | Like climbing stairs, but check validity of single/two-digit groupings at each step. |
| 174 | Maximum Product Subarray ⭐ | Medium | Visa, Arista | https://leetcode.com/problems/maximum-product-subarray/ | Track both running max AND running min (negative numbers can flip min into max). |
| 175 | Longest Palindromic Substring ⭐ | Medium | All 5 companies | https://leetcode.com/problems/longest-palindromic-substring/ | Expand-around-center for each index (and each gap) in O(n²). |
| 176 | Palindromic Substrings | Medium | Samsung | https://leetcode.com/problems/palindromic-substrings/ | Same expand-around-center technique, count instead of tracking longest. |
| 177 | Regular Expression Matching | Hard | Samsung | https://leetcode.com/problems/regular-expression-matching/ | 2D DP handling `.` (any char) and `*` (zero or more preceding char) separately. |
| 178 | Wildcard Matching | Hard | Samsung | https://leetcode.com/problems/wildcard-matching/ | Similar 2D DP to Regex Matching, `*` matches any sequence (including empty), `?` matches any single char. |
| 179 | Maximal Square | Medium | Samsung | https://leetcode.com/problems/maximal-square/ | `dp[i][j]=min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1` if cell is 1, tracking max side length. |
| 180 | Interleaving String | Medium | Qualcomm | https://leetcode.com/problems/interleaving-string/ | 2D DP: `dp[i][j]` true if `s3` prefix can be formed from `s1[:i]` and `s2[:j]` interleaved. |

---

## 15. Dynamic Programming Part 2 — Knapsack & Advanced

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 181 | Coin Change ⭐ | Medium | All 5 companies | https://leetcode.com/problems/coin-change/ | `dp[amount]=min(dp[amount], dp[amount-coin]+1)` for each coin — unbounded knapsack. |
| 182 | Coin Change II | Medium | Visa | https://leetcode.com/problems/coin-change-ii/ | `dp[j] += dp[j-coin]` iterating coins in outer loop to avoid counting permutations as distinct. |
| 183 | Partition Equal Subset Sum ⭐ | Medium | Qualcomm | https://leetcode.com/problems/partition-equal-subset-sum/ | If total sum even, check if a subset sums to `total/2` — classic 0/1 knapsack (subset-sum DP). |
| 184 | Target Sum | Medium | Samsung | https://leetcode.com/problems/target-sum/ | Convert to subset-sum problem: find subset with sum `(total+target)/2`. |
| 185 | Ones and Zeroes | Medium | Qualcomm | https://leetcode.com/problems/ones-and-zeroes/ | 2D 0/1 knapsack where "capacity" is a pair (m zeros, n ones) instead of a single weight. |
| 186 | Combination Sum IV | Medium | Visa | https://leetcode.com/problems/combination-sum-iv/ | `dp[target] += dp[target-num]` for each num — order matters here so it's like counting permutations. |
| 187 | Longest Increasing Path in a Matrix | Hard | Samsung | https://leetcode.com/problems/longest-increasing-path-in-a-matrix/ | DFS + memoization from each cell, only moving to strictly larger neighbors. |
| 188 | Burst Balloons | Hard | Samsung | https://leetcode.com/problems/burst-balloons/ | Interval DP — think about which balloon is burst LAST in a range, not first. |
| 189 | Matrix Chain Multiplication (GfG classic) | Hard | C-DOT | https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/ | Interval DP — try every split point k in range (i,j), minimize cost of multiplying left and right chains + merge cost. |
| 190 | Distinct Subsequences | Hard | Samsung | https://leetcode.com/problems/distinct-subsequences/ | 2D DP: `dp[i][j] = dp[i-1][j-1]+dp[i-1][j]` if chars match, else `dp[i-1][j]`. |
| 191 | Best Time to Buy and Sell Stock with Cooldown | Medium | Visa | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/ | State machine DP with 3 states: held, sold (cooldown next), rest. |
| 192 | Perfect Squares | Medium | Qualcomm | https://leetcode.com/problems/perfect-squares/ | `dp[n]=min(dp[n-i*i]+1)` for all `i*i<=n` — same unbounded knapsack pattern as Coin Change. |
| 193 | Integer Break | Medium | C-DOT | https://leetcode.com/problems/integer-break/ | `dp[n]=max(j*(n-j), j*dp[n-j])` for all splits j — try breaking vs not breaking the remainder. |
| 194 | Boolean Parenthesization (GfG classic) | Hard | C-DOT | https://www.geeksforgeeks.org/boolean-parenthesization-problem-dp-37/ | Interval DP tracking count of ways to make each sub-expression evaluate True and False separately. |

---

## 16. Greedy

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 195 | Jump Game ⭐ | Medium | Visa, Qualcomm | https://leetcode.com/problems/jump-game/ | Track farthest reachable index so far; if current index exceeds it, return false. |
| 196 | Jump Game II | Medium | Arista | https://leetcode.com/problems/jump-game-ii/ | Greedy BFS-style — track current level's farthest reach and next level's farthest reach. |
| 197 | Gas Station | Medium | C-DOT | https://leetcode.com/problems/gas-station/ | If total gas ≥ total cost, solution exists; track running tank, reset start whenever tank goes negative. |
| 198 | Non-overlapping Intervals | Medium | Samsung | https://leetcode.com/problems/non-overlapping-intervals/ | Sort by end time, greedily keep interval with earliest end, remove overlaps. |
| 199 | Meeting Rooms II ⭐ | Medium | Visa, Samsung | https://leetcode.com/problems/meeting-rooms-ii/ | Sort start/end times separately; min-heap of end times, or two-pointer over sorted arrays. |
| 200 | Partition Labels | Medium | Visa | https://leetcode.com/problems/partition-labels/ | Track the last occurrence index of each character; extend current partition until you reach that max last-index. |
| 201 | Minimum Number of Arrows to Burst Balloons | Medium | Arista | https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/ | Sort by end coordinate, greedily shoot an arrow at the end of the first unburst balloon's range. |
| 202 | Candy | Hard | Samsung | https://leetcode.com/problems/candy/ | Two passes: left-to-right ensuring increasing neighbor rule, right-to-left ensuring the same, take max at each index. |

---

## 17. Bit Manipulation

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 203 | Single Number ⭐ | Easy | Arista, Qualcomm | https://leetcode.com/problems/single-number/ | XOR all elements — duplicates cancel (`a^a=0`), leaving the unique number. |
| 204 | Single Number II | Medium | Qualcomm | https://leetcode.com/problems/single-number-ii/ | Track bit counts mod 3 across all numbers, or use two bitmask variables (ones, twos) state machine. |
| 205 | Single Number III | Medium | Qualcomm | https://leetcode.com/problems/single-number-iii/ | XOR all numbers to get `a^b`, find any set bit to split numbers into two groups, XOR each group separately. |
| 206 | Number of 1 Bits | Easy | Qualcomm | https://leetcode.com/problems/number-of-1-bits/ | `n & (n-1)` repeatedly clears the lowest set bit — count iterations. |
| 207 | Counting Bits | Easy | Qualcomm | https://leetcode.com/problems/counting-bits/ | `dp[i] = dp[i>>1] + (i&1)` — reuse previously computed bit counts. |
| 208 | Missing Number | Easy | Arista | https://leetcode.com/problems/missing-number/ | XOR all indices and all values together — missing number remains. |
| 209 | Reverse Bits | Easy | Qualcomm | https://leetcode.com/problems/reverse-bits/ | Shift result left, OR with last bit of n, shift n right, repeat 32 times. |
| 210 | Sum of Two Integers (no + or -) | Medium | Arista, Qualcomm | https://leetcode.com/problems/sum-of-two-integers/ | XOR for sum without carry, AND+shift for carry; repeat until carry is 0. |
| 211 | Bitwise AND of Numbers Range | Medium | Arista | https://leetcode.com/problems/bitwise-and-of-numbers-range/ | Right shift both m and n until equal (common prefix), shift back left. |
| 212 | Subsets using Bitmask | Medium | Qualcomm | https://leetcode.com/problems/subsets/ | Iterate `mask` from 0 to `2^n - 1`; each bit in mask decides whether to include that index. |
| 213 | Power of Two | Easy | C-DOT | https://leetcode.com/problems/power-of-two/ | A power of two has exactly one set bit — check `n>0 && (n&(n-1))==0`. |
| 214 | Gray Code | Medium | Qualcomm | https://leetcode.com/problems/gray-code/ | Formula: `gray(i) = i ^ (i >> 1)` generates the sequence directly. |

---

## 18. String Algorithms (Advanced)
*(Highly relevant for Arista/Qualcomm — pattern matching is core to networking/embedded software)*

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 215 | Implement strStr() / Find the Index of the First Occurrence in a String | Easy | All 5 companies | https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/ | Naive O(nm) first, then learn KMP's failure function (LPS array) for O(n+m). |
| 216 | KMP Algorithm — LPS Array (concept, implement from scratch) | Medium | Arista, Qualcomm | https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/ | Build the Longest Prefix-Suffix array first; use it to skip re-comparisons on mismatch. |
| 217 | Repeated String Match | Medium | Arista | https://leetcode.com/problems/repeated-string-match/ | Repeat string `a` enough times to cover length of `b`, then check substring/KMP match (try n and n+1 repeats). |
| 218 | Shortest Palindrome | Hard | Qualcomm | https://leetcode.com/problems/shortest-palindrome/ | KMP trick — build `s + "#" + reverse(s)`, the LPS value at the end tells you the longest palindromic prefix. |
| 219 | Longest Happy Prefix (Z-function/KMP application) | Hard | Arista | https://leetcode.com/problems/longest-happy-prefix/ | Same LPS array trick as KMP — the last value of the LPS array is your answer. |
| 220 | Rabin-Karp Algorithm (concept, implement from scratch) | Medium | C-DOT | https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/ | Use rolling hash to compare pattern hash with each window hash in O(1) per shift (average case). |
| 221 | Roman to Integer | Easy | C-DOT | https://leetcode.com/problems/roman-to-integer/ | Traverse left to right; if current value < next value, subtract, else add. |
| 222 | Integer to Roman | Medium | C-DOT | https://leetcode.com/problems/integer-to-roman/ | Greedy — use largest possible Roman value repeatedly from a precomputed value-symbol list. |
| 223 | Multiply Strings | Medium | Qualcomm | https://leetcode.com/problems/multiply-strings/ | Simulate manual multiplication digit by digit into a result array of size `len1+len2`. |
| 224 | Minimum Window Subsequence | Hard | Samsung | https://leetcode.com/problems/minimum-window-subsequence/ | Two-pointer: scan forward to find a match, then scan backward from match end to shrink and find true window start. |

---

## 19. Math & Number Theory

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 225 | Pow(x, n) ⭐ | Medium | Qualcomm, Arista | https://leetcode.com/problems/powx-n/ | Fast exponentiation (binary exponentiation) — halve the exponent each recursive call. |
| 226 | Sqrt(x) | Easy | Qualcomm | https://leetcode.com/problems/sqrtx/ | Binary search for the largest integer whose square ≤ x. |
| 227 | GCD/HCF and LCM (implement from scratch) | Easy | C-DOT, Qualcomm | https://www.geeksforgeeks.org/gcd-in-competitive-programming/ | Euclidean algorithm: `gcd(a,b) = gcd(b, a%b)` until b becomes 0. |
| 228 | Count Primes (Sieve of Eratosthenes) ⭐ | Medium | C-DOT, Qualcomm | https://leetcode.com/problems/count-primes/ | Mark multiples of each prime starting from p² as composite in a boolean array up to n. |
| 229 | Excel Sheet Column Number/Title | Easy | C-DOT | https://leetcode.com/problems/excel-sheet-column-number/ | Treat it as base-26 conversion, but note there's no "zero" digit (A=1 not 0). |
| 230 | Reverse Integer | Medium | Qualcomm | https://leetcode.com/problems/reverse-integer/ | Pop digits from the end using modulo/divide, check for 32-bit overflow before each push. |
| 231 | Happy Number | Easy | C-DOT | https://leetcode.com/problems/happy-number/ | Use Floyd's cycle detection (slow/fast) on the sequence of sum-of-squared-digits to detect infinite loops. |
| 232 | Factorial Trailing Zeroes | Medium | Qualcomm | https://leetcode.com/problems/factorial-trailing-zeroes/ | Count factors of 5 in `n!` (since factors of 2 always outnumber factors of 5): `n/5 + n/25 + n/125...`. |
| 233 | Power of Three | Easy | C-DOT | https://leetcode.com/problems/power-of-three/ | Keep dividing by 3 while divisible, or check if `n` divides the largest power of 3 that fits in an int. |

---

## 20. Design / OOP Questions
*(Very common at Visa & Arista — often a follow-up after DSA rounds)*

| # | Problem | Difficulty | Company Tag | LeetCode | Hint |
|---|---------|-----------|-------------|----------|------|
| 234 | LRU Cache (revisit) ⭐ | Medium | Visa, Arista | https://leetcode.com/problems/lru-cache/ | See #79 — HashMap + Doubly Linked List. |
| 235 | LFU Cache | Hard | Arista | https://leetcode.com/problems/lfu-cache/ | HashMap of key→node + HashMap of frequency→doubly linked list of nodes at that frequency. |
| 236 | Design Twitter | Medium | Visa | https://leetcode.com/problems/design-twitter/ | HashMap user→tweets and user→following; heap to merge k most recent tweets across followees. |
| 237 | Insert Delete GetRandom O(1) | Medium | Visa | https://leetcode.com/problems/insert-delete-getrandom-o1/ | ArrayList + HashMap (value→index); swap-with-last trick to delete in O(1). |
| 238 | Design Circular Queue | Medium | Qualcomm | https://leetcode.com/problems/design-circular-queue/ | Fixed-size array with `front`/`rear` pointers and modulo arithmetic to wrap around. |
| 239 | Design Hit Counter | Medium | Arista | https://leetcode.com/problems/design-hit-counter/ | Queue/circular buffer storing timestamps; pop expired hits (older than 300s) before each count query. |
| 240 | Design a Rate Limiter (conceptual, not on LeetCode) | Medium | Arista, Qualcomm | https://www.geeksforgeeks.org/rate-limiting-system-design/ | Discuss Token Bucket vs Sliding Window Log vs Fixed Window Counter approaches — very relevant for networking companies. |
| 241 | Design a Parking Lot (classic OOD) | Medium | Visa, C-DOT | https://www.geeksforgeeks.org/design-a-parking-lot-using-object-oriented-principles/ | Model classes: `ParkingLot`, `Level`, `Spot`, `Vehicle` (inheritance for Car/Bike/Truck); focus on clean OOP relationships. |
| 242 | Design an Elevator System (conceptual) | Medium | Qualcomm, Samsung | https://www.geeksforgeeks.org/design-elevator-system/ | Discuss state (idle/moving), request queue handling, and scheduling algorithm (SCAN/LOOK). |
| 243 | Time Based Key-Value Store | Medium | Samsung | https://leetcode.com/problems/time-based-key-value-store/ | HashMap of key → sorted list of (timestamp, value) pairs; binary search for the right timestamp on `get`. |

---

## 21. Final Revision — Top 30 Starred
*(If you only have your last week — revise these 30 problems. They cover the highest-frequency patterns across all 5 companies.)*

1. Two Sum — https://leetcode.com/problems/two-sum/
2. Maximum Subarray (Kadane's) — https://leetcode.com/problems/maximum-subarray/
3. 3Sum — https://leetcode.com/problems/3sum/
4. Longest Substring Without Repeating Characters — https://leetcode.com/problems/longest-substring-without-repeating-characters/
5. Merge Intervals — https://leetcode.com/problems/merge-intervals/
6. Trapping Rain Water — https://leetcode.com/problems/trapping-rain-water/
7. Reverse Linked List — https://leetcode.com/problems/reverse-linked-list/
8. Linked List Cycle — https://leetcode.com/problems/linked-list-cycle/
9. Merge k Sorted Lists — https://leetcode.com/problems/merge-k-sorted-lists/
10. LRU Cache — https://leetcode.com/problems/lru-cache/
11. Valid Parentheses — https://leetcode.com/problems/valid-parentheses/
12. Largest Rectangle in Histogram — https://leetcode.com/problems/largest-rectangle-in-histogram/
13. Binary Tree Level Order Traversal — https://leetcode.com/problems/binary-tree-level-order-traversal/
14. Validate Binary Search Tree — https://leetcode.com/problems/validate-binary-search-tree/
15. Lowest Common Ancestor of a Binary Tree — https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
16. Binary Tree Maximum Path Sum — https://leetcode.com/problems/binary-tree-maximum-path-sum/
17. Number of Islands — https://leetcode.com/problems/number-of-islands/
18. Course Schedule — https://leetcode.com/problems/course-schedule/
19. Network Delay Time (Dijkstra) — https://leetcode.com/problems/network-delay-time/
20. Min Cost to Connect All Points (MST) — https://leetcode.com/problems/min-cost-to-connect-all-points/
21. Kth Largest Element in an Array — https://leetcode.com/problems/kth-largest-element-in-an-array/
22. Find Median from Data Stream — https://leetcode.com/problems/find-median-from-data-stream/
23. Coin Change — https://leetcode.com/problems/coin-change/
24. Longest Common Subsequence — https://leetcode.com/problems/longest-common-subsequence/
25. Partition Equal Subset Sum — https://leetcode.com/problems/partition-equal-subset-sum/
26. Word Search II (Trie) — https://leetcode.com/problems/word-search-ii/
27. Search in Rotated Sorted Array — https://leetcode.com/problems/search-in-rotated-sorted-array/
28. Single Number — https://leetcode.com/problems/single-number/
29. Sum of Two Integers (bit manipulation) — https://leetcode.com/problems/sum-of-two-integers/
30. Implement Trie (Prefix Tree) — https://leetcode.com/problems/implement-trie-prefix-tree/

---

## What's next
Once you start working through this, tell me and we'll build:
- **Part 2**: CS Fundamentals (OS, CN, DBMS) — Arista/Qualcomm/Samsung/C-DOT specific concepts (routing, memory management, TCP/IP handshake, cache coherence, DNS, sockets — all very relevant given these are networking/chip companies)
- **Part 3**: Aptitude & Quant practice list
- **Part 4**: HR/Behavioral question bank + company-specific culture notes
- **Part 5**: Mock interview problem sets, one tailored per company, timed like a real round