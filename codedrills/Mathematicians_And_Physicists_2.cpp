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
#define tree sjf
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

const int nmax = 1e5 + 5;
int dp[nmax][2];
int tree[2 * nmax][2];
int n, q;

void build(int index, int start, int end)
{
    if (start == end)
    {
        tree[index][0] = dp[start][0];
        tree[index][1] = dp[start][1];
        return;
    }
    int mid = (start + end) / 2;
    build(index + 1, start, mid);
    build(index + 2 * (mid - start + 1), mid + 1, end);
    tree[index][0] = (tree[index + 1][0] + tree[index + 2 * (mid - start + 1)][0]) % mod;
    tree[index][1] = (tree[index + 1][1] + tree[index + 2 * (mid - start + 1)][1]) % mod;
}

int query(int index, int start, int end, int l, int r, int flag)
{
    if (start > r || end < l)
    {
        return 0;
    }
    if (start >= l && end <= r)
        return tree[index][flag];

    int mid = (start + end) / 2;
    int first = query(index + 1, start, mid, l, r, flag);
    int second = query(index + 2 * (mid - start + 1), mid + 1, end, l, r, flag);
    return (first + second) % mod;
}

void update(int index, int target, int value, int start, int end, int flag)
{
    if (start == end)
    {
        tree[index][flag] = value;
        return;
    }

    int mid = (start + end) / 2;
    if (target <= mid)
    {
        update(index + 1, target, value, start, mid, flag);
    }
    else
    {
        update(index + 2 * (mid - start + 1), target, value, mid + 1, end, flag);
    }
    tree[index][0] = (tree[index + 1][0] + tree[index + 2 * (mid - start + 1)][0]) % mod;
    tree[index][1] = (tree[index + 1][1] + tree[index + 2 * (mid - start + 1)][1]) % mod;
}

void build()
{
    build(0, 0, n);
}

int query(int l, int r, int flag)
{
    return query(0, 0, n, l, r, flag);
}

void update(int target, int value, int flag)
{
    update(0, target, value, 0, n, flag);
}

void solve()
{
    cin >> n >> q;
    vector<int> left(n + 1, -1);
    vpi queries;
    for (int i = 0; i < q; i++)
    {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1)
            left[l] = max(r, left[l]);
        else
            queries.push_back({l, r});
    }
    vector<int> mapped(n + 1);
    int prev = -1;
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i <= prev)
            mapped[i] = count, prev = max(prev, left[i]);
        else
            prev = left[i], mapped[i] = ++count;
    }
    // print(mapped);
    for (auto &[fir, sec] : queries)
    {
        fir = mapped[fir], sec = mapped[sec];
        // cout << fir << " " << sec << endl;
    }
    n = count;
    left.clear();
    left.resize(n + 1, -1);
    for (auto [fir, sec] : queries)
    {
        left[sec] = max(fir, left[sec]);
    }
    // vector<int>
    for (int i = 0; i < nmax; i++)
        for (int j = 0; j < 2; j++)
            dp[i][j] = 0;
    if (left[1] != 1)
        dp[1][0] = 1, dp[1][1] = 1;
    else
    {
        cout << "0\n";
        return;
    }
    build();
    // print(left);
    prev = 1;
    // cout<<tree[0][1]<<endl;
    for (int i = 2; i <= n; i++)
    {
        if (left[i] == i)
        {
            cout << "0\n";
            return;
        }
        if (left[i] == -1)
        {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
        }
        else
        {
            int sum; 
            // if(prev > left[i]) {
            //     int sum = query(prev, i-1, 0) + query(prev, i - 1, 1);
            //     sum %= mod;
            //     dp[i][0] = sum, dp[i][1] = sum;
            // } else {
                dp[i][1] = query(max(left[i],prev), i - 1, 0);
                dp[i][0] = query(max(left[i],prev), i - 1, 1);
            // }
            prev = left[i];
        }
        update(i, dp[i][0], 0);
        update(i, dp[i][1], 1);
        // cout << dp[i][0] << " " << dp[i][1] << endl;
    }
    cout << (dp[n][0] + dp[n][1]) % mod << endl;
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
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

#ifndef ONLINE_JUDGE
    cout << setprecision(10) << elapsed << endl;
#endif
    return 0;
}