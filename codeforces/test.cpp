#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int a;
                cin >> a;
                sum += a;
            }
        }
        int p;
        cin >> p;
        vector<pair<int, int>> pa;
        pa.push_back({0, 0});
        for (int i = 0; i < p; i++)
        {
            int a, b;
            cin >> a >> b;
            pa.push_back({a, b});
        }
        int k;
        cin >> k;
        int noof = sum / k;

        sort(pa.begin(), pa.end());
        int temp = 0;
        int flag = 0;
        for (int i = 1; i <= p; i++)
        {
            temp += (pa[i].first - pa[i - 1].second);
            if (temp >= noof)
            {
                flag = 1;
                cout << pa[i].first - (noof - temp) << endl;
                break;
            }
        }
        if(flag) continue;
        cout << -1 << endl;
    }
        return 0;
}