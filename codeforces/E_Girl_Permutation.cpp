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

const int nmax = 2e5+10;
ll factorial[nmax], invfact[nmax];

void preprocess() {
    factorial[0] = 1;
    for(ll i = 1; i < nmax; i++) factorial[i] = factorial[i-1] * i % mod;
    invfact[nmax-1] = binpow(factorial[nmax-1], mod-2, mod);
    for(ll i = nmax-2; i >= 0; i--) invfact[i] = invfact[i+1] * (i + 1) % mod;
}

ll nCr(ll n, ll r) {
    ll ans = factorial[n] * invfact[r] % mod;
    ans = ans * invfact[n-r] % mod;
    return ans;
}

ll recur(ll start, ll end, vl &prefix, vl &suffix) {
    ll sz = end - start + 1;
    if(prefix.size() && suffix.size() && prefix.back() == suffix.back()) {
        ll mid = prefix.back();
        prefix.pop_back();
        suffix.pop_back();
        ll temp = nCr(sz-1, mid-1);
        ll ans = temp;
        if(mid > 1) ans *= recur(1, mid-1, prefix, suffix);
        ans %= mod;
        if(mid < sz) ans *= recur(mid+1, sz, prefix, suffix);
        debug4(start, end, mid, ans);
        return ans % mod;
    }
    if(prefix.size()) {
        if(prefix.back() <= end && prefix.back() >= start) {
            ll mid = prefix.back();
            prefix.pop_back();
            ll temp = nCr(sz-1, mid-start);
            ll ans = temp;
            if(mid > start) ans *= recur(start, mid-1, prefix, suffix);
            ans %= mod;
            if(mid < end) ans *= recur(mid+1, end, prefix, suffix);
            debug4(start, end, mid, ans);
            return ans % mod;
        }
    }
    if(suffix.size()) {
        if(suffix.back() >= start && suffix.back() <= end) {
            ll mid = suffix.back();
            suffix.pop_back();
            // debug4(sz, mid, start, end);
            ll temp = nCr(sz-1, mid-start);
            ll ans = temp;
            if(mid > start) ans *= recur(start, mid-1, prefix, suffix);
            ans %= mod;
            if(mid < end) ans *= recur(mid+1, end, prefix, suffix);
            debug4(start, end, mid, ans);
            return ans % mod;
        }
    }
    debug2(start, end);
    return factorial[sz];
}
void solve()
{
    ll n, m1, m2;
    cin>>n>>m1>>m2;
    vl prefix(m1), suffix(m2);
    read(prefix);
    read(suffix);

    if(prefix.back() != suffix[0] || prefix[0] != 1 || suffix.back() != n) {    
        cout<<"0\n";
        return;
    }
    reverse(all(suffix));
    cout<<recur(1, n, prefix, suffix)<<endl;
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 1;
    cin >> t;
    preprocess();
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