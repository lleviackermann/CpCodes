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


vi order;
set<int> graph[1002];
set<int> rev_graph[1002];
vi used;
void dfs1(int u) {
    used[u] = 1;
    // print(graph[u]);
    for(auto nei : graph[u]) {
        if(!used[nei]) dfs1(nei);
    }
    order.push_back(u);
}

int cnt = 0;
vi comp(1005, 0);
void dfs2(int u) {
    comp[u] = cnt;
    for(auto i : rev_graph[u]) {
        if(comp[i] == 0) dfs2(i);
    }
}


void solve()
{
    int n;
    cin >> n;
    vvi arr(n, vi(3));
    for(int i = 0; i < 3; i++) for(int j = 0; j < n; j++) cin >> arr[j][i];
    for(int i = 0; i < 2*n+1; i++) graph[i].clear();
    for(int i = 0; i < 2*n+1; i++) rev_graph[i].clear();
    comp.clear();
    used.clear();
    comp.resize(n*2+10, 0);
    used.resize(n*2+10, 0);
    cnt = 0;
    order.clear();
    auto calc = [&](int x) {
        return (x < 0 ? abs(x) + n : x);
    };


    auto add_edge = [&](int x, int y) {
        // debug2(x, y);
        // debug4(calc(-x), calc(-y), calc(x), calc(y));
        graph[calc(-x)].insert(calc(y));
        graph[calc(-y)].insert(calc(x));
        rev_graph[calc(y)].insert(calc(-x));
        rev_graph[calc(x)].insert(calc(-y));
    };

    auto print_graph = [&](set<int> temp[]) {
        for(int i = 1; i <= 2*n; i++) {
            cout << i << "->";
            print(temp[i]);
        }
    };

    for(int i = 0; i < n; i++) {
        auto& vec = arr[i];
        add_edge(vec[0], vec[1]);
        add_edge(vec[0], vec[2]);
        add_edge(vec[1], vec[2]);
    }
    // print_graph(graph);
    // print_graph(rev_graph);
    for(int i = 1; i <= 2*n; i++) {
        debug2(i, used[i]);
        if(!used[i]) dfs1(i);
        // if(!used[i+n]) dfs1(i+n);
    }
    print(order);
    while(order.size()) {
        int bac = order.back();
        order.pop_back();
        if(comp[bac] != 0) continue;
        cnt++;
        dfs2(bac);
    }
    for(int i = 1; i <= n; i++) debug2(comp[i], comp[i+n]);
    for(int i = 1; i <= n; i++) {
        if(comp[i] == comp[i+n]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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