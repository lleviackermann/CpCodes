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
#define roots fsdafdf
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

const int nmax = 1e5+10;
vvi edges(nmax);
vvi reverseEdges(nmax);
int used[nmax];
vi sortedNode;
vi components;
vi first_mem(nmax, 0);
vvi adj_scc(nmax);
ll val[nmax];

void dfs1(int u) {
    used[u] = true;
    for(auto i : edges[u]) {
        if(used[i]) continue;
        dfs1(i);
    }
    sortedNode.push_back(u);
}

void dfs2(int u, int k) {
    components.pb(u);
    used[u] = k;
    for(auto i : reverseEdges[u]) {
        if(used[i]) continue;
        dfs2(i, k);
    }
}

void solve()
{
    int n, m;
    cin>>n>>m;
    vi arr(n+1);
    for(int i = 1; i <= n; i++) cin>>arr[i];

    for(int i = 0; i < m; i++) {
        int st, en;
        cin>>st>>en;
        edges[st].pb(en);
        reverseEdges[en].pb(st);
    }
    memset(used, 0, sizeof used);
    for(int i = 1; i <= n; i++) {
        if(!used[i]) dfs1(i);
    }
    memset(used, 0, sizeof used);
    int k = 0;
    reverse(all(sortedNode));
    for(auto i : sortedNode) {
        if(!used[i]) {
            dfs2(i, ++k);
            int root = components.front();
            for(auto u : components) {
                first_mem[u] = root;
                val[root] += arr[u];
            }
            components.clear();
        }
    }
    for(int v = 1; v <= n; v++) {
        for(auto nei : edges[v]) {
            int root_v = first_mem[v], root_nei = first_mem[nei];
            if(root_v != root_nei) {
                adj_scc[root_v].pb(root_nei);
            }
        }
    }
    // for(int i = 1; i <= n; i++) {
    //     cout<<i<<" ->";
    //     for(auto j : edges[i]) cout<<" "<<j<<" ";
    //     cout<<endl;
    // }
    // for(int i = 1; i <= n; i++) debug3(i, first_mem[i], val[i]);
    // for(int i = 1; i <= n; i++) {
    //     cout<<i<<" ->";
    //     for(auto j : adj_scc[i]) cout<<" "<<j<<" ";
    //     cout<<endl;
    // }
    for(int i = 1; i <= n; i++) val[i] = -1 * val[i];
    vl coins(n+1, 1e17);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll root = first_mem[i];
        if(coins[root] != 1e17) continue;
        priority_queue<pl, vector<pl>, greater<pl>> store;
        coins[root] = val[root];
        store.push({coins[root], root});
        while(store.size()) {
            auto [tempcoins, ind] = store.top();
            store.pop();
            if(tempcoins > coins[ind]) continue;
            ans = max(ans, -1*coins[ind]);
            for(auto nei : adj_scc[ind]) {
                if(coins[nei] > coins[ind] + val[nei]) {
                    coins[nei] = coins[ind] + val[nei];
                    store.push({coins[nei], nei});
                }
            }
        }
    }
    // cout<<-1*coins[fa]<<endl;
    cout<<ans<<endl;
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
    // cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}