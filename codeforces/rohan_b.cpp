#include <bits/stdc++.h>
using namespace std;
#define ll long long
void solve()
{
    ll tot, n;
    cin >> tot >> n;
    vector<ll> prd(n), coll(n);
    for (auto &i : prd)
        cin >> i;
    for (auto &i : coll)
        cin >> i;
    ll low = 1, high = 1e18+10;
    ll ans = high;
    auto binary = [&](ll mid)
    {
        ll sum = 0;
        for (int i = 0; i < n; i++)
        {
            if(sum >= tot) return true;
            sum += prd[i];
            sum += ((mid - 1) / (coll[i])) * prd[i];
        }
        return sum >= tot;
    };
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (binary(mid))
            ans = mid, high = mid - 1;
        else
            low = mid + 1;
    }
    cout << ans << endl;
}
int main()
{
    int t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}