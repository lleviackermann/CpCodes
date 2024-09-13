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

const int nmax = 5e5+1;
int segtree[4*nmax];
int n;

void build(int index, int start, int end, vi& arr) {
    if(start == end) {
        segtree[index] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(index + 1, start, mid, arr);
    build(index + 2 * (mid - start + 1), mid + 1, end, arr);
    segtree[index] = __gcd(segtree[index+1], segtree[index + 2 * ((start + end) / 2 - start + 1)]);
} 

void update(int index, int start, int end, int target, int val) {
    if(start == end) {
        segtree[index] = val;
        return;
    }
    int mid = (start + end) / 2;
    if(target <= mid) update(index+1, start, mid, target, val);
    else update(index + 2 * (mid - start + 1), mid+1, end, target, val);
    segtree[index] = __gcd(segtree[index+1], segtree[index + 2 * (mid - start + 1)]);

}

ll x;
int tem_ans = 0;
void query(int index, int start, int end, int l, int r) {
    if(l > end || r < start || tem_ans > 1) return;
    if(start >= l && end <= r && segtree[index] % x == 0) return;
    if(start >= l && end <= r && segtree[index] % x && tem_ans) {
        tem_ans += 1;
        return;
    }
    if(start == end) {
        tem_ans += 1;
        return;
    }
    ll mid = (start + end) / 2;
    int left = index + 1, right = index + 2 * (mid - start + 1);
    if(segtree[left] % x) {
        query(left, start, mid, l, r);
    }
    debug3(index, start, end);
    debug3(start, mid, segtree[left]);
    debug3(mid+1, end, segtree[right]);
    // if(sum && (segtree[right] % x)) return 10;
    if(segtree[right] % x) {
        query(right, mid+1, end, l, r);
    }
    // debug3(start, end, sum);
    return;
}


void solve()
{
    cin >> n;
    vi arr(n);
    read(arr);
    build(0, 0, n-1, arr);

    int q;
    cin >> q;
    while(q--) {
        int flag, l, r;
        cin >> flag >> l >> r;
        if(flag == 1) {
            cin >> x;
            tem_ans = 0;
            query(0, 0, n-1, l-1, r-1);
            // debug3(l, r, ans);
            cout << (tem_ans > 1 ? "NO" : "YES") << endl;
        } else {
            update(0, 0, n-1, l-1, r);
        }
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