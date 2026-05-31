/*
 * Zebra Coloring of Intervals - Optimal Solution
 *
 * Key insight: f(x,y) = 1 iff sum(a[x..y]) is even.
 * This reduces to: count pairs (x,y) with l<=x<=y<=r such that
 * prefix_parity[y] == prefix_parity[x-1].
 *
 * Let p[i] = (a[1] + a[2] + ... + a[i]) mod 2, p[0] = 0.
 * f(x,y) = 1 iff p[y] == p[x-1].
 *
 * Query answer = #{pairs (i,j): l-1 <= i < j <= r, p[i] == p[j]}
 *              = C(c0, 2) + C(c1, 2)
 * where c0 = #{k in [l-1,r]: p[k]=0}, c1 = #{k in [l-1,r]: p[k]=1}.
 *
 * Precompute ones[i] = #{k in [0,i]: p[k]=1}.
 * c1 = ones[r] - ones[l-2]  (with ones[-1] = 0)
 * c0 = (r - l + 2) - c1
 *
 * Time: O(n + q), Space: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // p[i] = prefix sum mod 2, p[0]=0
    // ones[i] = number of 1s in p[0..i]
    vector<int> ones(n + 1);
    int parity = 0;
    ones[0] = 0; // p[0] = 0, so initially count of 1s in p[0..0] is 0
    // Wait: ones[i] = #{k in [0..i]: p[k]=1}
    // p[0] = 0, so ones[0] = 0
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        parity ^= (a & 1);
        ones[i] = ones[i - 1] + parity;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        // Count 1s in p[l-1 .. r]
        // p[0..r] has ones[r] ones; p[0..l-2] has ones[l-2] ones (or 0 if l-2 < 0)
        long long c1 = ones[r] - (l >= 2 ? ones[l - 2] : 0);
        long long total = (long long)(r - l + 2); // number of indices l-1..r
        long long c0 = total - c1;

        long long ans = c0 * (c0 - 1) / 2 + c1 * (c1 - 1) / 2;
        cout << ans << "\n";
    }

    return 0;
}
