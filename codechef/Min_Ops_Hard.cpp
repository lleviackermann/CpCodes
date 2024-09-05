#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int tt;
    cin >> tt;
    for (int h = 1; h <= tt; h++) {
        int n, q;
        cin >> n >> q;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        vector<vector<int>> diff(n, vector<int>(2, 0));
        for (int i = 1; i < n; i++) {
            diff[i] = diff[i - 1];
            if (v[i] > v[i - 1]) diff[i][0] += v[i] - v[i - 1];
            else diff[i][1] += v[i - 1] - v[i];
        }
        for (int i = 0; i < q; i++) {
            int l, r, k;
            cin >> l >> r >> k;
            int pos = diff[r - 1][0] - diff[l - 1][0];
            int neg = diff[r - 1][1] - diff[l - 1][1];
            int d = max(pos, neg) - min(pos, neg);
            if (k < d) cout << min(pos, neg) + (d - k) << "\n";
            else if (k >= pos + neg) cout << "0\n";
            else cout << (pos + neg - k + 1) / 2 << "\n";
        }
    }
    return 0;
}