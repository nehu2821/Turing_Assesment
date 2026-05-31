/*
 * Qwen Attempt 2 - INCORRECT
 *
 * Approach: Correctly reduces to prefix parity, but uses the WRONG range.
 * Thinks the answer counts pairs (i, j) with l <= i <= j <= r where
 * p[i] == p[j] (using 1-indexed prefix array, forgetting p[0]).
 *
 * This misses the critical p[l-1] term. For query (l, r):
 * - Correct: count pairs from p[l-1..r] (total r-l+2 elements)
 * - Wrong:   count pairs from p[l..r]   (total r-l+1 elements)
 *
 * Additionally builds a "ones" prefix array incorrectly (off-by-one).
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // p[i] = prefix sum mod 2 for i in 1..n (WRONG: p[0] is excluded)
    vector<int> p(n + 1, 0);
    vector<int> ones(n + 1, 0); // ones[i] = count of 1s in p[1..i]
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        cur ^= (a & 1);
        p[i] = cur;
        ones[i] = ones[i - 1] + p[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        // WRONG: uses p[l..r] instead of p[l-1..r]
        long long c1 = ones[r] - ones[l - 1];
        long long total = r - l + 1; // should be r - l + 2
        long long c0 = total - c1;

        long long ans = c0 * (c0 - 1) / 2 + c1 * (c1 - 1) / 2;
        cout << ans << "\n";
    }
    return 0;
}
