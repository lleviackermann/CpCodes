#include <bits/stdc++.h>
using namespace std;


int main() {
    int n;
    cin >> n;

    vector <int> store;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        store.push_back(x);
    }

    sort(store.begin(), store.end());
    int ans = INT32_MAX;
    for (int i = 0; i < n; i++) {
        int lim = store[i] + n;

        int pos = lower_bound(store.begin(), store.end(), lim) - store.begin();
        if (pos < n) {
            if (store[pos] != lim) {
                pos--;
            }
        }

        ans = min(ans, n - (pos - i));

        lim = store[i] - n;
        pos = lower_bound(store.begin(), store.end(), lim) - store.begin();

        ans = min(ans, n - (i - pos));
    }

    cout << ans << endl;

    return 0;
}