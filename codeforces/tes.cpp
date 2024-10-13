#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> shop(n);
    for(auto &i : shop) cin >> i.first >> i.second;
    sort(shop.begin(), shop.end(), [&](pair<ll, ll>& fir, pair<ll, ll>& sec) {
        if(fir.first == sec.first) return fir.second < sec.second;
        return fir.first < sec.first;
    }); 
    ll low = 0, high = 1e15;
    ll ans = 0;
    while(low <= high) {
        ll mid = (low + high) / 2;
        ll st = shop[0].first;
        int flag = 1;
        for(int i = 1; i < n; i++) {
            if(st + mid > shop[i].second) {
                flag = 0;
                break;
            }
            st = max(st + mid, shop[i].first);
        }
        if(flag) ans = mid, low = mid + 1;
        else high = mid - 1;
    }
    cout << ans << endl;
    // for()
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}