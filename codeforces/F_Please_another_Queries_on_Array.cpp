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

const int PRIME_SIZE = 62;

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

vector<int> primes, revprimes;


struct item {
    ll bitmask, prod;

    item() {
        prod = 1;
        bitmask = 0;
    }

    item(ll num) {
        prod = num;
        bitmask = 0;
        for(int i = 0; i < PRIME_SIZE; i++) {
            if(num%primes[i]) continue;
            // debug2(num, primes[i]);
            bitmask = bitmask | (1ll<<i);
        }
    }

    static item merge(item fir, item sec) {
        // cout<<"fir sec "<<endl;
        item ans;
        ans.prod = fir.prod * sec.prod % mod;
        ans.bitmask = fir.bitmask | sec.bitmask;
        return ans;
    }

    static item clear() {
        item ans;
        ans.bitmask = 0;
        ans.prod = 1;
        return ans;
    }

};

template <typename T, typename V>
class SegmentTree
{
public:
    T n;
    vector<V> tree;
    vector<V> lazyTree;

    SegmentTree(vector<T> &arr)
    {
        this->n = arr.size();
        tree.resize(2 * this->n + 1);
        lazyTree.resize(2 * this->n + 1);
        for(int i = 0; i < 2*this->n+1; i++) {
            lazyTree[i] = V();
        }
        build(arr);
    }

    void build(T index, T start, T end, vector<T> &arr)
    {
        // debug2(start, end);
        if (start == end)
        {
            tree[index] = V(arr[start]);
            return;
        }
        T mid = (start + end) / 2;
        build(index + 1, start, mid, arr);
        build(index+2*(mid-start+1), mid + 1, end, arr);
        tree[index] = V::merge(tree[index + 1], tree[index+2*(mid-start+1)]);
    }

    V lazyQuery(T index, T start, T end, T l, T r)
    {
        forward(start, end, index);
        if (start > r || end < l)
        {
            return V::clear();
        }
        
        if (start >= l && end <= r)
        {
            return tree[index];
        }

        T mid = (start + end) / 2;
        V first = lazyQuery(index + 1, start, mid, l, r);
        V second = lazyQuery(index+2*(mid-start+1), mid + 1, end, l, r);
        return V::merge(first, second);
    }

    void update(T index, T l, T r, T value, T start, T end)
    {
        forward(start, end, index);
        if (end < l || start > r || start > end)
            return;
        if (start >= l && end <= r)
        {
            lazyTree[index] = V(value);
            forward(start, end, index);
            return;
        }

        T mid = (start + end) / 2;
        update(index + 1, l, r, value, start, mid);
        update(index+2*(mid-start+1), l, r, value, mid + 1, end);
        tree[index] = V::merge(tree[index + 1], tree[index+2*(mid-start+1)]);

    }

    void forward(T start, T end, T index) {
        T mid = (start + end) / 2;
        tree[index].prod = tree[index].prod * binpow(lazyTree[index].prod, (end-start+1), mod) % mod;
        tree[index].bitmask = tree[index].bitmask | lazyTree[index].bitmask;
        if(start!=end) {
            lazyTree[index+1] = V::merge(lazyTree[index+1], lazyTree[index]);
            lazyTree[index+2*(mid-start+1)] = V::merge(lazyTree[index+2*(mid-start+1)], lazyTree[index]);
        }
        lazyTree[index] = V::clear();
    }

    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }

    T lazyQuery(T l, T r)
    {
        V temp = lazyQuery(0, 0, this->n - 1, --l, --r);
        debug2(temp.bitmask, temp.prod);
        ll num = temp.prod, deno = 1;
        for(ll i = 0; i < PRIME_SIZE; i++) {
            if(temp.bitmask & (1ll<<i)) {
                num = num * (primes[i] - 1) % mod;
                num = num * revprimes[i] % mod;
            }
        }
        
        return num;
    }

    void update(T l, T r, T value)
    {
        update(0, --l, --r, value, 0, this->n - 1);
    }
};

// int tree[]


int isPrime(int n)
{
    if (n <= 1)
        return 0;
    if (n == 2 || n == 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
 
    return 1;
}

void solve()
{
    ll n, q;
    cin>>n>>q;
    vl arr(n);
    read(arr);
    for(int i = 2; i <= 300; i++) {
        if(isPrime(i)) {
            primes.push_back(i);
            revprimes.push_back(binpow(i, mod-2, mod));
        }
    }
    SegmentTree<ll,item> segtree(arr);
    while(q--) {
        string s;
        cin>>s;
        ll l,r;
        cin>>l>>r;
        if(s == "TOTIENT") {
            ll num = segtree.lazyQuery(l, r);
            cout<<num<<endl;
        } else {
            ll val;
            cin>>val;
            segtree.update(l,r,val);
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
    cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}

// 300 ^ (10^5)
// 2 2 3 5 5

// (2,62), (3, 9), (5, 6)

