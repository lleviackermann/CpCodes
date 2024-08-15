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
#define tree fadjf
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

const int nmax = 1e5;
const int l = 21;
int in[nmax+1], out[nmax+1], parents[nmax+1][l];
vvi tree(nmax+1);
int timer = -1;
ll val[nmax+1];
vl tax;

void dfs(int u, int v) {
    in[u] = ++timer;
    parents[u][0] = v;
    for(auto nei : tree[u]) {
        if(nei == v) continue;
        dfs(nei, u);
    }
    out[u] = ++timer;
}

bool isancestor(int u, int v) {
    return (in[u] < in[v] && out[u] > out[v]);
}

int lca(int a, int b) {
    if(isancestor(a, b)) return a;
    if(isancestor(b, a)) return b;
    for(int i = l-1; i >= 0; i--) {
        if(parents[a][i] == -1) continue;
        if(!isancestor(parents[a][i], b)) a = parents[a][i];
    }
    assert(a != -1);
    return parents[a][0];
}

void preprocess(int n) {
    timer = -1;
    dfs(0, -1);
    for(int i = 1; i < l; i++) {
        for(int j = 0; j < n; j++) {
            val[j] = 0;
            parents[j][i] = -1;
            if(parents[j][i-1] != -1) parents[j][i] = parents[parents[j][i-1]][i-1];
        }
    }
}

void dfs2(int u, int v) {
    for(auto nei : tree[u]) {
        if(nei == v) continue;
        dfs2(nei, u);
        val[u] += val[nei];
    }
}

ll ans[nmax+1][2];
void dfs3(int u, int v) {
    ans[u][0] = val[u] * (tax[u] / 2);
    ans[u][1] = val[u] * tax[u];
    ll half = 0, full = 0;
    for(auto nei : tree[u]) {
        if(nei == v) continue;
        dfs3(nei, u);
        half += ans[nei][1];
        full += min(ans[nei][0], ans[nei][1]);
    }
    ans[u][0] += half;
    ans[u][1] += full;
}


void solve()
{
    int n,m;
    cin >> n >> m;
    tax.clear();
    tax.resize(n);
    read(tax);
    for(int i = 0; i < n; i++) tree[i].clear();
    for(int i = 0; i < n-1; i++) {
        int st, en;
        cin >> st >> en;
        --st, --en;
        tree[st].push_back(en);
        tree[en].push_back(st);
    }
    preprocess(n);
    while(m--) {
        int st, en;
        cin >> st >> en;
        --st, --en;
        int lc = lca(st, en);
        val[st] += 1;
        val[en] += 1;
        val[lc] -= 1;
        if(parents[lc][0] != -1) val[parents[lc][0]] -= 1;
    }
    dfs2(0, -1);
    // for(int i = 0; i < n; i++) cout << val[i] << " ";
    // cout << endl;
    dfs3(0, -1);
    cout << min(ans[0][0], ans[0][1]) << endl;
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