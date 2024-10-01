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

constexpr int nmax = 2e5+1;
ll fact[nmax], inv[nmax];

void precalc() {
    fact[0] = 1;
    for(int i = 1; i < nmax; i++) fact[i] = fact[i-1] * i % mod;
    inv[nmax-1] = binpow(fact[nmax-1], mod-2, mod);
    for(int i = nmax-2; i >= 0; i--) inv[i] = inv[i+1] * (i + 1) % mod;
}

ll nCr(ll n, ll r) {
    ll ans = fact[n] * inv[r] % mod;
    return ans * inv[n-r] % mod;
}

void solve()
{
    ll n;
    cin >> n;
    vi arr(n), prr(n);
    read(arr);
    read(prr);
    ll ans = 0;
    vector<vector<pair<int, ll>>> dp(n);
    for(int i = 0; i < n; i++) dp[i].push_back({0, 1ll});
    for(int i = 1; i >= 0; i--) {
        int zero = 0, ones = 0;
        for(int j = 0; j < n; j++) {
            if((arr[j] >> i) & 1) ones++;
            else zero++;
        }
        debug(i);
        debug2(zero, ones);
        // ll for_zero = 
        for(int j = 0; j < n; j++) {
            int is_set = (arr[j] >> i) & 1;
            vector<pair<int, ll>> new_pa;
            ll for_zero = 0, for_one = 0;
            if(is_set) {
                for_one = binpow(2, zero, mod) * binpow(2, ones-2, mod) % mod;
                for_zero = binpow(2, zero, mod) * binpow(2, ones-2, mod) % mod;
            } else {
                for_one = binpow(2, zero-1, mod) * binpow(2, ones - 1, mod) % mod;
                for_zero = binpow(2, zero-1, mod) * binpow(2, ones - 1, mod) % mod;
            }
            debug2(for_zero, for_one);
            auto &vec = dp[j];
            for(auto [fir, sec] : vec) {
                new_pa.push_back({fir | (1 << i), sec * for_one % mod});
                new_pa.push_back({fir, sec * for_zero % mod});
            }
            vec.clear();
            vec = new_pa;
        }
    }
    for(int i = 0; i < n; i++) {
        // auto &vec = dp[i]
        cout << i << "->";
        for(auto [fir, sec] : dp[i]) {
            cout << fir << " " << sec << endl;
        }
    }
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 1;
    precalc();
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