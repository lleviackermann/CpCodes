#include <bits/stdc++.h>

#define ll long long
using namespace std;

void solve()
{
    ll n;
    cin >> n;
    vector<ll> arr(n), val(n);
    for(auto &i : arr) cin>>i;
    for(auto &i : val) cin>>i;
    for (int i = 1; i < n; i++)
        val[i] += val[i - 1];
    ll avg;
    cin >> avg;
    for (int i = 0; i < n; i++)
        arr[i] -= avg;
    for (int i = 1; i < n; i++)
        arr[i] += arr[i - 1];
    map<ll, ll> m;
    vector<ll> dp(n, -1e9);
    if (arr[0] == 0)
    {
        dp[0] = val[0];
    }
    m[arr[0]] = 1;
    ll ans = 0;
    ans = max(ans, dp[0]);
    for (int i = 1; i < n; i++)
    {
        ll temp = m[arr[i]];
        temp--;
        if (temp != -1)
        {
            ll x = val[i] - val[temp];
            dp[i] = max(dp[temp], 0ll) + x;
        }
        m[arr[i]] = i + 1;
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
}