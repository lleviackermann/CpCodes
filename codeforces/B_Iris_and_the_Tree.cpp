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

const int nodemax = 2e5 + 5;
const int l = 21;
int parents[nodemax][l];
int tin[nodemax], tout[nodemax];
int sz[nodemax], dep[nodemax];
int timer = 0;
vector<vector<int>> adj(nodemax);

void dfs(int u, int par)
{
    tin[u] = ++timer;
    if(u != 1) parents[u][0] = par;
    sz[u] = 1;
    dep[u] = dep[par] + 1;
    for (auto i : adj[u])
    {
        if (i == par)
            continue;
        dfs(i, u);
        sz[u] += sz[i];
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
    dep[0] = -1;
    timer = 0;
    parents[1][0] = -1;
    dfs(1, 0);
    for (int i = 1; i < l; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            parents[j][i] = ((parents[j][i - 1] == -1) ? -1 : parents[parents[j][i - 1]][i - 1]);
        }
    }
}

int dist(int u, int v) {
    return (dep[u] + dep[v] - 2*dep[lca(u, v)]);
}

void solve()
{
    ll n, w;
    cin >> n >> w;
    for(int i = 0; i <= n; i++) adj[i].clear();
    for(int i = 2; i <= n; i++) {
        int st;
        cin >> st;
        adj[st].push_back(i);
        adj[i].push_back(st);
    }
    preprocess(n);
    ll cntwei = 0;
    ll tot = 0, comp = 0;
    int te = n;
    --te;
    vl filled(n+1, 0);
    vl distance(n+1, 0);
    for(int i = 1; i < n; i++) distance[i] = dist(i, i+1);
    distance[n] = dist(n, 1);
    while(te--) {
        ll ind, wei;
        cin >> ind >> wei;
        tot += wei;
        ll prev = ind - 1;
        ll nex = ind + sz[ind] - 1;
        filled[prev]++, filled[nex]++;
        cntwei += 2ll * wei;
        if(filled[prev] == distance[prev]) comp++;
        if(filled[nex] == distance[nex]) comp++;
        cout << cntwei + (n - comp) * (w - tot) << " \n"[te==0];
    }   
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