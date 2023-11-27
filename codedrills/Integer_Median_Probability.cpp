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

const ll mod = 998244353;

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

long long binpow(long long a, long long b, long long m)
{
    a %= m;
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

#define NMAX 500005
int fact[NMAX];
int inverse[NMAX];
int invfact[NMAX];

void precompute()
{
    fact[0] = 1;
    for (int i = 1; i < NMAX; i++)
        fact[i] = (ll)fact[i - 1] * i % mod;
    invfact[NMAX - 1] = binpow(fact[NMAX - 1], mod - 2, mod);
    for (int i = NMAX - 2; i >= 1; i--)
        invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
    for (int i = 0; i < NMAX; i++)
    {
        inverse[i] = binpow(i, mod - 2, mod);
    }
}

int nCr(int n, int r)
{
    int temp = (ll)fact[n] * invfact[r] % mod;
    temp = (ll)temp * invfact[n - r] % mod;
    return temp;
}

int suffix[NMAX], prefix[NMAX];

void solve()
{
    ll n, m;
    cin >> n >> m;
    if (n % 2)
    {
        cout << "1\n";
        return;
    }
    precompute();
    int half = n / 2;
    for(int i = 1; i <= m; i++) {
        int left = i - 1;
        prefix[i] = (binpow(i, half, mod) - binpow(i - 1, half, mod) + mod);
        if(prefix[i] >= mod) prefix[i] -= mod;
        left = m - i + 1;
        suffix[i] = (binpow(left, half, mod) - binpow(left - 1, half, mod) + mod);
        if(suffix[i] >= mod) suffix[i] -= mod;
    }
    // for(int i = 1; i <= m; i++) cout<<prefix[i]<<" "<<suffix[i]<<endl;
    for(int i = m-2; i >= 1; i--) {
        suffix[i] += suffix[i+2];
        suffix[i] %= mod;
    }
    ll ans = binpow(m, n, mod);
    ll deno = binpow(ans, mod - 2, mod);
    int choose = nCr(n, half);
    // debug(choose);
    for(int i = 1; i < m; i++) {
        ll temp = (ll)choose * prefix[i] % mod;
        temp = temp * suffix[i+1] % mod;
        // debug2(i, temp);
        ans = (ans - temp + mod);
        if(ans >= mod) ans -= mod;
    }
    // cout<<ans<<endl;
    // debug(ans);
    cout<<ans * deno % mod<<endl;
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
