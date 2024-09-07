#include <bits/stdc++.h>

using namespace std;

long long n, M;

long long frac[3000005], inv[3000005];

long long powermod(long long a, long long b, long long m)
{
	if (b == 0) return 1;
	unsigned long long k = powermod(a, b / 2, m);
	k = k * k;
	k %= m;
	if (b & 1) k = (k * a) % m;
	return k;
}

void Ready()
{
	frac[0] = 1;
	inv[0] = 1;
	for (int i = 1; i <= 3000000; i++)
	{
		frac[i] = (frac[i - 1] * i) % M;
	}
	
	inv[3000000] = powermod(frac[3000000], M - 2, M);
	
	for (int i = 3000000; i > 0; i--)
	{
		inv[i - 1] = (inv[i] * i) % M;
	}
}

long long C(long long n, long long k)
{
	return ((frac[n] * inv[k]) % M * inv[n - k]) % M;
}

int main()
{
	cin >> n >> M;
	Ready();
	long long ans[4]{};
	
	// X = 0
	
	ans[0] = 1;
	
	// X = 1
	
	ans[1] = 2 * frac[2 * n] - frac[n] - ans[0] + M + M;
	ans[1] %= M;
	
	// X = 2
	
	ans[2] = frac[2 * n];
	ans[2] = ans[2] * C(2 *n, n) % M;
	ans[2] = ans[2] * frac[n] % M;
	ans[2] = ans[2] * 2 % M;
    cout << ans[2] << endl;
	for (int i = 0; i <= n; i++)
	{
		int sub = C(n, i);
		sub = sub * C(n, n - i) % M;
		sub = sub * C(2 * n - i, n) % M;
		sub = sub * frac[n] % M;
		sub = sub * frac[n] % M;
		sub = sub * frac[n] % M;
        cout << i << " " << sub << endl;
		ans[2] = (ans[2] - sub + M) % M;
	}
	ans[2] = (ans[2] - ans[1] + M) % M;
	ans[2] = (ans[2] - ans[0] + M) % M;
	
	// X = 3
	
	ans[3] = frac[3 * n];
	ans[3] = (ans[3] - ans[2] + M) % M;
	ans[3] = (ans[3] - ans[1] + M) % M;
	ans[3] = (ans[3] - ans[0] + M) % M;
	
	long long answer = ans[1] + 2 * ans[2] + 3 * ans[3];
	answer %= M;
	
	cout << answer << endl;
}