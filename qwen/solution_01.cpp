/*
 * Qwen Attempt 1 - INCORRECT
 *
 * Approach: Tries to track the two zebra coloring patterns separately using
 * prefix sums. Believes that pattern A and pattern B can give different parity
 * outcomes, so defines f(x,y) = 1 iff the DIFFERENCE of the two pattern sums
 * is divisible by 2 (thinking this means they "agree"). 
 *
 * Core error: Computes diff = wA(x,y) - wB(x,y) mod 2 and checks diff==0,
 * but wA - wB = 2*wA so diff is always 0 mod 2. This makes every subarray
 * count as valid, giving ans = (r-l+1)*(r-l+2)/2 for every query. Wrong!
 *
 * Also has O(n) per query (still fast enough, but wrong answers).
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // patA[i] = prefix sum of (-1)^{i-1} * a[i] starting from index 1
    // (global pattern, not subarray-relative)
    vector<long long> patA(n + 1, 0), patB(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long signA = ((i % 2) == 1) ? 1 : -1;
        long long signB = -signA;
        patA[i] = patA[i - 1] + signA * a[i];
        patB[i] = patB[i - 1] + signB * a[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        long long ans = 0;
        // O(n) per query: iterate starting points, use prefix sums
        for (int x = l; x <= r; x++) {
            for (int y = x; y <= r; y++) {
                long long wA = patA[y] - patA[x - 1];
                long long wB = patB[y] - patB[x - 1];
                // f(x,y) = 1 iff wA - wB ≡ 0 (mod 2)
                // (wrong: this is always true since wA - wB = 2*wA)
                long long diff = ((wA - wB) % 2 + 2) % 2;
                if (diff == 0) ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
