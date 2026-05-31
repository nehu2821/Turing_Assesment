/*
 * Zebra Coloring of Intervals - Brute Force Solution
 * O(n^2 * q) — for small inputs only, used to validate test cases.
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

    while (q--) {
        int l, r;
        cin >> l >> r;

        long long ans = 0;
        long long psum = 0;
        for (int x = l; x <= r; x++) {
            psum = 0;
            for (int y = x; y <= r; y++) {
                psum += a[y];
                if (psum % 2 == 0) ans++;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
