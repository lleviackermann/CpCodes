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

const int nmax = 6;
vector<vector<int>> mat(nmax, vi(nmax + 1, 0));
vector<vector<int>> visited(6, vi(7, -1));

int dp[7][7][7][7][7][7][7][2];

bool won(int row, int col, int sign) {
    for(int i = -3; i <= 0; i++) {
        int hor = 0, vert = 0, diag = 0;
        for(int j = i; j < i + 4; j++) {
            //hor
            int ny = col + j, nx = row;
            if(ny >= 7 || ny < 0 || visited[nx][ny] != sign) {}
            else hor++;
            nx = row + j, ny = col;
            if(nx >= 6 || nx < 0 || visited[nx][ny] != sign) {}
            else vert++;
            nx = row + j, ny = col + j;
            if(nx >= 6 || nx < 0 || ny >= 7 || ny < 0 || visited[nx][ny] != sign) {}
            else diag++;
        }
        if(hor == 4 || vert == 4 || diag == 4) return true;
    }
    return false;
}

vi las(7, 5);

set<int> se;
int recur(int per) {
    if(dp[las[0]+1][las[1]+1][las[2]+1][las[3]+1][las[4]+1][las[5]+1][las[6]+1][per] != -1) return 1;
    for(int i = 0; i < 7; i++) {
        if(las[i] != -1) {
            if(mat[las[i]][i] == per) {
                visited[las[i]][i] = per;
                if(won(las[i], i, per)) {
                    se.insert(per);
                    // return dp[las[0]+1][las[1]+1][las[2]+1][las[3]+1][las[4]+1][las[5]+1][las[6]+1][per] = 1;
                    continue;
                }
                las[i]--;
                recur(per^1);
                las[i]++;
                visited[las[i]][i] = -1;
            }
        }
    }
    return dp[las[0]+1][las[1]+1][las[2]+1][las[3]+1][las[4]+1][las[5]+1][las[6]+1][per] = 1;
}

int tt = 0;
void solve()
{
    tt++;
    for(int i = 0; i < 6; i++) {
        string s;
        cin >> s;
        // cout << s << endl;
        for(int j = 0; j < 7; j++) {
            if(s[j] == 'F') mat[i][j] = 1;
            else mat[i][j] = 0;
            visited[i][j] = -1;
        }
    }
    se.clear();
    las.clear();
    las.resize(7, 5);
    memset(dp, -1, sizeof(dp));
    recur(0);
    char ans = '0';
    if(se.size() == 2) ans = '?';
    else if(se.size() == 1) {
        if(*se.begin() == 0) ans = 'C';
        else ans = 'F';
    } 
    cout << "Case #" << tt << ": " << ans << endl;
}

int main()
{ 
    suprit;

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}