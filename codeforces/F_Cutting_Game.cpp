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

void build(int index, int start, int end, vi &ycor, vector<vector<int>> &segtree)
{
    if (start == end)
    {
        segtree[index].push_back(ycor[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(index + 1, start, mid, ycor, segtree);
    build(index + 2 * (mid - start + 1), mid + 1, end, ycor, segtree);
    int left = 0, right = 0;
    while (left < segtree[index + 1].size() && right < segtree[index + 2 * (mid - start + 1)].size())
    {
        if (segtree[index + 1][left] > segtree[index + 2 * (mid - start + 1)][right])
        {
            segtree[index].push_back(segtree[index + 2 * (mid - start + 1)][right]);
            right++;
        }
        else
        {
            segtree[index].push_back(segtree[index + 1][left]);
            left++;
        }
    }
    while (left < segtree[index + 1].size())
    {

        segtree[index].push_back(segtree[index + 1][left]);
        left++;
    }
    while (right < segtree[index + 2 * (mid - start + 1)].size())
    {
        segtree[index].push_back(segtree[index + 2 * (mid - start + 1)][right]);
        right++;
    }
}

int queries(int index, int start, int end, int low, int high, int l, int r, vector<vector<int>> &segtree)
{
    if (start > r || end < l)
        return 0;
    if(start >= l && end <= r) {
        debug3(index, start, end);
        print(segtree[index]);
        int fir = lower_bound(all(segtree[index]), low) - segtree[index].begin();
        int sec = upper_bound(all(segtree[index]), high) - segtree[index].begin();
        return sec - fir;
    }
    int mid = (start + end) / 2;
    int a = queries(index + 1, start, mid, low, high, l, r, segtree);
    int b = queries(index + 2 * (mid - start + 1), mid + 1, end, low, high, l, r, segtree);
    return a + b;
}

void solve()
{
    int a, b, m, n;
    cin >> a >> b >> m >> n;
    vpi coordinates(m);
    for (auto &i : coordinates)
        cin >> i.first >> i.second;
    sort(all(coordinates));
    // for(auto i : coordinates) {
    //     cout << i.first << " " << i.second << endl;
    // }
    vi xcor;
    for (int i = 0; i < m; i++)
    {
        xcor.pb(coordinates[i].first);
    }
    vi ycor(m);
    for (int i = 0; i < m; i++)
        ycor[i] = coordinates[i].second;
    vector<vector<int>> segtree(2 * m + 10);
    build(0, 0, m-1, ycor, segtree);
    int rs = 1, rn = a, ys = 1, yn = b;
    int cnt = 0;
    int alice = 0, bob = 0;
    // cout << endl;
    // print(xcor);
    while(n--) {
        char c;
        int k;
        cin >> c >> k;
        int val = 0;
        int mi;
        int en = upper_bound(all(xcor), rn) - xcor.begin();
        int fi = lower_bound(all(xcor), rs) - xcor.begin();
        debug4(rs, rn, ys, yn);
        if(c == 'D') {
            int mi = lower_bound(all(xcor), rn - k +1) - xcor.begin();
            debug2(mi, en);
            if(mi != en) {
                val = queries(0, 0, m-1, ys, yn, mi, en-1, segtree);
            }
            rn = rn - k;
        } else if(c == 'U') {
            int mi = upper_bound(all(xcor), rs + k - 1) - xcor.begin();
            debug2(mi, fi);
            if(mi != fi) {
                val = queries(0, 0, m-1, ys, yn, fi, mi - 1, segtree);
            }
            rs = rs + k;
        } else if(c == 'L') {
            if(fi != en) {
                val = queries(0, 0, m-1, ys, ys + k - 1, fi, en-1, segtree);
            }
            ys = ys + k;
        } else {
            debug2(fi, en);
            if(fi != en) {
                val = queries(0, 0, m-1, yn - k + 1, yn, fi, en-1, segtree);
            }
            yn = yn - k;
        }
        debug(val);
        if(cnt) bob += val;
        else alice += val;
        cnt ^= 1;
    }
    cout << alice << " " << bob << endl;
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