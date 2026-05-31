# Zebra Coloring of Intervals — Problemsetter Submission

## Quick Summary

A range-query problem over a 1D array. The core challenge is recognizing that a seemingly complex "zebra coloring with weighted parity" constraint collapses to a trivial parity condition, and then efficiently counting valid sub-intervals under range queries.

## Difficulty

**Codeforces Div2 C / Div1 A** — The problem is straightforward once the key insight is found, but the misleading surface structure (alternating colors, $(-1)^{c_i}$ weights, range queries) is likely to cause LLMs and many human contestants to over-engineer the solution.

## Key Insight

$(-1)^k \equiv 1 \pmod{2}$ for all integers $k$.  
This means the "weighted parity sum" reduces to just the plain element sum modulo 2, making both zebra patterns equivalent and collapsing $f(l,r)$ to simply `sum(a[l..r]) % 2 == 0`.

## File Guide

| File | Description |
|------|-------------|
| `problem.md` | Full problem statement |
| `solution.cpp` | Optimal O(n+q) solution |
| `solution.md` | Step-by-step solution explanation |
| `solution_bf.cpp` | Brute-force O(n²q) for testing |
| `generator.cpp` | Random test case generator |
| `idea.md` | Problem conception and rejected variants |
| `requirements.json` | Time/memory limits |
| `test_cases/` | 7 test cases (edge + stress) |
| `qwen/` | Three failing Qwen solution attempts |

## Building

```bash
g++ -O2 -o solution solution.cpp
g++ -O2 -o solution_bf solution_bf.cpp
g++ -O2 -o generator generator.cpp

# Run a test
./solution < test_cases/1.in

# Stress test
for seed in $(seq 1 500); do
  ./generator $seed 20 10 100 > /tmp/t.in
  diff <(./solution < /tmp/t.in) <(./solution_bf < /tmp/t.in) || echo "DIFF at seed $seed"
done
echo "Done"
```

## Why Qwen Fails

- **Attempt 1**: Checks if `wA(x,y) - wB(x,y) ≡ 0 (mod 2)` — always true, so counts all subarrays as valid.
- **Attempt 2**: Off-by-one on the prefix parity range (`p[l..r]` instead of `p[l-1..r]`), and wrong range length.
- **Attempt 3**: `ones[l-1]` instead of `ones[l-2]`, plus wrong `total = r-l+1` instead of `r-l+2`.
