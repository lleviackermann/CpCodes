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
    ll n;
    cin >> n;
    vpl center(n);
    vl radii(n);
    for(int i = 0; i < n; i++) cin >> center[i].ff >> center[i].ss >> radii[i];
    vvi graph(n);
    auto istangent = [&](int i, int j) -> bool {
        auto [x1, y1] = center[i];
        auto [x2, y2] = center[j];
        ll center_dist = (x2-x1) * (x2-x1) + (y2-y1) * (y2 - y1);
        ll radii_dist = (radii[i] + radii[j]) * (radii[i] + radii[j]);
        return center_dist == radii_dist;
    };
    auto add_edge = [&](int i, int j) {
        graph[i].push_back(j);
        graph[j].push_back(i);
    };

    vi colors(n, -1);
    auto assign_colors = [&](auto&& assign_colors, int u, int color) -> bool {
        // debug2(u, color);
        colors[u] = color;
        bool flag = true;
        for(auto nei : graph[u]) {
            if(colors[nei] == -1) flag = flag && assign_colors(assign_colors, nei, color^1);
            else if(colors[nei] == color) return false;
        }
        return flag;
    };
    vi visited(n, 0);
    auto sum = [&](auto&& sum, int u) -> int {
        // debug(u);
        int ans = (colors[u] ? 1 : -1);
        visited[u] = 1;
        for(auto it : graph[u]) {
            if(visited[it]) continue;
            ans += sum(sum, it);
        }
        colors[u] = -1;
        return ans;
    };

    auto dfs = [&](auto&& dfs, int u, vi& tem) -> void {
        tem[u] = 1;
        for(auto it : graph[u]) {
            if(tem[it]) continue;
            dfs(dfs, it, tem);
        }
    };
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(istangent(i, j)) {
                add_edge(i, j);
            }
        }
    }
    // for(int i = 0; i < n; i++) {
    //     cout << i << "->";
    //     print(graph[i]);
    // }
    for(int i = 0; i < n; i++) {
        if(visited[i]) continue;
        vi tem = visited;
        bool flag = assign_colors(assign_colors, i, 0);
        if(flag && sum(sum, i) > 0) {
            debug3(i, sum(sum, i), n);
            cout << "YES\n";
            return;
        }
        visited.clear();
        visited.resize(n, 0);
        flag = assign_colors(assign_colors, i, 1);
            print(colors);
        if(flag && sum(sum, i) > 0) {
            debug3(i, sum(sum, i), -n);
            cout << "YES\n";
            return;
        }
        dfs(dfs, i, tem);
        visited = tem;
    }
    cout << "NO\n";

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