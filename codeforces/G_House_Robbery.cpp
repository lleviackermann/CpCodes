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

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int low = 1, high = 1e6+10;
    int ans = -1;
    string x(n, '1');
    if (n == 1 || x == s)
    {
        cout << 0 << endl;
        return;
    }
    // string tem = "1" + s + "1";
    auto nex = [](int num)
    {
        return (num + 1) / 2;
    };
    int fir = -1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            fir = i;
            break;
        }
    }
    auto binary = [&](int mid)
    {
        // string tem = "1" + s + "1"
        int flag;
        if(fir == 0) flag = 0;
        else {
            if(fir + 1 <= mid) flag = 0;
            else if(fir <= mid) flag = 1;
            else return false;
        }
        int cnt = 0;
        for (int i = fir + 1; i < n; ++i)
        {
            if (s[i] == '0')
                cnt++;
            else
            {
                if (cnt == 0)
                {
                    flag = 0;
                    continue;
                }
                if (flag)
                {
                    if (nex(cnt) + 1 <= mid)
                        flag = 0;
                    else if (nex(cnt - 1) + 1 <= mid)
                        flag = 1;
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    if (nex(cnt - 1) + 1 <= mid)
                        flag = 0;
                    else if (nex(cnt) <= mid)
                        flag = 1;
                    else
                    {
                        return false;
                    }
                }
                // if(cnt == 0)
                cnt = 0;
            }
        }
        if (cnt == 0)
        {
            return true;
        }
        if (flag)
        {
            if (cnt + 1 <= mid)
                flag = 0;
            else
            {
                return false;
            }
        }
        else
        {
            if (cnt <= mid)
                flag = 0;
            else
            {
                return false;
            }
        }
        return true;
    };
    while (low <= high)
    {
        int mid = (low + high) / 2;
        bool ret = binary(mid);
        debug2(mid, ret);
        if (binary(mid))
            ans = mid, high = mid - 1;
        else
            low = mid + 1;
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