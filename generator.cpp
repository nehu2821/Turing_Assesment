/*
 * Test Case Generator for Zebra Coloring of Intervals
 * Usage: ./generator <seed> <n> <q> <max_val>
 */
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    int seed   = (argc > 1) ? atoi(argv[1]) : 42;
    int n      = (argc > 2) ? atoi(argv[2]) : 10;
    int q      = (argc > 3) ? atoi(argv[3]) : 5;
    long long mx = (argc > 4) ? atoll(argv[4]) : 1000000000LL;

    mt19937_64 rng(seed);
    auto rval = [&](long long lo, long long hi) {
        return lo + (long long)(rng() % (hi - lo + 1));
    };

    cout << n << " " << q << "\n";
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << rval(0, mx);
    }
    cout << "\n";

    for (int i = 0; i < q; i++) {
        int l = (int)rval(1, n);
        int r = (int)rval(l, n);
        cout << l << " " << r << "\n";
    }

    return 0;
}
