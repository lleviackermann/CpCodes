#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define endl "\n"
#define fo(i, n) for (i = 0; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n; k++)
#define pb push_back
#define ll long long
#define mp make_pair
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, arr) for (auto it = arr.begin(); it != arr.end(); it++)
#define PI 3.1415926535897932384626
#define suprit ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0);
#define line cout << endl;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef map<ll, ll> ml;
typedef map<string, ll> msl;
typedef map<ll, string> mls;
typedef unordered_map<ll, ll> uml;
typedef unordered_map<string, ll> umsl;
typedef unordered_map<ll, string> umls;
typedef set<ll> sl;
typedef set<pair<ll, ll>> spl;
typedef ordered_set<ll> osl;
typedef ordered_set<pair<ll, ll>> ospl;

const ll mod = 998244353;

bool comp2(pair<ll, ll> &arr, pair<ll, ll> &b)
{
    if (arr.first == b.first)
        return arr.second < b.second;
    return arr.first < b.first;
};

template <typename T> void read(T i, T n, vector<T> &arr) { for(T j = i; j < n; j++) cin >> arr[j]; }
template <typename T> void read(vector<T> &arr) { for(auto &j : arr) cin>>j; }

#ifndef ONLINE_JUDGE

template <typename T, typename V> void print(set<pair<T, V>> &arr) { for(auto &it : arr) cout<<it.first<<" "<<it.second<<endl; line}
template <typename T, typename V> void print(pair<T, V>& pa) { cout<<pa.first<<" "<<pa.second<<endl; }
template <typename T> void print(T i, T last, vector<T> &arr) { for(T j = i; j < last; j++) cout<<arr[j]<<" "; line} 
template <typename T> void print(T i, vector<T> &arr) { for(T j = i; j < arr.size(); j++) cout<<arr[j]<<" "; line} 
template <typename T> void print(vector<T> &arr) { for(auto &i : arr) cout<<i<<" "; line}
template <typename T, typename V> void print(unordered_map<T, V>& arr) { for(auto &it : arr) cout<<it.first<<" "<<it.second<<endl; line}
template <typename T, typename V> void print(map<T, V>& arr) { for(auto &it : arr) cout<<it.first<<" "<<it.second<<endl;}
template <typename T> void print(unordered_set<T> &arr) { for(auto &it : arr) cout<<it<<" "; line }
template <typename T> void print(ordered_set<T> &arr) { for(auto &it : arr) cout<<it<<" "; line }
template <typename T> void print(set<T> &arr) { for(auto &it : arr) cout<<it<<" "; line }
template <typename T, typename... Args> void print(T t, Args... args) { cout << t << " "; print(args...); }
template <typename T> void print(T t) { cout<<t<<"\n"; }
#define debug(x) cout<<#x<<" "<<x<<endl;
#define debug2(x, y) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<endl;
#define debug3(x, y, z) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<" "<<#z<<" "<<z<<endl;
#define debug4(x, y, z, a) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<" "<<#z<<" "<<z<<" "<<#a<<" "<<a<<endl;

#else

#define print(x) 
#define debug(x)
#define debug2(x, y)
#define debug3(x, y, z)
#define debug4(x, y, z, a)

#endif

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

vl fact, inv;
const int nmax = 2e5+10;
void preprocess() {
    fact.resize(nmax+1, 1);
    inv.resize(nmax+1, 1);
    for(int i = 1; i <= nmax; i++) fact[i] = fact[i-1] * i % mod;
    inv[nmax] = binpow(fact[nmax], mod - 2, mod);
    for(int i = nmax-1; i >= 0; i--) inv[i] = inv[i+1] * (i + 1) % mod;
}

ll nCr(ll n, ll r) {
    return fact[n] * inv[r] % mod * inv[n-r] % mod;
}

void solve()
{
    ll n;
    cin >> n;
    vl arr(n);
    read(arr);
    vvl dp(n);
    vl cnt(n, 0);
    for(int i = 0; i < n; i++) cnt[arr[i]]++;
    dp[0].push_back(0);
    ll ans = 0;
    ll sum = n;
    sum -= cnt[0];
    for(int i = 1; i <= cnt[0]; i++) {
        dp[0].push_back(nCr(cnt[0], i));
        ans += dp[0][i] * i % mod *binpow(2, sum, mod) % mod;
        ans %= mod;
    }
    // for(int i = 0; i <= cnt[0]; i++) cout << dp[0][i] << " ";
    // cout << endl;
    for(int i = cnt[0] - 1; i >= 0; i--) dp[0][i] = (dp[0][i] + dp[0][i+1]) % mod;
    //     for(int i = 0; i <= cnt[0]; i++) cout << dp[0][i] << " ";
    // cout << endl;
    for(int i = 1; i < n; i++) {
        dp[i].push_back(0ll);
        // cout << dp[i].back() << " ";
        ll ncr_sum = 0;
        for(int j = 1; j <= cnt[i]; j++) {
            ncr_sum += nCr(cnt[i], j);
            ncr_sum %= mod;
        }
        sum -= cnt[i];
        for(int j = 1; j < min((ll)dp[i-1].size(), cnt[i] + 1); j++) {
            ll curr = 0;
            int p_s = dp[i-1].size();
            if(j < p_s - 1) {
                curr += dp[i-1][j+1] * nCr(cnt[i], j) % mod;
                curr %= mod;
            }
            ll prev = dp[i-1][j];
            if(j + 1 < p_s) prev = (prev - dp[i-1][j+1] + mod) % mod;
            curr += ncr_sum * prev % mod;
            curr %= mod;
            ans += curr * j % mod * binpow(2, sum, mod) % mod;
            ans %= mod;
            dp[i].push_back(curr);
            // cout << dp[i].back() << " ";
            ncr_sum = (ncr_sum - nCr(cnt[i], j) + mod) % mod;
        }
        // cout << endl;
        int ano = dp[i].size();
        for(int j = ano - 2; j >= 0; j--) {
            dp[i][j] += dp[i][j+1];
            dp[i][j] %= mod;
        }
    }
    cout << ans << endl;
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 1;
    preprocess();
    cin >> t;
    while (t--)
    {
        solve();
    }
    clock_t end = clock();
    
    #ifndef ONLINE_JUDGE
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}