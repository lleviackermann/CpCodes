#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve() {
    ll n, k;
    cin>>n>>k;
    vector<ll> start(n), end(n), val(n), dpfirst(1e6+2, 0), dpsecond(1e6+2, 0);
    for(auto &i : start) cin>>i;
    for(auto &i : end) cin>>i;
    for(auto &i : val) cin>>i;
    for(int i = 0; i < n; i++) {
        dpfirst[start[i]] += val[i];
        dpsecond[end[i]+1] += val[i];
    }
    ll ans = 0;
    ll temp = 0;
    ll prev = 0;
    for(int i = 1; i <= k; i++) {
        temp += dpfirst[i];
    }
    ans = max(ans, temp);
    for(int i = k+1; i <= 1e6; i++) {
        temp += dpfirst[i];
        prev += dpsecond[i-k];
        ans = max(ans, temp - prev);
    }
    cout<<ans<<endl;

}
int main () {
    int t = 1;
    // cin>>t;
    while(t--) {
        solve();
    }
}