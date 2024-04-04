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

vvi adj(100005);
int pos = 0, maxlen = 0;
vl population(1e5+10);
int start_node, end_node;
void fartehst(int u, int v, int counter)
{
    // debug3(u, v, counter);
    if (counter > maxlen)
    {
        maxlen = counter;
        pos = u;
    }
    for (auto i : adj[u])
    {
        // debug2(i,u);
        if (i == v)
            continue;
        fartehst(i, u, counter + 1);
    }
}


ll costcalc = 0;
void calccost(int u, int v, ll counter) {
    costcalc += 1ll * ((counter+1)/2) * population[u] % mod; 
    for(auto nei : adj[u]) {
        if(nei == v) continue;
        calccost(nei, u, counter+1);
    }
    costcalc %= mod;
}

const int nodemax = 1e5 + 5;
const int l = 21;
int parents[nodemax][l];
int tin[nodemax], tout[nodemax], depth[nodemax];
int timer = 0;

void dfs(int u, int par)
{
    tin[u] = ++timer;
    if(u == 0) depth[u] = 0;
    else depth[u] = depth[par] + 1;
    parents[u][0] = par;

    for (auto i : adj[u])
    {
        if (i == par)
            continue;
        dfs(i, u);
    }
    tout[u] = ++timer;
}

bool isAncestor(int u, int v)
{
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int lca(int u, int v)
{
    if (isAncestor(u, v))
        return u;
    if (isAncestor(v, u))
        return v;

    for (int i = l - 1; i >= 0; i--)
    {
        if (parents[u][i] == -1)
            continue;
        if (!isAncestor(parents[u][i], v))
            u = parents[u][i];
    }
    // cout<<u<<endl;
    return parents[u][0];
}

void preprocess(int n)
{
    dfs(0, -1);
    for (int i = 1; i < l; i++)
    {
        for (int j = 0; j < n; j++)
        {
            parents[j][i] = ((parents[j][i - 1] == -1) ? -1 : parents[parents[j][i - 1]][i - 1]);
        }
    }
}

void solve()
{
    int n;
    cin>>n;
    for(int i = 0; i < n; i++) cin>>population[i];
    for(int i = 0; i < n-1; i++) {
        int st, en;
        cin>>st>>en;
        --st, --en;
        adj[st].pb(en);
        adj[en].pb(st);
    }
    // for(int i = 0; i < n; i++) {
    //     cout<<i<<"->";
    //     print(adj[i]);
    // }
    pos = -1, maxlen = -1;
    fartehst(0, -1, 0);
    start_node = pos;
    debug2(pos, maxlen);
    pos = -1, maxlen = -1;
    fartehst(start_node, -1, 0);
    end_node = pos;
    preprocess(n);
    auto distance = [&] (int a, int b) {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    };
    debug(distance(0, 2));
    int tma = 1e9, tind = -1;
    for(int i = 0; i < n; i++) {
        int ma = max(distance(i, start_node), distance(i, end_node));
        if((ma+1)/2 < tma) tma = (ma+1) / 2, tind = i;
    }
    debug2(tma, tind);
    calccost(tind, -1, 0);
    cout<<costcalc<<endl;
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