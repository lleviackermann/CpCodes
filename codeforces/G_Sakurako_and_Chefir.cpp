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

int binpow(long long a, long long b, long long m) {
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

void solve()
{
    int n;
    cin >> n;
    vvi tre(n);
    for(int i = 1; i < n; i++) {
        int st, en;
        cin >> st >> en;
        --st, --en;
        tre[st].push_back(en);
        tre[en].push_back(st);
    }
    const int limit = 22;
    vector<int> subtree_size(n, 0), root_dist(n, 0);
    vector<vector<int>> parent(n, vi(22, -1)), ancestor_sub(n, vi(limit, 0));
    vector<array<int, 2>> max_subchild(n, {-1, -1});
    auto dfs = [&](auto&& dfs, int u, int v, int curr) -> void {
        root_dist[u] = curr;
        if(v != -1) {
            parent[u][0] = v;
            for(int i = 1; i < limit; i++) {
                if(parent[u][i-1] == -1) break;
                parent[u][i] = parent[parent[u][i-1]][i-1];
            }
        }
        for(auto neighbour : tre[u]) {
            if(neighbour != v) {
                dfs(dfs, neighbour, u, curr + 1);
                subtree_size[u] = max(subtree_size[u], 1 + subtree_size[neighbour]);
                auto &[fir, sec] = max_subchild[u];
                if(fir == -1) fir = neighbour;
                else if(subtree_size[fir] <= subtree_size[neighbour]) sec = fir, fir = neighbour;
                else if(sec == -1) sec = neighbour;
                else if(subtree_size[sec] < subtree_size[neighbour]) sec = neighbour;
            }
        }
    };
    dfs(dfs, 0, -1, 0);
    for(int i = 1; i < n; i++) {
        int par = parent[i][0];
        auto &imm_par = ancestor_sub[i][0];
        auto &[fir, sec] = max_subchild[par];
        if(fir == i) {
            if(sec == -1) imm_par = 1;
            else imm_par = 2 + subtree_size[sec];
        } else {
            imm_par = 2 + subtree_size[fir];
        }
    }
    for(int level = 1; level < limit; level++) {
        for(int node = 1; node < n; node++) {
            if(parent[node][level] == -1) continue;
            auto &left = ancestor_sub[node][level-1];
            auto &right = ancestor_sub[parent[node][level-1]][level-1];
            ancestor_sub[node][level] = max(left, binpow(2, level - 1, mod) + right);
        }
    }
    auto get_ancestor_max = [&](int node, int par) {
        int ans = 0;
        int curr = 0;
        par = min(par, root_dist[node]);
        for(int level = 21; level >= 0; level--) {
            if((par >> level) & 1) {
                ans = max(ans, curr + ancestor_sub[node][level]);
                curr += binpow(2, level, mod);
                node = parent[node][level];
            }
        }
        return ans;
    };
    int q;
    cin >> q;
    while(q--) {
        int node, par;
        cin >> node >> par;
        --node;
        cout << max(subtree_size[node], get_ancestor_max(node, par)) << " ";
    }
    cout << endl;
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