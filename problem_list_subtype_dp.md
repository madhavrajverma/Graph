# DP Interview Patterns — Full Subtype Breakdown

Every top-level pattern from the original guide, broken into subtypes the same way Grid DP was: **Subtype → Core Idea → Problems with one-line solutions.**

---

## 1. 1D Linear DP (Fibonacci-style)

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Pure counting recurrence | Ways to reach step N from a fixed small window | Climbing Stairs | `dp[i]=dp[i-1]+dp[i-2]`, ways to land on step i |
| Cost minimization | Same window, minimize instead of count | Min Cost Climbing Stairs | `dp[i]=cost[i]+min(dp[i-1],dp[i-2])` |
| Adjacency-exclusion | Can't pick two neighbors | House Robber | `dp[i]=max(dp[i-1], dp[i-2]+nums[i])` |
| Circular wrap-around | Adjacency rule but array wraps | House Robber II | Run House Robber twice, excluding first or last house, take max |
| Branching validity | Next state depends on 1 or 2 previous digits being valid | Decode Ways | `dp[i]=dp[i-1]` if single digit valid `+ dp[i-2]` if two-digit valid |
| Warm-up direct recurrence | Straight fixed-window recursion | Fibonacci Number / Tribonacci | `dp[i]=dp[i-1]+dp[i-2]` (or +dp[i-3]) directly |
| Transform-to-known-shape | Bucket sums collapse the problem into House Robber | Delete and Earn | Sum same-value nums into buckets, then run House Robber on buckets |

---

## 2. Kadane's / Max Subarray Family

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Pure Kadane's | Best run ending here vs restart | Maximum Subarray | `dp[i]=max(nums[i], dp[i-1]+nums[i])`, track global max |
| Dual max/min tracking | Negative numbers can flip min into max | Maximum Product Subarray | Track running `maxProd` and `minProd`, swap on negative number |
| Circular double-Kadane | Wrap-around sum needs two passes | Maximum Sum Circular Subarray | `max(normal Kadane's, total − minSubarray)`, handle all-negative edge case |
| Disguised Kadane's | Track running minimum instead of running sum | Best Time to Buy and Sell Stock | `profit=max(profit, price[i]-minPriceSoFar)` |
| Simultaneous max+min pass | Track best/worst prefix sums together | Maximum Absolute Sum of Any Subarray | Track running max-Kadane and min-Kadane in one pass, answer = `max(maxSum, -minSum)` |

---

## 3. 0/1 Knapsack

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Boolean reachability | Can we hit an exact target using each item once | Partition Equal Subset Sum | `dp[w]=dp[w] or dp[w-num]`, target = sum/2 |
| Sign-assignment reframing | Turn +/− assignment into a subset-sum target | Target Sum | Target = `(sum+S)/2`, count subsets summing to target |
| Difference minimization | Minimize gap between two partitioned sums | Last Stone Weight II | Find max achievable subset sum ≤ sum/2, answer = `sum - 2*that` |
| Multi-dimensional capacity | Two separate "weights" (zeros, ones) per item | Ones and Zeroes | `dp[z][o]=max(dp[z][o], dp[z-zeros][o-ones]+1)` |
| Multi-constraint knapsack | Two limited resources (people, profit floor) | Profitable Schemes | `dp[people][profit]` += ways, cap profit dimension at target |
| Value maximization classic | Classic reference case (not on LeetCode) | 0/1 Knapsack (textbook) | `dp[i][w]=max(skip item, take item)` |

---

## 4. Unbounded Knapsack / Coin Change

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Min-count minimization | Fewest coins to reach amount, coins reusable | Coin Change | `dp[a]=min(dp[a], dp[a-coin]+1)` for each coin |
| Counting combinations | Order doesn't matter — coin loop outside | Coin Change II | Loop coins outer, amounts inner: `dp[a]+=dp[a-coin]` |
| Counting permutations | Order matters — amount loop outside | Combination Sum IV | Loop amounts outer, coins inner: `dp[a]+=dp[a-coin]` |
| Squares-as-coins | Same shape, "coins" = perfect squares | Perfect Squares | `dp[n]=min(dp[n-i*i]+1)` for all i*i ≤ n |
| Windowed lookback | Cost only valid within a trailing day-window | Minimum Cost For Tickets | `dp[day]=min(dp[day-1]+cost1, dp[day-7]+cost7, dp[day-30]+cost30)` |

---

## 5. Longest Common Subsequence (LCS) Family

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Direct length LCS | Classic two-string common subsequence length | Longest Common Subsequence | Match → `dp[i][j]=dp[i-1][j-1]+1`, else `max(dp[i-1][j], dp[i][j-1])` |
| Derived edit-count | Deletions needed = leftover after LCS | Delete Operation for Two Strings | `len(A)+len(B)-2*LCS(A,B)` |
| Supersequence construction | Backtrack through LCS table to rebuild the string | Shortest Common Supersequence | Build LCS table, then walk it backward merging non-matching chars |
| Existence check | Boolean version — can characters interleave validly | Interleaving String | `dp[i][j] = (dp[i-1][j] and A[i]==C[i+j]) or (dp[i][j-1] and B[j]==C[i+j])` |
| Counting subsequences | Same table shape but counts ways, not length | Distinct Subsequences | Match → `dp[i][j]=dp[i-1][j-1]+dp[i-1][j]`, else `dp[i][j]=dp[i-1][j]` |
| Renamed LCS | Same recurrence, different framing | Uncrossed Lines | Identical to LCS — connecting lines without crossing = common subsequence |

---

## 6. Longest Increasing Subsequence (LIS) Family

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| O(n²) ending-here DP | LIS length ending exactly at i | Longest Increasing Subsequence (DP) | `dp[i]=max(dp[j]+1)` for j<i where `nums[j]<nums[i]` |
| O(n log n) patience sorting | Maintain tails array, binary search insertion point | Longest Increasing Subsequence (optimized) | Binary search `tails[]` for lower bound, replace or append |
| Counting LIS | Track length AND number of ways to reach that length | Number of Longest Increasing Subsequences | Maintain `dp[i]` (length) and `count[i]` (ways), merge counts on ties |
| 2D sort + 1D LIS reduction | Sort by dim 1, LIS on dim 2 handles the 2nd constraint | Russian Doll Envelopes | Sort by width asc (height desc on ties), then LIS on heights |
| Chain/greedy variant | Sort by end value, greedy pick | Maximum Length of Pair Chain | Sort by end, greedily extend chain (or DP with same shape) |
| Bitonic combination | LIS run forward and backward, combine at each index | Longest Bitonic Subsequence | `answer[i] = LIS_ending_at[i] + LDS_starting_at[i] - 1`, max over i |

---

## 7. Palindrome DP

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Boolean palindrome table | Expand outward by increasing substring length | Longest Palindromic Substring | `dp[i][j] = s[i]==s[j] and dp[i+1][j-1]`, track longest true span |
| Counting variant | Same table, just count true entries | Palindromic Substrings | Same recurrence as above, increment counter instead of tracking longest |
| Reversed-LCS reframing | Palindromic subsequence = LCS(s, reverse(s)) | Longest Palindromic Subsequence | Run LCS recurrence on `s` and `reverse(s)` |
| Min-cut partitioning | Combine palindrome table with 1D "min cuts up to i" | Palindrome Partitioning II | `cuts[i]=min(cuts[j]+1)` for all j where `s[j+1..i]` is a palindrome |
| Min insertion via LPS | Insertions needed = leftover after longest palindromic subsequence | Minimum Insertion Steps to Make a String Palindrome | `len(s) - LPS(s)` |

---

## 8. Interval DP

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Classic split-point | Try every split k inside range, combine sub-costs | Matrix Chain Multiplication (textbook) | `dp[i][j]=min over k of dp[i][k]+dp[k+1][j]+cost(i,k,j)` |
| "Last event" reframing | Think of k as last, not first, action in the interval | Burst Balloons | `dp[i][j]=max over k of dp[i][k-1]+dp[k+1][j]+nums[i-1]*nums[k]*nums[j+1]` (k = last burst) |
| Extra merge-count dimension | Track how many piles have been merged so far | Minimum Cost to Merge Stones | `dp[i][j][m]` = min cost merging `[i,j]` into m piles, extra loop over K-1 groupings |
| Operation-counting variant | dp counts turns/ops instead of a sum/cost | Strange Printer | `dp[i][j]=dp[i][j-1]+1`, or merge when `s[i]==s[k]` similar to matched chars |
| Extra matching-count state | State also tracks consecutive identical boxes attached | Remove Boxes | `dp[i][j][k]` = max points removing `[i,j]` with k extra boxes matching `s[j]` attached |

---

## 9. Grid / Path DP

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Path counting | Sum ways to reach cell from valid neighbors | Unique Paths | `dp[r][c]=dp[r-1][c]+dp[r][c-1]` |
| Path counting w/ obstacles | Same, but obstacle cells forced to 0 | Unique Paths II | Same recurrence, `dp[r][c]=0` if obstacle |
| Path optimization | Min/max value while moving, same neighbor structure | Minimum Path Sum | `dp[r][c]=grid[r][c]+min(dp[r-1][c], dp[r][c-1])` |
| Path optimization (triangular) | Same idea on a triangular index space | Triangle | `dp[r][c]=triangle[r][c]+min(dp[r+1][c], dp[r+1][c+1])`, bottom-up |
| Reverse grid DP | Constraint depends on the future path, compute backward | Dungeon Game | `dp[r][c]=max(1, min(dp[r+1][c], dp[r][c+1]) - dungeon[r][c])` |
| Shape/expansion DP | dp = size of shape ending here, min of neighbors | Maximal Square | `dp[r][c]=min(dp[r-1][c], dp[r][c-1], dp[r-1][c-1])+1` if cell is 1 |
| Multi-agent DP | Two positions collapse into one shared time dimension | Cherry Pickup | State `(step, col1, col2)` since row = step − col for both agents |

---

## 10. String Matching DP (Edit Distance Family)

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Classic 3-operation edit | Insert/delete/replace cost 1 each | Edit Distance | Match → `dp[i][j]=dp[i-1][j-1]`, else `1+min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])` |
| Wildcard transitions | `?` matches any char, `*` matches any sequence | Wildcard Matching | `*` → `dp[i][j]=dp[i-1][j] or dp[i][j-1]`; `?`/match → `dp[i][j]=dp[i-1][j-1]` |
| Regex transitions | `*` means zero-or-more of the *preceding* char | Regular Expression Matching | On `*`: `dp[i][j]=dp[i][j-2] or (charMatches and dp[i-1][j])` |
| Simplified early-exit check | Constant-space check instead of full table | One Edit Distance | Walk both strings once, allow exactly one mismatch/insert/delete then compare rest |

---

## 11. State Machine DP (Stock Trading Family)

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Unlimited transactions | 2-state machine (hold/not-hold), no limit | Best Time to Buy and Sell Stock II | `hold=max(hold, notHold-price)`, `notHold=max(notHold, hold+price)` |
| Cooldown 3-state | Add a "resting after sell" state | Best Time to Buy and Sell Stock with Cooldown | `hold=max(hold, rest-price)`, `sold=hold+price`, `rest=max(rest, sold_prev)` |
| Fee 2-state | Subtract fee once per completed transaction | Best Time to Buy and Sell Stock with Transaction Fee | `hold=max(hold, notHold-price)`, `notHold=max(notHold, hold+price-fee)` |
| Bounded transaction counter | State adds "which transaction number we're on" | Best Time to Buy and Sell Stock III | Track `buy1,sell1,buy2,sell2` explicitly across single pass |
| Generalized K transactions | Same as III but K is a parameter | Best Time to Buy and Sell Stock IV | `dp[k][hold]` over days: `dp[k][1]=max(dp[k][1], dp[k-1][0]-price)`, `dp[k][0]=max(dp[k][0], dp[k][1]+price)` |

---

## 12. Bitmask DP

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Reachability/partition bitmask | Track which elements used so far as a bitmask | Partition to K Equal Sum Subsets | `dp[mask]` = can this used-set be split into valid full groups so far |
| TSP-shaped bitmask+node | Classic bitmask + "currently at node" state | Shortest Path Visiting All Nodes | `dp[mask][node]=min(dp[mask^(1<<node)][prev]+dist)`, BFS/DP over `(mask,node)` |
| Two-group assignment bitmask | Bitmask over the smaller group, iterate assignments | Minimum Cost to Connect Two Groups of Points | `dp[i][mask]` = min cost connecting first i points of group1 with group2-subset `mask` covered |
| Row-based bitmask | Bitmask represents a row's seating/state, transition row→row | Maximum Students Taking Exam | `dp[row][mask]` valid if no adjacent seats conflict with `broken` pattern and previous row |
| Small-n permutation bitmask | Bitmask over people (not items), iterate over items per person | Number of Ways to Wear Different Hats to Each Other | `dp[hat][mask]` = ways to assign hats 1..hat covering people in `mask` |

---

## 13. Digit DP

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Position + used-digit bitmask | Track digit position, tight-bound flag, and digits used | Numbers With Repeated Digits | Count all numbers ≤ N minus count of numbers with all-unique digits |
| Complement counting | Count valid unique-digit numbers, subtract from total | Count Numbers with Unique Digits | `dp[position]` combinatorially counts unique-digit numbers directly (no repeated-digit complement needed) |
| Per-digit occurrence counting | Count occurrences of a target digit across the range | Number of Digit One | `dp[position][tight]` tracks count of digit "1" appearances, not just valid-number count |

---

## 14. Tree DP

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Include/exclude pair | DFS returns `(includeRoot, excludeRoot)` | House Robber III | `include = node.val + sum(childExclude)`, `exclude = sum(max(childInclude, childExclude))` |
| Global-max path tracking | Track best downward path, update global max at each node | Binary Tree Maximum Path Sum | `downPath = node.val + max(0, leftDown, rightDown)`; update `globalMax` with `node.val+leftDown+rightDown` |
| Height with side-effect | Return height, update diameter as a side-effect | Diameter of Binary Tree | `height(node) = 1+max(height(left), height(right))`, update `diameter = leftHeight+rightHeight` |
| Value-matching extension | Extend downward only while values match | Longest Univalue Path | Extend `leftPath`/`rightPath` only if child value == node value, else reset to 0 |
| 3-state greedy hybrid | Node is covered / has camera / needs coverage | Binary Tree Cameras | Place camera if any child needs coverage; propagate covered/needs-coverage upward |

---

## 15. Partition / Subset-Sum Family

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Two-subset boolean | Can we hit sum/2 exactly | Partition Equal Subset Sum | Same as 0/1 Knapsack boolean reachability (cross-listed) |
| K-subset bitmask/backtracking | Track used elements, try to fill K buckets to target | Partition to K Equal Sum Subsets | `dp[mask]` = remainder progress; backtrack/memoize on bitmask |
| Fixed K=4 special case | Same as K-subset with K hardcoded to 4 | Matchsticks to Square | Same bitmask/backtracking DP, target = sum/4 |
| Binary search + feasibility | Binary search the answer, greedily check feasibility | Split Array Largest Sum | Binary search on max-subarray-sum value, greedily count required splits |

---

## 16. Game Theory DP

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Classic alternating interval DP | Current player's best score minus opponent's optimal response | Predict the Winner | `dp[i][j]=max(nums[i]-dp[i+1][j], nums[j]-dp[i][j-1])` |
| Same shape, renamed | Identical recurrence, different flavor text | Stone Game | Same as Predict the Winner; first player wins iff `dp[0][n-1] > 0` |
| Extra move-count dimension | Add "M" (moves allowed this turn) to the state | Stone Game II | `dp[i][M]` = best score from suffix i with move-budget M, opponent gets the rest |
| Bitmask + turn parity | Track used numbers as bitmask, parity decides whose turn | Can I Win | `dp[mask]` = can current player force a win from this used-set, check win condition each pick |

---

## 17. DP on DAG (Graph-Flavored DP)

| Subtype | Core Idea | Problem | One-liner Solution |
|---|---|---|---|
| Implicit DAG longest path | Grid edges only go to strictly increasing neighbors | Longest Increasing Path in a Matrix | `dp[r][c]=1+max(dp[neighbor])` for neighbors with greater value, memoize |
| Step-budget path counting | Count paths in an implicit DAG with a moves-remaining dimension | Out of Boundary Paths | `dp[step][r][c]=sum(dp[step-1][neighbor])`, paths that exit count |
| State-augmented implicit DAG | Node = (position, extra parameter) rather than position alone | Frog Jump | `dp[(position,jumpSize)]` = reachable if `(position-jumpSize, jumpSize-1/0/+1)` reachable |

---

## Meta-Skill Reminder

For every subtype above, the same two questions unlock the whole row:

1. **What does `dp[state]` represent, precisely?**
2. **What are the valid transitions in, and what's the base case?**

The subtype is just a hint for *how big and how shaped* that state needs to be — one variable, two indices, an interval, a bitmask, or a pair returned from recursion.