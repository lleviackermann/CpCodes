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

int dp[4][4][100001];

string s, t;
int n;
vi fir, sec;

int recur(int ind, int row_mask, int col_mask) {
    if(ind == n) {
        // cout << ind << " " << row_mask << " " << col_mask << endl;
        if(row_mask == 3 && col_mask == 3) return 0;        
        return -1e9;
    }
    if(dp[row_mask][col_mask][ind] != -1) return dp[row_mask][col_mask][ind];
    int ans = 0;
    if(row_mask == 0) {
        if(col_mask == 2) {
            int sum = fir[ind-1] + fir[ind-2] + fir[ind];
            int flag = (sum >= 2 ? 1 : 0);
            ans = max(ans, flag + recur(ind+1, 3, 0));
        } else if(col_mask == 0) {
            int sum = fir[ind-1] + fir[ind-2] + fir[ind];
            int sum2 = sec[ind-1] + sec[ind-2] + sec[ind];
            int flag = sum / 2 + sum2 / 2;
            ans = max(ans, flag + recur(ind+1, 3, 3));
        } else if(col_mask == 3) {
            int sum = fir[ind-1] + fir[ind-2] + fir[ind];
            int flag = sum / 2;
            ans = max(ans, flag + recur(ind+1, 3, 2));
        }
    } else if(row_mask == 2) {
        if(col_mask == 2) {
            int sum = fir[ind-1] + sec[ind-1];
            int flag1 = (sum + fir[ind]) / 2;
            ans = max(ans, flag1 + recur(ind+1, 3, 2));
            flag1 = (sum + sec[ind]) / 2;
            ans = max(ans, flag1 + recur(ind+1, 2, 3));
            ans = max(ans, recur(ind+1, 0, 0));
        } else if(col_mask == 3) {
            ans = max(ans, recur(ind+1, 0, 2));
            int flag = (fir[ind-1] + fir[ind] + sec[ind]) / 2;
            ans = max(ans, flag + recur(ind + 1, 3, 3));
        } else if(col_mask == 0) {
            int flag = (sec[ind-2] + sec[ind-1] + sec[ind]) / 2;
            ans = max(ans, flag + recur(ind+1, 0, 3));
        }
    } else if(row_mask == 3) {
        if(col_mask == 2) {
            ans = max(ans, recur(ind + 1, 2, 0));
            int flag = (fir[ind] + sec[ind-1] + sec[ind]) / 2;
            ans = max(ans, flag + recur(ind+1, 3, 3));
        } else if(col_mask == 3) {
            ans = max(ans, recur(ind+1, 2, 2));
        } else if(col_mask == 0) {
            int flag = (sec[ind-2] + sec[ind-1] + sec[ind]) / 2;
            ans = max(ans, flag + recur(ind + 1, 2, 3));
        }
    }
    debug4(ind, row_mask, col_mask, ans);
    return dp[row_mask][col_mask][ind] = ans;
}

void solve()
{
    cin >> n;
    cin >> s >> t;
    fir.clear();
    sec.clear();
    fir.resize(n, 0);
    sec.resize(n, 0);
    for(int i = 0; i < n; i++) {
        if(s[i] == 'A') fir[i] = 1;
        if(t[i] == 'A') sec[i] = 1;
    }
    // memset(dp, -1, sizeof(dp));
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) for(int k = 0; k < n; k++) dp[i][j][k] = -1;
    }

    cout << recur(0, 3, 3) << endl;
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