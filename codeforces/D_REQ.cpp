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


const int nmax = 2e5+5;
ll seg[2*nmax];
ll gc[2*nmax];
int n;
const int valmax = 1000001;
int phi[valmax];
int inverse[valmax];

    

long long binpow(long long a, long long b, long long m) {
    a %= m;
    if(a == 0) return 1;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void preprocess() {
    for(int i = 0; i <= valmax; i++) inverse[i] = binpow(i, mod-2, mod);
    for(int i = 1; i <= valmax; i++) phi[i] = i - 1;
    phi[0] = 1;
    phi[1] = 1;
    for(int i = 2; i <= valmax; i++) {
        for(int j = 2 * i; j <= valmax; j += i) phi[j] -= phi[i];
    }
}

void build() {
    for(int i = n-1; i > 0; i--) {
        gc[i] = __gcd(gc[i << 1], gc[i << 1 | 1]);
        seg[i] = (seg[i << 1] * seg[i << 1 | 1] % mod) * gc[i] % mod;
        seg[i] = seg[i] * inverse[phi[gc[i]]] % mod;
    }
}

int query(int l, int r) {
    ll gc_tem = 0, val = 1;
    ll flag = 0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        debug2(l, r);
        if(l & 1) {
            gc_tem = __gcd(gc[l], gc_tem);
            val = (val * seg[l] % mod) * gc_tem % mod;
            val = val * inverse[phi[gc_tem]] % mod;
            if(flag == 0) val = phi[gc_tem], flag = 1;
            debug3(l, gc_tem, val);
            l++;
        }
        if(r & 1) {
            --r;
            gc_tem = __gcd(gc[r], gc_tem);
            val = (val * seg[r] % mod) * gc_tem % mod;
            val = val * inverse[phi[gc_tem]] % mod;
            if(flag == 0) val = phi[gc_tem], flag = 1;
            debug3(r, gc_tem, val);
        }
    }
    return val;
}

void solve()
{
    cin >> n;
    preprocess();
    debug4(phi[8], phi[90], __gcd(8,90), phi[__gcd(8, 90)]);
    debug(phi[720]);
    for(int i = n; i < 2 * n; i++) {
        cin >> gc[i];
        seg[i] = phi[gc[i]];
    }

    build();
    for(int i = 1; i < 2*n; i++) {
        debug3(i, gc[i], seg[i]);
    }
    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << query(l, r) << endl;
    }
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 1;
    // cin >> t;
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