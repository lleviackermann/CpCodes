#include <bits/stdc++.h>

using namespace std;

bool cmp(int x, int y, int z)
{
    if (z > 30)
        return 1;
    return x < y * (1LL << z);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        int mod = 1e9 + 7;
        vector<pair<int, int>> val;
        long long ans = 0;
        vector<long long> pow2(n * 32 + 1);
        pow2[0] = 1;
        for (int i = 1; i <= n * 32; i++)
            pow2[i] = pow2[i - 1] * 2 % mod;
        for (int i = 0; i < n; i++)
        {
            int x = a[i], y = 0;
            while (x % 2 == 0)
                x /= 2, y++;
            while (!val.empty() && cmp(val.back().first, x, y))
            {
                ans = (ans - val.back().first * pow2[val.back().second] % mod + mod) % mod;
                ans = (ans + val.back().first) % mod;
                y += val.back().second;
                val.pop_back();
            }
            val.push_back({x, y});
            ans = (ans + val.back().first * pow2[val.back().second]) % mod;
            cout << ans << ' ';
        }
        cout << '\n';
    }
    return 0;
}