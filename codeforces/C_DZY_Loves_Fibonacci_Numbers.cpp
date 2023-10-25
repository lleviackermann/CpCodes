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

const ll mod = 1e9 + 9;

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

const int NMAX = 300000;
int fib[NMAX+3];
int fibsum[NMAX+3];
template <typename T>
class SegmentTree
{
public:
    T n;
    vector<T> tree;
    vector<pair<ll, ll>> lazyTree;


    SegmentTree(vector<T> &arr)
    {
        this->n = arr.size();
        tree.resize(4 * this->n + 1);
        lazyTree.resize(4 * this->n + 1, {0ll,0ll});
        build(arr);
    }

    void build(T index, T start, T end, vector<T> &arr)
    {
        if (start == end)
        {
            tree[index] = arr[start];
            return;
        }
        T mid = (start + end) / 2;
        build(2 * index + 1, start, mid, arr);
        build(2 * index + 2, mid + 1, end, arr);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
        tree[index] %= mod;
    }

    T lazyQuery(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            return 0;
        }
        forward(start, end, index);
        if (start == end)
        {
            return tree[index];
        }

        if (start >= l && end <= r)
        {
            return tree[index];
        }

        T mid = (start + end) / 2;
        T first = lazyQuery(2 * index + 1, start, mid, l, r);
        T second = lazyQuery(2 * index + 2, mid + 1, end, l, r);
        return (first + second)%mod;
    }

    void update(T index, T l, T r, T start, T end)
    {
        forward(start, end, index);
        if (end < l || start > r || start > end)
            return;
        if (start == end)
        {
            lazyTree[index].first = fib[start-l+1];
            forward(start, end, index);
            return;
        }
        if (start >= l && end <= r)
        {
            lazyTree[index].first = fib[start-l+1];
            lazyTree[index].second = fib[start-l+2];
            debug2(lazyTree[index].first, lazyTree[index].second);
            forward(start, end, index);
            return;
        }

        T mid = (start + end) / 2;
        update(2 * index + 1, l, r, start, mid);
        update(2 * index + 2, l, r, mid + 1, end);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
        tree[index] %= mod;
    }

    void forward(T start, T end, T index) {
        ll num = end - start + 1;
        ll fir = lazyTree[index].first, sec = lazyTree[index].second;
        tree[index] = tree[index] + (fir * (num == 1 ? 1 : (fibsum[num-2]+1)) % mod) + (sec * fibsum[num-1] % mod);
        debug3(tree[index], start, end);
        ll sumfir = (fir * (num == 1 ? 1 : (fibsum[num-2]+1)) % mod);
        ll sumsec =  + (sec * fibsum[num-1] % mod);
        debug4(fir, sec, sumfir, sumsec);
        tree[index] %= mod;
        if(start!=end) {
            T mid = (start + end) / 2;
            lazyTree[(index<<1)+1].first = (lazyTree[(index<<1)+1].first + fir) % mod;
            if(start!=mid) lazyTree[(index<<1)+1].second = (lazyTree[(index<<1)+1].second + sec) % mod;
            ll nex = mid+2-start;
            lazyTree[(index<<1)+2].first = (lazyTree[(index<<1)+2].first + (fir*fib[nex-2]%mod + sec*fib[nex-1]%mod)) % mod;
            nex++;
            if(mid+1!=end) lazyTree[(index<<1)+2].second = (lazyTree[(index<<1)+2].second + (fir*fib[nex-2]%mod + sec*fib[nex-1]%mod)) % mod;
        }
        lazyTree[index].first = 0, lazyTree[index].second = 0;
    }

    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }

    T lazyQuery(T l, T r)
    {
        return lazyQuery(0, 0, this->n - 1, --l, --r);
    }

    void update(T l, T r)
    {
        update(0, --l, --r, 0, this->n - 1);
    }
};

void solve()
{
    ll n,q;
    cin>>n>>q;
    vl arr(n);
    read(arr);
    SegmentTree<ll> segtree(arr);
    fib[1] = 1, fib[2] = 1;
    fib[0] = 0;
    fibsum[0] = 0, fibsum[1] = 1;
    for(int i = 3; i <= NMAX; i++) fib[i] = (fib[i-1] + fib[i-2]) % mod;
    for(int i = 2; i <= NMAX; i++) fibsum[i] = (fib[i] + fibsum[i-1]) % mod;
    for(int i = 1; i <= 10; i++) debug2(fib[i], fibsum[i]);
    while(q--) {
        ll sign, l, r;
        cin>>sign>>l>>r;
        if(sign == 1) {
            segtree.update(l,r);
        } else {
            cout<<segtree.lazyQuery(l,r)<<endl;
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
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    
    #ifndef ONLINE_JUDGE
    // cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}

// 3 4 3+4 3+4+4 3+4+4+3+4 
// 1,0    0,1   1,1    1,2,  