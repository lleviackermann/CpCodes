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

const int nmax = 2e5 + 5;

class segmentTree
{
private:
    vector<array<ll, 2>> segtree;
    vi lazy;
    int n;
    vl arr;

    void compress(vl& numbers) {
        sort(all(numbers));
        numbers.erase(unique(all(numbers)), numbers.end());
        arr = numbers;
        print(arr);
    }

    ll get_index(ll num) {
        int ans = lower_bound(all(arr), num) - arr.begin();
        return ans;
    }

    void changes(int index, int start, int end) {
        int mid = (start + end) >> 1;
        int &add = lazy[index];
        if(!add) return;
        if(add < 3) {
            segtree[index] = {add == 1 ? n + 10 : start, add == 1 ? start : n + 10};
            if(start != end) {
                int &left = lazy[index + 1], &right = lazy[index + 2 * (mid - start + 1)];
                left = add, right = add;
            }
        } else {
            swap(segtree[index][0], segtree[index][1]);
            if(start != end) {
                int &left = lazy[index + 1], &right = lazy[index + 2 * (mid - start + 1)];
                if(left == 3) left = 0;
                else if(left > 0) {
                    left = (left == 1 ? 2 : 1);
                } else left = 3;
                if(right == 3) right = 0;
                else if(right > 0) {
                    right = (right == 1 ? 2 : 1);
                } else right = 3;
            }
        }
        add = 0;
    }

    void applyChanges(int index, int start, int end, int type) {
        debug3(start, end, type);
        int &curr = lazy[index];
        if(curr == 0) curr = type;
        else if(type == 3) {
            if(curr < 3) curr = (curr == 1 ? 2 : 1);
            else curr = 0;
        }
        else {
            curr = type;
        } 
        changes(index, start, end);
    }

    void build(int index, int start, int end) {
        if(start == end) {
            segtree[index] = {start, n+10};
            return;
        };
        int mid = (start + end) >> 1;
        build(index + 1, start, mid);
        build(index + 2 * (mid - start + 1), mid + 1, end);
        segtree[index][0] = min(segtree[index + 1][0], segtree[index + 2 * (mid - start + 1)][0]);
        segtree[index][1] = min(segtree[index + 1][1], segtree[index + 2 * (mid - start + 1)][1]);

    }

    void update(int index, int left, int right, int start, int end, int type) {
        changes(index, start, end);
        if(left > end || right < start) return;
        if(start >= left && end <= right) {
            applyChanges(index, start, end, type);
            return;
        }
        int mid = (start + end) >> 1;
        update(index + 1, left, right, start, mid, type);
        update(index + 2 * (mid - start + 1), left, right, mid + 1, end, type);
        segtree[index][0] = min(segtree[index + 1][0], segtree[index + 2 * (mid - start + 1)][0]);
        segtree[index][1] = min(segtree[index + 1][1], segtree[index + 2 * (mid - start + 1)][1]);
    }

public:
    segmentTree(vl& number)
    {
        compress(number);
        n = arr.size();
        lazy.resize(2*n+1);
        for(ll i = 0; i <= 2*n; i++) lazy[i] = 0;
        segtree.resize(2*n+1);
        build(0, 0, n-1);
    }

    void update(ll l, ll r, int type) {
        int left = get_index(l), right = get_index(r+1) - 1;
        debug2(left, right);
        update(0, left, right, 0, n-1, type);
    }

    ll get_ans() {
        int ind = segtree[0][0];
        assert(ind >= 0 && ind < n);
        return arr[ind];
    }

};

void solve()
{
    int n;
    cin >> n;
    vector<array<ll, 3>> queries(n);
    vl numbers;
    for (auto &[flag, l, r] : queries)
    {
        cin >> flag >> l >> r;
        debug3(flag, l, r);
        numbers.push_back(l);
        numbers.push_back(r+1);
    }
    numbers.push_back(1);
    segmentTree seg(numbers);
    for(auto &[flag, l, r] : queries) {
        seg.update(l, r, flag); 
        cout << seg.get_ans() << endl;
    }
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