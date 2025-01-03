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

vector<string> mat;
int n, m;

int directionr(int i, int j, int current) {
    int type = 2;
    assert(mat[i][j] != '.');
    if(mat[i][j] == '/') type = 1;
    if(type == 1) {
        if(current == 0) return 3;
        else if(current == 1) return 2;
        else if(current == 2) return 1;
        return 0;
    } else {
        if(current < 2) return current ^ 1;
        else {
            return (current == 2 ? 3 : 2);
        }
    }
    return -1;
}

bool movePos(int i_, int j_, int dir) {
    vector<vector<vector<int>>> visited(4, vector<vector<int>>(n, vector<int>(m, 0)));
    array<int, 3> temp = {i_, j_, dir};
    bool fl = false;
    if(i_ == 1 && j_ == 0) fl = true;
    while(temp[0] >= 0 && temp[0] < n && temp[1] >= 0 && temp[1] < m) {
        auto &[f, s, d] = temp;
        if(fl) debug3(f, s, d);
        if(visited[d][f][s]) break;
        visited[d][f][s] = 1;
        if(mat[f][s] != '.') {
            d = directionr(f, s, d);
        }
        if(d == 0) f++;
        else if(d == 1) s++;
        else if(d == 2) f--;
        else s--;
        
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == '.') continue;
            bool check = false;
            for(int k = 0; k < 4; k++) if(visited[k][i][j]) check = true;
            if(!check) {
                if(fl) debug2(i, j);
                return false;
            }
        }
    }
    return true;
}

void solve()
{
    cin >> n >> m;
    mat.resize(n);
    read(mat);
    // for(auto st : mat) cout << st << endl;
    vector<string> ans;
    for(int i = 0; i < m; i++) {
        if(movePos(0, i, 0)) ans.push_back("N" + to_string(i + 1));
        if(movePos(n-1, i, 2)) ans.push_back("S" + to_string(i + 1));
    }
    for(int i = 0; i < n; i++) {
        if(movePos(i, 0, 1)) ans.push_back("W" + to_string(i + 1));
        if(movePos(i, m-1, 3)) ans.push_back("E" + to_string(i + 1));
    }
    cout << ans.size() << endl;
    for(auto fi : ans) cout << fi << " ";
    cout << endl;
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