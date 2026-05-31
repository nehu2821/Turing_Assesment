/*
 * Qwen Attempt 3 - INCORRECT
 *
 * Approach: Identifies the prefix parity reduction but has an off-by-one
 * error in the range of the ones[] array. Specifically:
 * - Uses ones[l-1] instead of ones[l-2] when computing c1.
 * - This causes wrong answers for all queries where l > 1.
 *
 * Also fails to handle the l=1 edge case (underflow when accessing ones[-1]).
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> ones(n + 1, 0);
    int parity = 0;
    // ones[i] = number of 1s in prefix parities p[1..i]
    // BUG: should include p[0]=0 in the counting range for queries
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        parity ^= (a & 1);
        ones[i] = ones[i - 1] + parity;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        // BUG: should be counting p[l-1..r], which is ones[r] - ones[l-2]
        // and the range has (r-l+2) elements.
        // Instead uses ones[l-1] (wrong lower bound) and wrong range size.
        long long c1 = ones[r] - ones[l - 1]; // off by one: misses p[l-1]
        long long total = (long long)(r - l + 1); // wrong: should be r-l+2
        long long c0 = total - c1;

        long long ans = c0 * (c0 - 1) / 2 + c1 * (c1 - 1) / 2;
        cout << ans << "\n";
    }

    return 0;
}
