#include <bits/stdc++.h>
using namespace std;

bool is_palin(long long n)
{
    string s = to_string(n);
    int sz = s.size();
    int i = 0;
    while (i < sz / 2)
    {
        if (s[i] != s[sz - 1 - i])
            return false;
        i++;
    }
    return true;
}
void solve()
{
    for (int i = 5; i < 6; i++)
    {
        int st = 1;
        for (int j = 2; j <= i; j++)
            st = st * 10;
        long long an = st;
        cout << i << " " << st << endl;
        for (int j = st; j < st * 10; j++)
        {
            for (int k = j; k < st * 10; k++)
            {
                long long tem = (long long)j * (long long)k;
                if (is_palin(tem))
                    an = tem;
            }
        }
        cout << i << " " << an << endl;
    }
}
int main()
{
    solve();
}