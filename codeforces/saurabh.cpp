#include <bits/stdc++.h>
#include <climits>
using namespace std;

void solve() {
	int n, budget;
	cin >> n >> budget;

	vector<vector<int>> adj(n);
	vector<int> degree_in(n);
	vector<int> cost(n), leadership(n);

	for (int i = 0; i < n; ++i) {
		int r, c, l;
		cin >> r >> c >> l;
		// r--;
		if (r >= 0)
			adj[r].emplace_back(i);
		degree_in[i]++;
		cost[i] = c;
		leadership[i] = l;
	}

	int ceo = 0;
	for (auto v = 0; v < n; ++v) {
		if (degree_in[v] == 0) {
			ceo = v;
			break;
		}
	}

	using i64 = long long;
	vector<i64> max_happiness(n);
	vector<multiset<i64, std::greater<>>> employees_under(n);
	vector<i64> employees_under_total_cost(n);

	auto dfs = [&](auto&& self, int u, int p = -1) -> void {
		for (auto v : adj[u]) {
			if (v == p)
				continue;
			self(self, v, u);

			if (employees_under[u].size() < employees_under[v].size())
				swap(employees_under[u], employees_under[v]);
			employees_under[u].insert(employees_under[v].cbegin(), employees_under[v].cend());
			employees_under_total_cost[u] += employees_under_total_cost[v];

			while (employees_under_total_cost[u] > budget) {
				auto it = employees_under[u].begin();
				employees_under_total_cost[u] -= *it;
				employees_under[u].erase(it);
			}
		}

		assert(employees_under_total_cost[u] <= budget);
		max_happiness[u] = leadership[u] * (int)employees_under[u].size();

		employees_under[u].emplace(cost[u]);
		employees_under_total_cost[u] += cost[u];

		while (employees_under_total_cost[u] > budget) {
			auto it = employees_under[u].begin();
			employees_under_total_cost[u] -= *it;
			employees_under[u].erase(it);
		}

		max_happiness[u] = max(max_happiness[u], leadership[u] * i64((int)employees_under[u].size()));
	};

	dfs(dfs, ceo);
	cout << *max_element(max_happiness.cbegin(), max_happiness.cend()) << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int t = 1;
	// std::cin >> t;
	while (t--)
		solve();
}
