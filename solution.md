# Solution Explanation: Zebra Coloring of Intervals

## Step 1: Simplify f(l, r)

A zebra coloring requires strict alternation of colors 0 and 1. For a subarray $[l..r]$, exactly two alternating patterns exist:
- **Pattern A**: $c_i = (i - l) \bmod 2$ → colors $0, 1, 0, 1, \ldots$
- **Pattern B**: $c_i = (i - l + 1) \bmod 2$ → colors $1, 0, 1, 0, \ldots$

For a valid coloring, the weighted parity sum must be zero modulo 2:
$$\sum_{i=l}^{r} (-1)^{c_i} \cdot a_i \equiv 0 \pmod{2}$$

**Key observation:** Since $-1 \equiv 1 \pmod{2}$, we have $(-1)^k \equiv 1 \pmod{2}$ for *all* integers $k$. Therefore:
$$\sum_{i=l}^{r} (-1)^{c_i} \cdot a_i \equiv \sum_{i=l}^{r} a_i \pmod{2}$$

This holds regardless of the coloring pattern chosen. So:

> $f(l, r) = 1$ **if and only if** $\sum_{i=l}^{r} a_i$ is **even**.

## Step 2: Reduce the Query

For a query $(l, r)$, we want:
$$\text{answer} = \#\{(x, y) : l \le x \le y \le r,\ f(x, y) = 1\}$$
$$= \#\{(x, y) : l \le x \le y \le r,\ \sum_{i=x}^{y} a_i \equiv 0 \pmod{2}\}$$

Define prefix parities: $p[0] = 0$, $p[i] = (a_1 + \cdots + a_i) \bmod 2$.

Then $\sum_{i=x}^{y} a_i \equiv 0 \pmod{2}$ iff $p[y] = p[x-1]$.

So we need:
$$\text{answer} = \#\{(i, j) : l - 1 \le i < j \le r,\ p[i] = p[j]\}$$

(Substituting $i = x - 1$, $j = y$; the constraint $i < j$ follows from $x \le y$ implies $x - 1 < y$.)

## Step 3: Count Equal-Parity Pairs

Let $c_0$ = number of indices $k \in [l-1, r]$ with $p[k] = 0$, and $c_1 = (r - l + 2) - c_0$ be the count of 1s.

The number of pairs with the same parity is:
$$\binom{c_0}{2} + \binom{c_1}{2} = \frac{c_0(c_0 - 1)}{2} + \frac{c_1(c_1 - 1)}{2}$$

## Step 4: Precompute for O(1) Queries

Let $\text{ones}[i] = \#\{k \in [0..i] : p[k] = 1\}$ (prefix count of 1s in the parity array).

Then for query $(l, r)$:
$$c_1 = \text{ones}[r] - \text{ones}[l-2] \quad (\text{with } \text{ones}[-1] = 0)$$
$$c_0 = (r - l + 2) - c_1$$
$$\text{answer} = \frac{c_0(c_0-1)}{2} + \frac{c_1(c_1-1)}{2}$$

## Complexity

- **Preprocessing**: $O(n)$ time and space to compute `ones[]`.
- **Per query**: $O(1)$.
- **Total**: $O(n + q)$ time, $O(n)$ space.

## Why Naive Approaches Fail

A natural (but slow) approach is to precompute prefix sums, then for each query iterate over all $O((r-l)^2)$ sub-intervals. This is $O(n^2)$ per query, giving $O(n^2 q)$ total — far too slow for $n = q = 10^5$.

A slightly smarter approach might precompute for each pair $(i, j)$ whether $f(i,j) = 1$ and build 2D prefix sums — but this requires $O(n^2)$ space and preprocessing, which also exceeds the limits.

The critical reduction is recognizing that the "zebra" constraint is a red herring: both alternating colorings yield the same parity equation, collapsing the problem to a simple range parity count.
