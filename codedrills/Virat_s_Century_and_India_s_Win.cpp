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

int addMod(int a, int b) {
    int c = a + b;
    if(c >= mod) c -= mod;
    return c; 
}

int subMod(int a, int b) {
    int c = a - b;
    if(c >= mod) c -= mod;
    if(c < 0) c += mod;
    return mod;
}

long long binpow(long long a, long long b, long long m) {
    if(a == 0) return 1;
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res % mod;
}

int runs[] = {1,2,3,4,6};
int invsix = binpow(6, mod-2, mod);
int dp[151][103][61][11][2][2];
ll solve(int runsLeft, int currScore, int strike, int ballsLeft, int wicketsDown, bool out, int ballOver) {
    if(runsLeft <= 0 && currScore >= 100) {
        return 1;
    }
    if(runsLeft <= 0) return 0;
    if(ballsLeft <= 0) return 0;
    if(wicketsDown >= 10) return 0;
    if(out && currScore < 100) return 0;
    // debug4(runsLeft, currScore, ballsLeft, wicketsDown);
    // debug3(strike, out, ballOver);
    // debug(dp[runsLeft][currScore][ballsLeft][wicketsDown][strike][out]);
    if(dp[runsLeft][currScore][ballsLeft][wicketsDown][strike][out] != -1) return dp[runsLeft][currScore][ballsLeft][wicketsDown][strike][out];
    int currans = 0;
    int nexball = ballOver + 1;
    if(nexball >= 6) nexball -= 6;
    if(strike) {
        currans = solve(runsLeft, currScore, 0, ballsLeft-1, wicketsDown+1, true, nexball);
    } else {
        int news = (nexball == 0);
        if(out) news = 0;
        currans = solve(runsLeft, currScore, news, ballsLeft-1, wicketsDown+1, out, nexball);
    }
    if(currans >= mod) currans = currans - mod;
    for(int i = 0; i < 5; i++) {
        int tempscore = currScore;
        if(strike) tempscore = currScore + runs[i];
        tempscore = min(tempscore, 100);
        int newStrike = strike ^ (runs[i]%2);
        if(nexball==0) newStrike ^= 1;
        if(out) newStrike = 0;
        currans = addMod(currans, solve(runsLeft-runs[i], tempscore, newStrike, ballsLeft-1, wicketsDown, out, nexball));
    }
    return dp[runsLeft][currScore][ballsLeft][wicketsDown][strike][out] = (ll)currans * invsix % mod;
}

void solve()
{
    int n,b,w,x;
    cin>>n>>b>>w>>x;
    ll temp = solve(n, x, 1, b, w, false, 6 - (b%6));
    cout<<temp<<endl;
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 1;
    cin >> t;
    memset(dp, -1, sizeof dp);

    while (t--)
    {
        solve();
    }
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    
    #ifndef ONLINE_JUDGE
    cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}