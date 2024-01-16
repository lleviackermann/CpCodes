#include <bits/stdc++.h>
using namespace std;
#define sim template <class c
#define ris return *this
#define dor > debug &operator<<
#define eni(x)                                                                    \
	sim > typename enable_if<sizeof dud<c>(0) x 1, debug &>::type operator<<(c i) \
	{
sim > struct rge
{
	c b, e;
};
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c *x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug
{
#ifdef LOCAL
	~debug() { cerr << endl; }
	eni(!=) cerr << boolalpha << i;
	ris;
} eni(==) ris << range(begin(i), end(i));
}
sim, class b dor(pair<b, c> d)
{
	ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d)
{
	*this << "[";
	for (auto it = d.b; it != d.e; ++it)
		*this << ", " + 2 * (it == d.b) << *it;
	ris << "]";
}
#else
	sim dor(const c &) { ris; }
#endif
}
;
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
// debug & operator << (debug & dd, P p) { dd << "(" << p.x << ", " << p.y << ")"; return dd; }

void test_case()
{
	int n, m;
	cin >> n >> m;
	vector<int> value(n);
	for (int i = 0; i < n; i++)
	{
		cin >> value[i];
	}
	vector<vector<int>> edges(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	vector<int> g(n);
	vector<vector<int>> inv(n);
	for (int i = 0; i < n; i++)
	{
		g[i] = i;
		inv[i] = {i};
	}
	vector<set<pair<int, int>>> those(n);
	for (int a = 0; a < n; a++)
	{
		for (int b : edges[a])
		{
			those[a].insert({value[b], b});
		}
	}

	function<void(int)> f = [&](int a) -> void
	{
		if (value[a] > 0 && (int)inv[a].size() == 1)
		{
			return;
		}

#define a a2
		auto uni = [&](int a, int b)
		{
			debug() << "uni" imie(a) imie(inv[a]) imie(b) imie(inv[b]);
			if (inv[b].size() > inv[a].size())
			{
				swap(a, b);
			}
			those[a].insert(those[b].begin(), those[b].end());
			those[b].clear();
			for (int x : inv[b])
			{
				g[x] = a;
				inv[a].push_back(x);
			}
			inv[b].clear();
		};
#undef a

		while (g[a] == a && !those[a].empty() && those[a].begin()->first <= (int)inv[a].size())
		{
			int b = those[a].begin()->second;
			those[a].erase(those[a].begin());
			if (g[a] == g[b])
			{
				continue;
			}
			uni(g[a], g[b]);
		}
	};

	for (int i = 0; i < n; i++)
	{
		f(i);
	}
	for (int i = 0; i < n; i++)
	{
		if ((int)inv[i].size() == n)
		{
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--)
	{
		test_case();
	}
}
