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


void solve()
{
    int n, q;
    cin >> n >> q;
    vi colors(n+1, 0);
    for(int i = 1; i <= n; i++) cin >> colors[i];
    vvi tree(n+1);
    for(int i = 1; i < n; i++) {
        int st, en;
        cin >> st >> en;
        tree[st].pb(en);
        tree[en].pb(st);
    }
    vi parent(n+1);
    int black_vertex = 0, sum_two = 0, sum_more = 0, tot = 0, par_white = 0;
    vi subtree(n+1, 0);
    auto dfs = [&](auto&& dfs, int u, int v) -> void {
        parent[u] = v;
        int sum = 0;
        tot += colors[u];
        for(auto nei : tree[u]) {
            if(nei == v) continue;
            dfs(dfs, nei, u);
            sum += colors[nei];
        }
        if(colors[u] && colors[v] == 0) par_white++;
        if(colors[u]) {
            if(sum == 2) black_vertex ^= u, sum_two++;
            if(sum > 2) sum_more++;
        }
        subtree[u] = sum;

    };
    dfs(dfs, 1, 0);
    print(parent);
    auto flip = [&](int node) {
        colors[node] ^= 1;
        int diff = (colors[node] ? 1 : -1);
        int pa = parent[node];
        if(colors[pa] == 0) par_white += diff;
        if(subtree[node] == 2) sum_two += diff, black_vertex ^= node;
        else if(subtree[node] > 2) sum_more += diff;
        tot += diff;
        par_white -= diff * subtree[node];  
        if(colors[node]) {
            if(colors[pa] && subtree[pa] == 2) sum_two--, sum_more++, black_vertex ^= pa;
            subtree[pa]++;
            if(colors[pa] && subtree[pa] == 2) sum_two++, black_vertex ^= pa;
        } else {
            if(colors[pa] && subtree[pa] == 2) sum_two--, black_vertex ^= pa;
            subtree[pa]--;
            if(colors[pa] && subtree[pa] == 2) sum_two++, sum_more--, black_vertex ^= pa;
        }
    };

    auto check = [&]() -> bool {
        if(!tot || sum_more || sum_two > 1 || par_white > 1 || (sum_two && colors[parent[black_vertex]] == 1)) return false;
        return true;
    };
    while(q--) {
        int x;
        cin >> x;
        flip(x);
        debug4(tot, sum_more, sum_two, par_white);
        debug(black_vertex);
        if(check()) cout << "Yes\n";
        else cout << "No\n";
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