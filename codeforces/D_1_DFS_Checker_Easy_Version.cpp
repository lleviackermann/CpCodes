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
#define tree ldsafjdkjf
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

int power2[26];

int k;

bool match(pi &fir, pi &sec)
{
    return (fir.ff == sec.ff && fir.ss == sec.ss) || (fir.ss == sec.ff && fir.ff == sec.ss);
}

void solve()
{
    int n, q;
    cin >> n >> q;
    k = log2(n) + 1;
    vi parents(n+1, -1);
    for(int i = 2; i <= n; i++) cin >> parents[i];
    print(parents);
    vi permute(n+1, 0);
    for(int i = 1; i <= n; i++) cin >> permute[i];
    vi per_parents(n+1, -1), lvl(n+1, -1);
    queue<pi> store;
    store.push({1, 1});
    lvl[1] = 1;
    while(store.size()) {
        auto [ind, level] = store.front();
        store.pop();
        if(level == k) continue;
        int left = ind+1, right = ind + power2[k - level];
        per_parents[permute[left]] = permute[ind];
        per_parents[permute[right]] = permute[ind];
        lvl[left] = level + 1, lvl[right] = level + 1;
        if(level == k-1) continue;
        store.push({left, level+1});
        store.push({right, level+1});
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++) cnt += (parents[i] == per_parents[i]);
    print(per_parents);
    print(lvl);
    while(q--) {
        // line
        int a, b;
        cin >> a >> b;
        set<int> check;
        check.insert(permute[a]);
        check.insert(permute[b]);
        if(lvl[a] != k) {
            check.insert(permute[a+1]);
            check.insert(permute[a + power2[k - lvl[a]]]);
        }   
        if(lvl[b] != k) {
            check.insert(permute[b+1]);
            check.insert(permute[b + power2[k - lvl[b]]]);
        }     
        int ct = 0;
        for(auto chi : check) ct += (parents[chi] == per_parents[chi]);
        if(lvl[a] != k) {
            per_parents[permute[a+1]] = permute[b];
            per_parents[permute[a + power2[k - lvl[a]]]] = permute[b];
        }
        if(lvl[b] != k) {
            per_parents[permute[b+1]] = permute[a];
            per_parents[permute[b + power2[k - lvl[b]]]] = permute[a];
        }
        swap(per_parents[permute[a]], per_parents[permute[b]]);
        swap(permute[a], permute[b]);
        debug2(a, b);
        print(permute);
        print(per_parents);
        print(check);
        int nct = 0;
        for(auto chi : check) nct += (parents[chi] == per_parents[chi]);
        debug3(cnt, ct, nct);
        cnt += (nct - ct);
        cout << (cnt == n ? "YES" : "NO") << endl;
    }
}

int main()
{
    suprit;
    clock_t start = clock();

    int t = 1;
    cin >> t;
    power2[0] = 1;
    for (int i = 1; i < 26; i++)
        power2[i] = power2[i - 1] * 2;
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