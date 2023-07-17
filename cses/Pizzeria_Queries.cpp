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

template <typename T>
class SegmentTree
{
public:
    T n;
    vector<pair<ll,ll>> tree;

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
            tree[index] = {arr[start]+1, arr[end]+1};
            return;
        }
        T mid = (start + end) / 2;
        build(2 * index + 1, start, mid, arr);
        build(2 * index + 2, mid + 1, end, arr);
        tree[index] = {min(tree[2*index+1].first+end-mid, tree[2*index+2].first), min(tree[2*index+1].second, tree[2*index+2].second+mid-start+1)};
    }

    T leftQuery(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            return 2e9;
        }
        if (start >= l && end <= r)
        {
            // debug3(start, end, tree[index].first);
            return tree[index].first + r - end;
        }
        T mid = (start + end) / 2;
        T first = leftQuery(2 * index + 1, start, mid, l, r);
        T second = leftQuery(2 * index + 2, mid + 1, end, l, r);
        return min(first, second);
    }

    T rightQuery(T index, T start, T end, T l, T r)
    {
        if (start > r || end < l)
        {
            return 2e9;
        }
        if (start >= l && end <= r)
            return tree[index].second + start - l;

        T mid = (start + end) / 2;
        T first = rightQuery(2 * index + 1, start, mid, l, r);
        T second = rightQuery(2 * index + 2, mid + 1, end, l, r);
        return min(first, second);
    }

    void update(T index, T target, T value, T start, T end)
    {
        if (start == end)
        {
            tree[index] = {value+1, value+1};
            return;
        }

        T mid = (start + end) / 2;
        if (target <= mid)
        {
            update(2 * index + 1, target, value, start, mid);
        }
        else
        {
            update(2 * index + 2, target, value, mid + 1, end);
        }
        tree[index] = {min(tree[2*index+1].first+end-mid, tree[2*index+2].first), min(tree[2*index+1].second, tree[2*index+2].second+mid-start+1)};
    }

    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }


    T query(T ind)
    {
        T left = leftQuery(0, 0, this->n - 1, 0, ind-2);
        T right = rightQuery(0, 0, this->n - 1, ind, this->n -1);
        // debug2(left, right);
        return min(left , right);
    }

    void update(T target, T value)
    {
        update(0, --target, value, 0, this->n - 1);
    }

};

void solve()
{
    ll n, q;
    cin>>n>>q;
    vl arr(n);
    read(arr);
    debug(arr[56]);
    SegmentTree<ll> segtree(arr);
    while(q--) {
        int x;
        cin>>x;
        if(x == 1) {
            int index, value;
            cin>>index>>value;
            arr[index-1] = value;
            segtree.update(index, value);
        } else {
            int index;
            cin>>index;
            cout<<min(arr[index-1],segtree.query(index))<<endl;
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