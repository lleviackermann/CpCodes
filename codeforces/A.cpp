#include <bits/stdc++.h>
#define ll long long
using namespace std;


void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    map<string, int> mapping;
    // int cnt = -1;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        mapping[s] = i;
    }

    if (m == 1)
    {
        vector<pair<int, int>> store;
        while (q--)
        {
            int sign, uid;
            string node;
            cin >> sign >> node >> uid;
            if (sign == 1)
            {
                if (store.size())
                    cout << "false" << endl;
                else
                {
                    store.push_back({mapping[node], uid});
                    cout << "true" << endl;
                }
            }
            else
            {
                if (store.size() && store[0].first == mapping[node] && store[0].second == uid)
                {
                    cout << "true" << endl;
                    store.pop_back();
                }
                else
                {
                    cout << "false" << endl;
                }
            }
        }
    }
    else
    {
        ll level = m;
        ll pa = 0;
        vector<ll> parent(n, -1);
        ll tem = 1;
        while (tem < n)
        {
            ll lev = tem + level;
            int cnt = 0;
            while (tem < lev && tem < n)
            {
                cnt++;
                parent[tem] = pa;
                tem++;
                if (cnt == m)
                    pa++, cnt = 0;
            }
            level *= m;
        }
        int no_flag = -1e9, des_flag = -1e9 + 10;
        vector<int> uid_store(n, no_flag);
        while (q--)
        {
            int sign, uid;
            string node;
            cin >> sign >> node >> uid;
            int maped = mapping[node];
            if (sign == 1)
            {
                bool pa_flag = false;
                int mp = maped;
                while (mp != -1)
                {
                    if (uid_store[mp] != no_flag  && uid_store[mp] != des_flag) {
                        pa_flag = true;
                        break;
                    }
                        
                    mp = parent[mp];
                }
                if (uid_store[maped] != no_flag || pa_flag)
                {
                    cout << "false" << endl;
                }
                else
                {
                    mp = maped;
                    while (mp != -1)
                    {
                        uid_store[mp] = des_flag;
                        mp = parent[mp];
                    }
                    uid_store[maped] = uid;
                    cout << "true" << endl;
                }
            }
            else
            {
                if (uid_store[maped] == uid)
                {
                    // uid_store[maped] = no_flag;
                    int x = maped;
                    while (maped != -1)
                    {
                        uid_store[maped] = no_flag;
                        maped = parent[maped];
                    }
                    cout << "true" << endl;
                }
                else
                {
                    cout << "false" << endl;
                }
            }
        }
    }
}

int main()
{

    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}