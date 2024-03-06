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

// 2-D segment tree

template <typename T>
class SegmentTree2D
{
public:
    T n;
    vector<vector<T>> tree;

    SegmentTree2D(vector<vector<T>> &arr)
    {
        this->n = arr.size();
        tree.resize(4 * this->n + 1, vector<T>(4*this->n+1, 0));
        build(arr);
    }

    void build(T index, T start, T end, T row, T rowindex, vector<vector<T>> &arr)
    {
        if (start == end)
        {
            tree[rowindex][index] = arr[row][start];
            return; 
        }
        T mid = (start + end) / 2;
        build(2 * index + 1, start, mid, row, rowindex, arr);
        build(2 * index + 2, mid + 1, end, row, rowindex, arr);
        tree[rowindex][index] = tree[rowindex][2 * index + 1] + tree[rowindex][2 * index + 2];
    }

    void build(T index, T start, T end, vector<vector<T>> &arr) {
        if (start == end)
        {
            build(0, 0, this->n-1, start, index, arr);
            // tree[rowindex][index] = arr[row][start];
            return; 
        }
        T mid = (start + end) / 2;
        build(2 * index + 1, start, mid, arr);
        build(2 * index + 2, mid + 1, end, arr);
        for(int i = 0; i < 4*n+1; i++) tree[index][i] = tree[2*index+1][i] + tree[2*index+2][i];
    }
    
    T query(T index, T start, T end, T l, T r, T row) {
        if(start > r || end < l) return 0;

        if(start >= l && end <= r) {
            return tree[row][index];
        }

        T mid = (start + end) / 2;
        T first = query(2*index+1, start,mid, l, r, row);
        T second = query(2*index+2, mid+1, end, l, r, row);
        return first + second;
    }

    T query(T index, T start, T end, T r1, T r2, T c1, T c2)
    {
        if (start > r2 || end < r1)
        {
            return 0;
        }
        if (start >= r1 && end <= r2)
        {
            return query(0, 0, this->n-1, c1, c2, index);
        }

        T mid = (start + end) / 2;
        T first = query(2 * index + 1, start, mid, r1, r2, c1, c2);
        T second = query(2 * index + 2, mid + 1, end, r1, r2, c1, c2);
        return first + second;
    }

    void updatecol(T index, T target, T start, T end, T row) {
        if(start == end) {
            tree[row][index] ^= 1;
            return;
        }
        T mid = (start + end) / 2;
        if(target <= mid) {
            updatecol(2*index+1, target, start, mid, row);
        } else {
            updatecol(2*index+2, target, mid+1, end, row);
        }
        tree[row][index] = tree[row][2*index+1] + tree[row][2*index+2];
    }

    void update(T index, T row, T col, T start, T end)
    {
        if (start == end)
        {
            updatecol(0, col, 0, this->n-1, index);
            return;
        }

        T mid = (start + end) / 2;
        if (row <= mid)
        {
            update(2 * index + 1, row, col, start, mid);
        }
        else
        {
            update(2 * index + 2, row, col, mid + 1, end);
        }
        int st = 0, en = this->n-1;
        int ind = 0;
        while(true) {
            int m = (st + en) / 2;
            tree[index][ind] = tree[2*index+1][ind] + tree[2*index+2][ind];
            if(st==en) break;
            if(col <= m) {
                en = m;
                ind = 2*ind+1;
            } else {
                st = m+1;
                ind = 2*ind+2;
            }
            
        }
        // for(int i = 0; i < 4*n+1; i++) tree[index][i] = tree[2*index+1][i] + tree[2*index+2][i];
    }

    void build(vector<vector<T>> &arr)
    {
        build(0, 0, this->n-1, arr);
    }

    T query(T r1, T r2, T c1, T c2)
    {
        return query(0, 0, this->n-1, --r1, --r2, --c1, --c2);
    }

    void update(T row, T col)
    {
        update(0, --row, --col, 0, this->n-1);
    }

};

void solve()
{
    ll n, q;
    cin>>n>>q;
    vvl arr(n, vl(n));
    for(int i = 0; i < n; i++) {
        string s;
        cin>>s;
        // debug(s);
        for(int j = 0; j < n; j++) arr[i][j] = (s[j] == '.' ? 0 : 1);
    }
    SegmentTree2D<ll> segtree(arr);
    while(q--) {
        ll sign;
        cin>>sign;
        if(sign==1) {
            ll l,r;
            cin>>l>>r;
            segtree.update(l, r);
        } else {
            ll r1, r2, c1, c2;
            cin>>r1>>c1>>r2>>c2;
            cout<<segtree.query(r1,r2,c1,c2)<<endl;
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

// 0 0 0 1 0 1
// 1 0 1 0 0 1 
// 0 1 0 1 1 1 
// 0 0 0 0 1 1 
// 0 1 1 1 0 0 
// 1 1 1 1 1 1