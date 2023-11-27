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
    vector<T> lazyTree;

    SegmentTree(vector<T> &arr)
    {
        this->n = arr.size();
        tree.resize(2 * this->n + 1);
        lazyTree.resize(2 * this->n + 1, 0);
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
        build(index + 1, start, mid, arr);
        build(index + 2 * (mid - start + 1), mid + 1, end, arr);
        tree[index] = tree[index + 1] + tree[index + 2 * (mid - start + 1)];
    }

    T lazyQuery(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            return 0;
        }

        if (start >= l && end <= r)
        {
            return tree[index];
        }

        T mid = (start + end) / 2;
        forward(start, mid, index+1);
        forward(mid+1, end, index+2*(mid - start + 1));
        T first = lazyQuery(index + 1, start, mid, l, r);
        T second = lazyQuery(index + 2 * (mid - start + 1), mid + 1, end, l, r);
        return first + second;
    }

    void update(T index, T l, T r, T value, T start, T end)
    {
        if (end < l || start > r || start > end)
            return;
        if (start >= l && end <= r)
        {
            lazyTree[index] += value;
            forward(start, end, index);
            return;
        }

        T mid = (start + end) / 2;
        forward(start, mid, index+1);
        forward(mid+1, end, index+2*(mid - start + 1));
        if (l <= mid)
        {
            update(index + 1, l, r, value, start, mid);
        }
        if (end > mid)
        {
            update(index + 2 * (mid - start + 1), l, r, value, mid + 1, end);
        }
        tree[index] = tree[index + 1] + tree[index + 2 * (mid - start + 1)];
    }

    void forward(ll start, ll end, ll index) {
        if(lazyTree[index]!=0) {
            tree[index] += (end - start + 1) * lazyTree[index];
            if(start != end) {
                lazyTree[index+1] += lazyTree[index];
                ll mid = (start + end) / 2;
                lazyTree[index+2*(mid - start + 1)] += lazyTree[index];
            }
            lazyTree[index] = 0;
        }
    }
    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }

    T lazyQuery(T l, T r)
    {
        return lazyQuery(0, 0, this->n - 1, l, r);
    }

    void update(T l, T r, T value)
    {
        update(0, l, r, value, 0, this->n - 1);
    }
};

const int nodemax = 5e5+5;
int tin[nodemax], tout[nodemax];
vi adj[nodemax];
int timer = 0;
void dfs(int curr, int par) {
    tin[curr] = ++timer;
    for(auto i : adj[curr]) {
        dfs(i, curr);
    }
    tout[curr] = ++timer;
}
void solve()
{
    ll q;
    cin>>q;
    vvl queries;
    timer = 0;
    for(int i = 0; i <= q; i++) adj[i].clear();
    int cnt = 1;
    for(int i = 0; i < q; i++) {
        int sign;
        cin>>sign;
        vl temp;
        temp.pb(sign);
        if(sign == 1) {
            int par;
            cin>>par;
            cnt++;
            adj[par].pb(cnt);
            temp.pb(par);
        } else {
            ll node, val;
            cin>>node>>val;
            temp.pb(node); temp.pb(val);
        }
        queries.pb(temp);
    }
    dfs(1, -1);
    vl dp(timer+1, 0);
    SegmentTree<ll> segtree(dp);
    vl ans(cnt+1, 0);
    int si = cnt;
    for(int i = q-1; i >= 0; i--) {
        ll sign = queries[i][0];
        if(sign == 1) {
            ans[cnt] = segtree.lazyQuery(tin[cnt], tin[cnt]);
            cnt--;
        } else {
            ll ind = queries[i][1], val = queries[i][2];
            segtree.update(tin[ind], tout[ind], val);
        }
    }
    ans[1] = segtree.lazyQuery(tin[1], tin[1]);
    for(int i = 1; i <= si; i++) cout<<ans[i]<<" ";
    cout<<endl;
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
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    
    #ifndef ONLINE_JUDGE
    cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}