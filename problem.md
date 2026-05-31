# Zebra Coloring of Intervals

## Problem Statement

You are given an array $a$ of $n$ integers. A **zebra coloring** of a contiguous subarray $a[l..r]$ is an assignment of colors $c_l, c_{l+1}, \ldots, c_r$ where each $c_i \in \{0, 1\}$, such that:

1. No two adjacent elements have the same color (i.e., $c_i \neq c_{i+1}$ for all $l \le i < r$).
2. The **weighted parity sum** equals zero:

$$\sum_{i=l}^{r} (-1)^{c_i} \cdot a[i] \equiv 0 \pmod{2}$$

Define $f(l, r) = 1$ if a valid zebra coloring of $a[l..r]$ exists, and $0$ otherwise.

You are given $q$ queries. Each query gives you two integers $l$ and $r$, and asks you to compute:

$$\sum_{l \le x \le y \le r} f(x, y)$$

That is, count how many sub-subarrays $[x, y] \subseteq [l, r]$ admit a valid zebra coloring.

## Input Format

The first line contains two integers $n$ and $q$ ($1 \le n \le 10^5$, $1 \le q \le 10^5$).

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($0 \le a_i \le 10^9$).

The next $q$ lines each contain two integers $l$ and $r$ ($1 \le l \le r \le n$).

## Output Format

For each query, print a single integer — the answer on a separate line.

## Examples

### Example 1

**Input:**
```
5 3
1 2 3 4 5
1 5
2 4
3 3
```

**Output:**
```
6
2
0
```

### Example 2

**Input:**
```
4 2
0 0 0 0
1 4
2 3
```

**Output:**
```
10
3
```

## Notes

**Understanding f(l, r):**

A zebra coloring must alternate colors: only two patterns exist for $[l..r]$:
- Pattern A: $c_i = (i - l) \bmod 2$, giving colors $0, 1, 0, 1, \ldots$
- Pattern B: $c_i = (i - l + 1) \bmod 2$, giving colors $1, 0, 1, 0, \ldots$

The weighted parity sum condition becomes:
$$\sum_{i=l}^{r} (-1)^{c_i} \cdot a[i] \equiv 0 \pmod{2}$$

Since $(-1)^k \equiv 1 \pmod{2}$ for all integers $k$ (as $-1 \equiv 1 \pmod{2}$), both patterns yield the same condition:
$$\sum_{i=l}^{r} a[i] \equiv 0 \pmod{2}$$

Therefore $f(l, r) = 1$ if and only if the sum of $a[l..r]$ is **even**.

**For Example 1**, array $[1, 2, 3, 4, 5]$, query $[1,5]$:
- $f(2,2) = 1$ ($a_2 = 2$ even), $f(4,4) = 1$ ($a_4 = 4$ even)
- $f(1,3) = 1$ (sum $= 6$), $f(3,5) = 1$ (sum $= 12$)
- $f(1,4) = 1$ (sum $= 10$), $f(2,5) = 1$ (sum $= 14$)
- Total = 6

**Time Limit:** 2 seconds
**Memory Limit:** 256 MB
