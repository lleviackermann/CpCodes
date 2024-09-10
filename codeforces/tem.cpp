#include <bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;
int n, k;
int phi(int x)
{
  int ans = x;
  for (int i = 2; i * i <= x; i++)
  {
    if (x % i == 0)
    {
      ans = ans / i * (i - 1);
    }
    while (x % i == 0)
    {
      x /= i;
    }
  }
  if (x > 1)
  {
    ans = ans / x * (x - 1);
  }
  return ans;
}
signed main()
{
  cin >> n >> k;
  k = (k + 1) / 2;
  for (int i = 1; i <= k && n > 1; i++)
  {
    n = phi(n);
  }
  cout << n % mod;
  return 0;
}