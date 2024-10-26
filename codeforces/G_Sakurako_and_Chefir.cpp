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

const ll mod = 1e9 + 7;

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

int binpow(long long a, long long b, long long m) {
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

void solve()
{
    int n;
    cin >> n;
    vvi tre(n);
    for(int i = 1; i < n; i++) {
        int st, en;
        cin >> st >> en;
        --st, --en;
        tre[st].push_back(en);
        tre[en].push_back(st);
    }
    vvi par(n, vi(21, -1));
    vi sub(n, 0);
    vvi ma_store(n);
    vector<vector<pi>> child(n);
    auto dfs = [&](auto&& dfs, int u, int v) -> void {
        par[u][0] = v;
        sub[u] = 0;
        for(auto nei : tre[u]) {
            if(nei != v) {
                dfs(dfs, nei, u);
                sub[u] = max(sub[u], 1 + sub[nei]);
                if(sub[u] == 1 + sub[nei]) ma_store[u].push_back(nei);
                child[u].push_back({sub[nei] + 1, nei});
            }
        }
        sort(all(child[u]));
    };
    vi zero(n, 0);
    auto dfs2 = [&](auto&& dfs2, int u, int v, int curr) -> void {
        zero[u] = curr;
        for(auto nei : tre[u]) {
            if(nei != v) {
                dfs2(dfs2, nei, u, curr + 1);
            }
        }
    };
    dfs(dfs, 0, -1);
    dfs2(dfs2, 0, -1, 0);
    vvi dp(n, vi(21, -1));
    for(int i = 0; i < 21; i++) par[0][i] = -1, dp[0][i] = -1;
    for(int i = 1; i < n; i++) {
        int up = (ma_store[par[i][0]].size() == 1 && ma_store[par[i][0]][0] == i ? 0 : 1);
        dp[i][0] = max(sub[i], up + sub[par[i][0]]);
    }
    for(int i = 1; i < 21; i++) {
        for(int j = 1; j < n; j++) {
            if(par[j][i-1] != -1) par[j][i] = par[par[j][i-1]][i-1];
            if(par[j][i] == -1) continue;
            int up = zero[j] - zero[par[j][i-1]];
            dp[j][i] = max(dp[j][i-1],  up + dp[par[j][i-1]][i-1]);
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < n; j++) cout << dp[j][i] << " ";
        cout << endl;
    }
    auto calc = [&](int u, int para) {
        int tem = u;
        int ma = 0;
        for(int i = 20; i >= 0; i--) {
            if((para >> i) & 1) {
                ma = max(ma, dp[tem][i]);
                tem = par[tem][i];
            }
        }
        return ma;
    };
    int q;
    cin >> q;
    while(q--) {
        int v, k;
        cin >> v >> k;
        --v;
        k = min(k, zero[v]);
        cout << max(calc(v, k), sub[v]) << " ";
    }
    cout << endl;
    // debug4(par[4][12], par[0][12], par[4][0], par[3][1]);
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 1;
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