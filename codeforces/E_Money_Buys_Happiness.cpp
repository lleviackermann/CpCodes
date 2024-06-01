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

int m, x;
// map<pair<ll, int>, int> dp; 
// int recur(vpi &cost, int ind, int curr_happ, int curr_x) {
//     if(ind == m) {
//         return 0;
//     }
//     if(dp.count({curr_x, curr_happ})) return dp[{curr_x, curr_happ}];
//     int ans = 0;
//     ans = max(ans, recur(cost, ind+1, curr_happ, curr_x + x));
//     if(curr_x >= cost[ind].ff) ans = max(ans, cost[ind].second + recur(cost, ind+1, curr_happ + cost[ind].second, curr_x - cost[ind].first + x));
//     return dp[{curr_x, curr_happ}] = ans;
// }
ll dp[100010][51];
void solve()
{
    cin >> m >> x;
    vpi cost_happiness(m);
    for(auto &i : cost_happiness) cin >> i.first >> i.second;

    // cout << recur(cost_happiness, 0, 0, 0)  << endl;
    int total_happines = 0;
    for(auto i : cost_happiness) total_happines += i.second;
    for(int i = 0; i <= total_happines; i++) {
        for(int j = 0; j <= m; j++) {
            if(j == 0) dp[i][j] = 0;
            else dp[i][j] = -1;
        }
    }
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        int hap = cost_happiness[i-1].second, cost = cost_happiness[i-1].first;
        if(x * (i-1) >= cost) {
            dp[hap][i] = x * (i - 1) - cost;
            ans = max(ans, hap);
            debug2(i, hap);
        }
        for(int j = hap + 1; j <= total_happines; j++) {
            int prev = j - hap;
            for(int k = i - 1; k > 0; k--) {
                if(dp[prev][k] == -1) continue;
                int remian_x = x * (i - k);
                if(dp[prev][k] + remian_x >= cost) {
                    ans = max(ans, j);
                    debug2(i, j);
                    dp[j][i] = max(dp[j][i], dp[prev][k] + remian_x - cost);
                }
            }
        }
    }
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