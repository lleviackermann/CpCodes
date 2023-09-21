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
#define suprit                    \
    ios_base::sync_with_stdio(0); \
    cout.tie(0);                  \
    cin.tie(0);
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

template <typename T>
void read(T i, T n, vector<T> &arr)
{
    for (T j = i; j < n; j++)
        cin >> arr[j];
}
template <typename T>
void read(vector<T> &arr)
{
    for (auto &j : arr)
        cin >> j;
}

#ifndef ONLINE_JUDGE

template <typename T, typename V>
void print(set<pair<T, V>> &arr)
{
    for (auto &it : arr)
        cout << it.first << " " << it.second << endl;
    line
}
template <typename T, typename V>
void print(pair<T, V> &pa) { cout << pa.first << " " << pa.second << endl; }
template <typename T>
void print(T i, T last, vector<T> &arr)
{
    for (T j = i; j < last; j++)
        cout << arr[j] << " ";
    line
}
template <typename T>
void print(T i, vector<T> &arr)
{
    for (T j = i; j < arr.size(); j++)
        cout << arr[j] << " ";
    line
}
template <typename T>
void print(vector<T> &arr)
{
    for (auto &i : arr)
        cout << i << " ";
    line
}
template <typename T, typename V>
void print(unordered_map<T, V> &arr)
{
    for (auto &it : arr)
        cout << it.first << " " << it.second << endl;
    line
}
template <typename T, typename V>
void print(map<T, V> &arr)
{
    for (auto &it : arr)
        cout << it.first << " " << it.second << endl;
}
template <typename T>
void print(unordered_set<T> &arr)
{
    for (auto &it : arr)
        cout << it << " ";
    line
}
template <typename T>
void print(ordered_set<T> &arr)
{
    for (auto &it : arr)
        cout << it << " ";
    line
}
template <typename T>
void print(set<T> &arr)
{
    for (auto &it : arr)
        cout << it << " ";
    line
}
template <typename T, typename... Args>
void print(T t, Args... args)
{
    cout << t << " ";
    print(args...);
}
template <typename T>
void print(T t) { cout << t << "\n"; }
#define debug(x) cout << #x << " " << x << endl;
#define debug2(x, y) cout << #x << " " << x << " " << #y << " " << y << endl;
#define debug3(x, y, z) cout << #x << " " << x << " " << #y << " " << y << " " << #z << " " << z << endl;
#define debug4(x, y, z, a) cout << #x << " " << x << " " << #y << " " << y << " " << #z << " " << z << " " << #a << " " << a << endl;

#else

#define print(x)
#define debug(x)
#define debug2(x, y)
#define debug3(x, y, z)
#define debug4(x, y, z, a)

#endif

int ans = 1e9;
string finalAns = "";
int dp[4][20][10][10];
int recur(string low, string high, int ind, int bound, int hnum, int lownum, int flag, string &curr)
{
    
    debug(bound);
    if (ind == low.size())
    {
        debug4(curr, hnum, lownum, ind);
        if(ans > hnum-lownum) {
            finalAns = curr;
            ans = hnum - lownum;
        }
        return dp[bound][ind][hnum][lownum] = hnum-lownum;
    }
    if(lownum != 1e9 && dp[bound][ind][hnum][lownum]!=-1) return dp[bound][ind][hnum][lownum];
    int lb, ub;
    if (bound == 3)
        lb = low[ind] - '0', ub = high[ind] - '0';
    else if (bound == 2)
        lb = 0, ub = high[ind] - '0';
    else if (bound == 1)
        lb = low[ind] - '0', ub = 9;
    else
        lb = 0, ub = 9;
    debug3(bound,lb,ub);
    int temp = 1e9;
    for (int i = lb; i <= ub; i++)
    {
        int newBound = 0;
        if (bound == 3)
        {
            if (low[ind] == high[ind])
                newBound = 3;
            else if (i == lb)
                newBound = 1;
            else if (i == ub)
                newBound = 2;
        }
        else if (bound == 2)
        {
            if (i == ub)
                newBound = 2;
        }
        else if (bound == 1)
        {
            if (i == lb)
                newBound = 1;
        }
        int ano;
        if(flag > ind) ano = (ind == 0 ? 1 : 0);
        else {
            if(flag == ind) ano = i;
            else ano = min(lownum, i);
        }
        curr.push_back(to_string(i)[0]);
        int x = recur(low, high, ind + 1, newBound, max(hnum, i), ano, flag, curr);
        curr.pop_back();
        temp = min(temp, x);
    }
    if(lownum != 1e9) dp[bound][ind][hnum][lownum] = temp;
    else dp[bound][ind][ub][lb] = temp;
    return temp;
}

ll conver(string s) {
    int n = s.size();
    ll num = 0;
    for(int i = 0; i < n; i++) {
        num = num * 10 + (s[i]-'0');
    }
    return num;
}
void solve()
{
    ll n, m;
    cin >> n >> m;
    string low = to_string(n);
    string high = to_string(m);
    int flag = high.size() - low.size();
    while (low.size() < high.size())
    {
        low = "0" + low;
    }
    // debug2(low, high);
    memset(dp, -1, sizeof dp);
    string curr = "";
    ans = 1e9;
    finalAns = "";
    recur(low, high, 0, 3, 0, 1e9, flag, curr);
    ll temp = conver(finalAns);
    cout << temp << endl;
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
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

#ifndef ONLINE_JUDGE
    cout << setprecision(10) << elapsed << endl;
#endif
    return 0;
}