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

struct segment {
    vpi edges;
    ll vertex;

    segment() {
        vertex = 0;
    }

    void print_() {
        debug(vertex);
        // for(auto [st, en] : edges) cout << st << " " << en << endl;
    }
};


void solve()
{
    ll n, m, c;
    cin >> n >> m >> c;

    vvi graph(n);
    auto add_edge = [&](int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    };
    vpi edges;
    for(int i = 1; i <= m; i++) {
        int xt, en;
        cin >> xt >> en;
        add_edge(--xt, --en);
        edges.push_back({xt, en});
    }
    vector<segment> arr;

    int cnt = 0;
    int num = -1;
    vi segnum(n, 0);
    vi visited(n, 0);
    auto dfs = [&](auto&& dfs, int u) -> void {
        visited[u] = 1;
        cnt++;
        segnum[u] = num;
        for(auto nei : graph[u]) {
            if(visited[nei]) continue;
            dfs(dfs, nei);
        }
    };
    for(int i = 0; i < n; i++) {
        if(visited[i]) continue;
        num++;
        cnt = 0;
        dfs(dfs, i);
        segment temp;
        temp.vertex = cnt;
        arr.push_back(temp);
    }
    debug(num);
    for(auto [st, en] : edges) {
        arr[segnum[st]].edges.push_back({st, en});
    }
    int st = -1, en = -1;
    cnt = 0;
    auto check = [&](auto&& check, int u) -> void {
        visited[u] = 1;
        cnt++;
        for(auto nei : graph[u]) {
            if(visited[nei] || (st == u && en == nei) || (st == nei && en == u)) continue;
            check(check, nei);
        }
    };
    int ind = -1;
    ll ans = 1e18;
    auto calc = [&](ll x, ll num) -> ll {
        return x * x + num * num;
    };
    for(auto seg : arr) {
        ++ind;
        vi tem;
        for(int i = 0; i < arr.size(); i++) {
            if(i != ind) tem.push_back(arr[i].vertex);
        }
        sort(all(tem));
        vi nodes(n+1, 0);
        nodes[0] = 1;
        for(auto it : tem) {
            for(int i = n-it; i >= 0; i--) nodes[i+it] |= nodes[i];
        }
        ll remain = n - seg.vertex;
        for(auto [fir, sec] : seg.edges) {
            visited.clear();
            visited.resize(n, 0);
            st = fir, en = sec;
            cnt = 0;
            check(check, fir);
            debug3(fir, sec, cnt);
            if(cnt == seg.vertex) continue;
            for(int i = 0; i <= remain; i++) {
                if(nodes[i]) {
                    seg.print_();
                    debug(i);
                    ans = min({ans, calc(cnt + i, seg.vertex - cnt + remain - i), calc(cnt + remain - i, seg.vertex - cnt + i)});
                }
            }
        }
    }
    debug(ans);
    if(num) {
        vi tem;
        for(int i = 0; i < arr.size(); i++) {
            tem.push_back(arr[i].vertex);
        }
        sort(all(tem));
        print(tem);
        vi nodes(n+1, 0);
        nodes[0] = 1;
        for(auto it : tem) {
            for(int i = n-it; i >= 0; i--) nodes[i+it] |= nodes[i];
        }
        print(nodes);
        for(int i = 1; i <= n; i++) {
            if(nodes[i]) ans = min(ans, calc(i, n - i));
        }
        debug(ans);
    }
    if(ans == 1e18) ans = -1;
    else ans += c * num;
    cout << ans << endl;
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