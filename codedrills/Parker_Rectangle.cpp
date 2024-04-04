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

bool validOrNot(vvi &mat)
{
    int n = mat.size();
    vl arr;
    for (int i = 0; i < n; i++)
    {
        ll sum = 0;
        for (int j = 0; j < n; j++)
            sum += mat[i][j];
        arr.pb(sum);
    }
    for (int i = 0; i < n; i++)
    {
        ll sum = 0;
        for (int j = 0; j < n; j++)
            sum += mat[j][i];
        arr.pb(sum);
    }
    sort(all(arr));
    // print(arr);
    ll ma_diff = n;
    return arr.back() - arr[0] <= ma_diff;
}
// 1 7 6
// 5 2 8
// 9 4 3
void solve()
{
    int n;
    cin >> n;
    if(n == 3) {
        cout<<"1 2\n";
        cout<<"1 2\n";
        return;
    }
    if(n == 5) {
        cout<<"2 3\n";
        cout<<"0 4 3\n";
        cout<<"5 1 2\n";
    }
    if (n & 1)
    {
        cout << "-1\n";
        return;
    }
    int row = n / 2;
    vvi mat(row, vi(row));
    int start = 1, end = row * row;
    if (row % 4 == 0 || row % 4 == 1)
    {
        for (int i = 0; i < row; i += 4)
        {
            if (i + 3 >= row)
                continue;
            for (int j = i; j < i + 4; j++)
            {
                int mid = (row / 4) * 4 / 2;
                if (j == i || j == i + 3)
                {
                    for (int k = 0; k < mid; k++)
                        mat[j][k] = start++;
                    for (int k = 2 * mid - 1; k >= mid; k--)
                        mat[j][k] = end--;
                }
                else
                {
                    for (int k = 0; k < mid; k++)
                        mat[j][k] = end--;
                    for (int k = 2 * mid - 1; k >= mid; k--)
                        mat[j][k] = start++;
                }
            }
        }
        if (row % 4)
        {
            int change = 1;
            while (change < row)
            {
                for (int i = 0; i < row; i += 2)
                {
                    swap(mat[change][i], mat[change][i + 1]);
                }
                change++;
                if (change % 4 == 3)
                    change += 2;
            }
            for (int i = 1; i < row; i += 2)
            {
                mat[row - 1][i] = start++;
            }
            for (int i = 0; i < row - 1; i++)
                mat[i][row - 1] = start++;
            for (int i = 0; i < row; i += 2)
                mat[row - 1][i] = start++;
        }
    }
    else
    {
        for (int i = 0; i < row; i += 4)
        {
            if (i + 3 >= row)
                continue;
            for (int j = i; j < i + 4; j++)
            {
                int mid = row / 2;
                if (j == i || j == i + 3)
                {
                    for (int k = 0; k < mid; k++)
                        mat[j][k] = start++;
                    for (int k = 2 * mid - 1; k >= mid; k--)
                        mat[j][k] = end--;
                }
                else
                {
                    for (int k = 0; k < mid; k++)
                        mat[j][k] = end--;
                    for (int k = 2 * mid - 1; k >= mid; k--)
                        mat[j][k] = start++;
                }
            }
        }
        if (row % 4 == 2)
        {
            for (int i = 0; i < row; i++)
            {
                if (i % 2)
                {
                    mat[row - 2][i] = start++;
                    mat[row - 1][i] = end--;
                }
                else
                {
                    mat[row - 2][i] = end--;
                    mat[row - 1][i] = start++;
                }
            }
        }
        else
        {
            int mid = row / 2;
            for (int k = 0; k < mid; k++)
                mat[row-3][k] = start++;
            for (int k = 2 * mid - 1; k >= mid; k--)
                mat[row-3][k] = end--;
            for (int k = 0; k < mid; k++)
                mat[row-2][k] = end--;
            for (int k = 2 * mid - 1; k >= mid; k--)
                mat[row-2][k] = start++;
            for(int k = mid; k < 2*mid; k++) mat[row-1][k] = start++;
            for(int k = 0; k < row-1; k++) mat[k][row-1] = start++;
            for(int k = 0; k < mid; k++) mat[row-1][k] = start++;
            mat[row-1][row-1] = start++;
        }
    }
    debug(validOrNot(mat));
    cout<<row<<" "<<row<<endl;
    for (auto r : mat)
    {
        for (auto c : r)
            cout << c << " ";
        cout << endl;
    }
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