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
 
template <typename T>
class SegmentTree
{
public:
    T n;
    vector<T> tree;
 
    SegmentTree(vector<T> &arr)
    {
        this->n = arr.size();
        tree.resize(4 * this->n + 1);
        build(arr);
    }
 
    void build(T index, T start, T end, vector<T> &arr)
    {
        if (start == end)
        {
            tree[index] = arr[start];
            return;
        }
        T mid = (start + end) / 2;
        build(2 * index + 1, start, mid, arr);
        build(2 * index + 2, mid + 1, end, arr);
        tree[index] = max(tree[2 * index + 1], tree[2 * index + 2]);
    }
 
    T query(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            return 0;
        }
        if (start >= l && end <= r)
            return tree[index];
 
        T mid = (start + end) / 2;
        T first = query(2 * index + 1, start, mid, l, r);
        T second = query(2 * index + 2, mid + 1, end, l, r);
        return max(first, second);
    }
 
    void update(T index, T target, T value, T start, T end)
    {
        if (start == end)
        {
            tree[index] = value;
            return;
        }
 
        T mid = (start + end) / 2;
        if (target <= mid)
        {
            update(2 * index + 1, target, value, start, mid);
        }
        else
        {
            update(2 * index + 2, target, value, mid + 1, end);
        }
        tree[index] = max(tree[2 * index + 1], tree[2 * index + 2]);
    }
 
    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }
 
    T query(T l, T r)
    {
        return query(0, 0, this->n - 1, l, r);
    }
 
    void update(T target, T value)
    {
        update(0, target, value, 0, this->n - 1);
    }
};
 
const int nodemax = 2e5 + 5;
const int l = 21;
int parents[nodemax][l];
int tin[nodemax], tout[nodemax];
int timer = 0;
int depth[nodemax], head[nodemax], position[nodemax], heavy[nodemax];
 
vector<vector<int>> adj;
 
int dfs(int u, int par)
{
    tin[u] = ++timer;
    parents[u][0] = par;
    int size = 1;
    int max_size = 0;
    for (auto i : adj[u])
    {
        if (i == par)
            continue;
        depth[i] = depth[u] + 1;
        int cur_size = dfs(i, u);
        size += cur_size;
        if(cur_size > max_size) {
            heavy[u] = i;
            max_size = cur_size;
        }
    }
    tout[u] = ++timer;
    return size;
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
 
int cur_pos;
 
void decompose(int v, int h) {
    head[v] = h, position[v] = cur_pos++;
    if(heavy[v] != -1) decompose(heavy[v], h);
 
    for(auto neighbour : adj[v]) {
        if(neighbour != parents[v][0] && neighbour != heavy[v]) {
            decompose(neighbour, neighbour);
        }
    }
}
 
void preprocess(int n)
{
    for(int i = 1; i <= n; i++) heavy[i] = -1;
    dfs(1, -1);
    for (int i = 1; i < l; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            parents[j][i] = ((parents[j][i - 1] == -1) ? -1 : parents[parents[j][i - 1]][i - 1]);
        }
    }
    cur_pos = 0;
    
    decompose(1, 1);
}
 
 
void solve()
{
    int n, q;
    cin>>n>>q;
 
    vi arr(n);
    read(arr);
    adj.resize(n+1);
    for(int i = 0; i < n-1; i++) {
        int st, en;
        cin>>st>>en;
        adj[st].pb(en);
        adj[en].pb(st);
    }
    preprocess(n);
    // for(int i = 1; i <= n; i++) {
    //     debug4(i, heavy[i], position[i], head[i]);
    // }
    vi store(cur_pos+10, 0);
    for(int i = 1; i <= n; i++) {
        store[position[i]] = arr[i-1];
    }
 
    SegmentTree<int> segtree(store);
 
    auto query = [&](int a, int b) {
        int lab = lca(a, b);
        int cur = a;
        int ans = 0;
        while(head[cur] != head[lab]) {
            if(head[cur] == cur) ans = max(ans, arr[cur-1]);
            else ans = max(ans, segtree.query(position[head[cur]], position[cur]));
            cur = parents[head[cur]][0];
        }
        if(head[cur] == cur) ans = max(ans, arr[cur-1]);
        else ans = max(ans, segtree.query(position[lab], position[cur]));
        cur = b;
        while(head[cur] != head[lab]) {
            if(head[cur] == cur) ans = max(ans, arr[cur-1]);
            else ans = max(ans, segtree.query(position[head[cur]], position[cur]));
            cur = parents[head[cur]][0];
        }
        if(head[cur] == cur) ans = max(ans, arr[cur-1]);
        else ans = max(ans, segtree.query(position[lab], position[cur]));
        return ans;
    };
 
    while(q--) {
        int sign, ind, thi;
        cin>>sign>>ind>>thi;
        if(sign == 1) {
            arr[ind-1] = thi;
            segtree.update(position[ind], thi);
        } else {
            cout<<query(ind, thi)<<" ";
        }
    }
    cout<<endl;
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
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    
    #ifndef ONLINE_JUDGE
    cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}