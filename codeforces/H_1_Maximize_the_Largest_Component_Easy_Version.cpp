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
    ll n, m;
    cin >> n >> m;
    vector<string> matrix(n);
    read(matrix);
    vector<vector<int>> store(n, vi(m, -1));

    int num = 0, cnt = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    // map<int, int> st;
    vector<int> st;
    st.push_back(0);
    auto dfs = [&](auto&& dfs, int i, int j) -> void {
        cnt++;
        store[i][j] = num;
        for(int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            if(ni < 0 || ni >= n || nj < 0 || nj >= m || matrix[ni][nj] == '.' || store[ni][nj] != -1) continue;
            dfs(dfs, ni, nj);
        }
    };

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(matrix[i][j] == '.' || store[i][j] != -1) continue;
            num++, cnt = 0;
            // debug4(i, j, num, cnt);
            dfs(dfs, i, j);
            st.push_back(cnt);
        }
    }
    int ans = 0;
    for(auto freq : st) ans = max(ans, freq);
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         cout << store[i][j] << " ";
    //     }
    //     line
    // }
    for(int i = 0; i < n; i++) {
        cnt = 0;
        set<int> count;
        for(int j = 0; j < m; j++) {
            if(store[i][j] == -1) cnt++;
            else if(count.count(store[i][j]) == 0) {
                count.insert(store[i][j]);
                cnt += st[store[i][j]];
            }
            if(i) {
                if(store[i-1][j] != -1 && count.count(store[i-1][j]) == 0) {
                    count.insert(store[i-1][j]);
                    cnt += st[store[i-1][j]];
                }
            }
            if(i != n-1) {
                if(store[i+1][j] != -1 && count.count(store[i+1][j]) == 0) {
                    count.insert(store[i+1][j]);
                    cnt += st[store[i+1][j]];
                }
            }
        }
        ans = max(ans, cnt);
    }
    for(int j = 0; j < m; j++) {
        cnt = 0;
        set<int> count;
        for(int i = 0; i < n; i++) {
            if(store[i][j] == -1) cnt++;
            else if(count.count(store[i][j]) == 0) {
                count.insert(store[i][j]);
                cnt += st[store[i][j]];
            }
            if(j) {
                if(store[i][j-1] != -1 && count.count(store[i][j-1]) == 0) {
                    count.insert(store[i][j-1]);
                    cnt += st[store[i][j-1]];
                }
            }
            if(j != m-1) {
                if(store[i][j+1] != -1 && count.count(store[i][j+1]) == 0) {
                    count.insert(store[i][j+1]);
                    cnt += st[store[i][j+1]];
                }
            }
        }
        ans = max(ans, cnt);
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