#include <bits/stdc++.h>
using namespace std;
#define int long long

int dp[50][50][50][50];
vector<int> a;

int rec(int l, int r, int low, int high)
{
    if (l > r || low > high)
        return 0;
    if (dp[l][r][low][high] != -1)
        return dp[l][r][low][high];
    if (l == r)
        return (a[l] >= low && a[l] <= high);
    int ans = max(rec(l + 1, r, low, high), rec(l, r - 1, low, high));
    if (a[l] >= low && a[l] <= high)
        ans = max(ans, rec(l + 1, r, a[l], high) + 1);
    if (a[r] >= low && a[r] <= high)
        ans = max(ans, rec(l, r - 1, low, a[r]) + 1);

    swap(a[l], a[r]);
    if (a[l] >= low && a[l] <= high)
        ans = max(ans, rec(l + 1, r - 1, a[l], high) + 1);
    if (a[r] >= low && a[r] <= high)
        ans = max(ans, rec(l + 1, r - 1, low, a[r]) + 1);
    if (a[l] >= low && a[l] <= high && a[r] >= low && a[r] <= high)
        ans = max(ans, rec(l + 1, r - 1, a[l], a[r]) + 2);
    swap(a[l], a[r]);
    // cout << l << " (" << a[l] <<  ") : " << r << " (" << a[r] << ") || " << low << " : " << high << " => " << ans << endl;
    return dp[l][r][low][high] = ans;
}

int32_t main()
{

    int n;
    cin >> n;
    a.resize(n);
    map<int, int> comp;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        comp[a[i]] = 0;
    }
    int ind = 0;
    for (auto &x : comp)
        comp[x.first] = ind++;
    for (int i = 0; i < n; i++)
        a[i] = comp[a[i]];
    cout << endl;
    memset(dp, -1, sizeof(dp));
    cout << rec(0, n - 1, 0, ind - 1);

    return 0;
}