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
template <typename T> void print(vector<T> &arr) { for(auto &i : arr) cout<<i.gcd<<" "; line}
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
struct item {
    int gcd, ans, total, count;

    item() {}

    item(int n) {
        this->gcd = n;
        this->count = 1;
        this->total = 1;
        this->ans = 0;
    }

    static item merge(item &fa, item &sa) {
        item first = fa;
        item second = sa;
        item temp;
        if(first.gcd > second.gcd) swap(first, second);
        if(first.gcd == second.gcd) {
            temp.gcd = first.gcd;
            temp.count = first.count + second.count;
            temp.total = first.total+ second.total;
            temp.ans = temp.total - temp.count;
        } else if(__gcd(first.gcd, second.gcd) == first.gcd) {
            temp.gcd = first.gcd;
            temp.count = first.count;
            temp.total = first.total + second.total;
            temp.ans = temp.total - temp.count;
        } else {
            temp.gcd = __gcd(first.gcd, second.gcd);
            temp.count = 0;
            temp.total = first.total + second.total;
            temp.ans = temp.total;
        }
        return temp;
    }
};

template <typename T>
class SegmentTree
{
public:
    T n;
    vector<item> tree;

    SegmentTree(vector<T> &arr)
    {
        this->n = arr.size();
        tree.resize(4 * this->n + 1);
        build(arr);
    }

    void build(T index, T start, T end, vector<T> &arr)
    {
        if (start == end)
        {
            tree[index] = item(arr[start]);
            return;
        }
        T mid = (start + end) / 2;
        build(2 * index + 1, start, mid, arr);
        build(2 * index + 2, mid + 1, end, arr); 
        // print(index);
        // print(this->tree);
        tree[index] = item::merge(tree[2 * index + 1], tree[2*index + 2]);
        // print(this->tree[index].gcd);
    }

    item query(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            item temp;
            temp.ans = -1;
            return temp;
        }
        if (start >= l && end <= r)
            return tree[index];

        T mid = (start + end) / 2;
        item first = query(2 * index + 1, start, mid, l, r);
        item second = query(2 * index + 2, mid + 1, end, l, r);
        if(first.ans == -1 && second.ans != -1) return second;
        else if(first.ans!= -1 && second.ans == -1) return first; 
        return item::merge(first, second);
    }

    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }

    item query(T l, T r)
    {
        return query(0, 0, this->n - 1, --l, --r);
    }
};



void solve()
{
    int n;
    cin>>n;
    vi arr(n);
    read(arr);
    SegmentTree<int> segtree(arr);
    int q;
    cin>>q;
    print(segtree.tree);

    while(q--) {
        int l, r;
        cin>>l>>r;
        cout<<segtree.query(l,r).ans<<endl;
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