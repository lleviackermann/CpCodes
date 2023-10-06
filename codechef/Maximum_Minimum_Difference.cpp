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


ll solve2(vl &arr, ll n, ll k)
{
    ll i = 0;
    ll j = 0;
    set<pair<ll, int>> s;
    ll ans = 0;
    s.insert({arr[0], 0});
    ll a, b;
    while (i <= j && j < n && i < n)
    {
        a = (*s.begin()).first;
        b = (*(--s.end())).first;
        if (b - a <= k)
        {
            ans += j - i + 1;
            j++;
            if (j < n)
                s.insert({arr[j], j});
        }
        else
        {
            s.erase({arr[i], i});
            i++;
        }
    }
    return ans;
}

ll solve3(vl &nums, ll n, ll limit) {
    set<pair<ll, ll>> maxi;
    ll start = 0;
    ll ans = 0;
    ll prev = 0;
    for (ll end = 0; end < n; end++)
    {
        ll curr = nums[end];
        maxi.insert({curr, end});
        // mini.insert({curr, end});
        while ((*(maxi.rbegin())).first - (*maxi.begin()).first > limit)
        {
            maxi.erase({nums[prev], prev});
            // maxi.erase({nums[prev], prev});
            prev++;
        }
        ans += (end - prev + 1);
    }
    return ans;
}
int solve()
{
    ll n = 200000;
    vl nums(n);
    srand(time(0));
    ll ub = 2e9, lb = 1;
    for(int i = 0; i < n; i++) {
        nums[i] = (rand() % (ub - lb + 1)) + lb;
    }
    ll k = 1e9;
    if(solve2(nums, n, k)!=solve3(nums,n,k)) {
        cout<<n<<" "<<k<<endl;
        print(nums);
        cout<<solve2(nums,n,k)<<" "<<solve3(nums,n,k)<<endl;
        return 1;
    }
    return 0;
    // debug(n*(n+1)/2);
    
}

int main()
{
    suprit;
    clock_t start = clock();

    int t = 100;
    // cin >> t;
    while (t--)
    {
        int flag = solve();
        if(flag) break;
        // else solve();
    }
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

#ifndef ONLINE_JUDGE
// cout << setprecision(10) << elapsed << endl;
#endif
    return 0;
}