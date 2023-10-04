/*
 *  Author : arpandesai0
 *  Created : [30-09-2023 12:57]
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 100005;
vector<int> spf(MAXN);
vector<vector<int>> pf_mem(MAXN);
void sieve()
{
	spf[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		spf[i] = i;
	}
	for (int i = 4; i < MAXN; i += 2) {
		spf[i] = 2;
	}
	for (int i = 3; i * i < MAXN; i++) {
		if (spf[i] == i) {
			for (int j = i * i; j < MAXN; j += i) {
				if (spf[j] == j) {
					spf[j] = i;
				}
			}
		}
	}
}
vector<int> getF(int x)
{
	if (pf_mem[x].size()) return pf_mem[x];
	int y = x;
	while (x != 1)
	{
		if (pf_mem[y].size() == 0 || pf_mem[y].back() != spf[x]) {
			pf_mem[y].push_back(spf[x]);
		}
		x = x / spf[x];
	}
	return pf_mem[y];
}


vector<int> f(MAXN + 1);
vector<bool> done(MAXN + 1);
vector<int> dp(MAXN + 1);

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		f[a[i]]++;
		dp[a[i]] = 0;
	}
	sort(a.rbegin(), a.rend());
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (done[a[i]]) continue;
		done[a[i]] = true;
		vector<int> pf = getF(a[i]);
		if (a[i] == 1) {
			for (int j = i - 1; j >= 0; j--) {
				dp[1] = max(dp[1], dp[a[j]] + f[a[j]]);
			}
		}
		for (int j : pf) {
			int y = a[i] / j;
			if (f[y] == 0) continue;
			dp[y] = max(dp[y], dp[a[i]] + f[a[i]]);
		}
		ans = max(ans, a[i] * (dp[a[i]] + f[a[i]]));
	}
	cout << ans << '\n';
	for (int i = 0; i < n; i++) {
		done[a[i]] = false;
		dp[a[i]] = 0, f[a[i]] = 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	sieve();
	int  t = 1;
	cin >> t;
	while (t--)
		solve();

	return 0;
}