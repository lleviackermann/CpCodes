#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;

int n;
struct DSU
{
  int d;
  int fa[maxn], r[maxn];
  void prepare()
  {
    for (int i = 1; i <= n; i++)
      fa[i] = i, r[i] = i;
  }
  int find(int x)
  {
    if (fa[x] == x)
      return x;
    return fa[x] = find(fa[x]);
  }
  void merge(int x, int y)
  {
    x = find(x), y = find(y);
    if (x == y)
      return;
    fa[x] = y;
    r[y] = max(r[x], r[y]);
  }
  void chg(int L, int R)
  {
    for (int p = find(L); p < R; p = find(p))
      merge(p, p + d);
  }
} dsu[11];

void solve()
{
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= 10; i++)
    dsu[i].prepare(), dsu[i].d = i;
  for (int i = 1; i <= m; i++)
  {
    int a, d, k;
    scanf("%d%d%d", &a, &d, &k);
    dsu[d].chg(a, a + d * k);
  }
  for(int i = 1; i <= n; i++) {
    cout << i << "->";
    cout << dsu[2].fa[i] << "," << dsu[2].fa[i] << endl;
  }
  for (int i = 1; i <= 10; i++)
    for (int j = 1; j <= n; j++)
      dsu[0].merge(j, dsu[i].find(j));
  int ans = 0;
  for (int i = 1; i <= n; i++)
    if (dsu[0].find(i) == i)
      ans++;
  printf("%d\n", ans);
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T--)
  {
    solve();
  }
  return 0;
}
