#include "bits/stdc++.h"
using namespace std;
#define x first
#define y second
const int N = 5000;
int p[N][N];
vector<int> a[N];
int main()
{
	int n, m, cond;
	cin >> n >> m >> cond;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	map<pair<pair<int, int>, int>, int> no;
	for (int i = 1; i <= cond; i++)
	{
		int p, q, r;
		cin >> p >> q >> r;
		no[{{p, q}, r}]++;
	}

	queue<pair<int, int>> q;
	q.push({1, 1});
	pair<int, int> ans = {-1, -1};
	while (!q.empty())
	{
		int u = q.front().x;
		int v = q.front().y;
		q.pop();
		if (v == n)
		{
			ans = {u, v};
			break;
		}
		for (int i : a[v])
		{
			if (p[v][i] or no[{{u, v}, i}])
				continue;
			p[v][i] = u;
			q.push({v, i});
		}
	}
	if (ans.x == -1)
	{
		puts("-1");
		return 0;
	}
	vector<int> path;
	while (ans.y != 1)
	{
		path.push_back(ans.y);
		ans = {p[ans.x][ans.y], ans.x};
	}
	path.push_back(1);
	cout << path.size() - 1 << "\n";
	reverse(path.begin(), path.end());
	for (int i : path)
		cout << i << " ";
}