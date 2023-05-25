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
template <typename T> void print(vector<T> &arr) { for(auto &i : arr) cout<<i.index<<" "; line}
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
    int index, number, start;

    item() {}

    item(int n) {
        this->index = -1;
        this->number = -1;
        this->start = -1;
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
        tree[index] = item(0);
    }

    T query(T index, T start, T end, T ind)
    {
        // if(ind < start || ind > end) return -1;

        if(tree[index].index != -1) {
            debug3(start, end, ind);
            if(start!=end) {
                if(tree[2*index+1].number < tree[index].number) {
                    tree[2*index+1].index = tree[index].index;
                    tree[2*index+1].number = tree[index].number;
                    tree[2*index+1].start = tree[index].start;
                }
                if(tree[2*index+2].number < tree[index].number) {
                    tree[2*index+2].index = tree[index].index;
                    tree[2*index+2].number = tree[index].number;
                    tree[2*index+2].start = tree[index].start;
                }
            }
        }

        if(start == end) {
            if(tree[index].index==-1) return -1;
            return tree[index].index + ind - tree[index].start;
        }

        T mid = (start + end) / 2;

        if(ind <= mid) return query(2*index+1, start, mid, ind);
        else return query(2*index+2, mid+1, end, ind);


    }

    void update(T l, T r, T value, T index, T start, T end, T num) {
        if(l > end || r < start) return;

        if(start == end || start >= l && end <= r) {
            tree[index].index = value;
            tree[index].start = l;
            tree[index].number = num;
            return;
        }

        int mid = (start + end) / 2;
        if(l <= mid) update(l, r, value, 2*index+1, start, mid, num);
        if(r > mid) update(l, r, value, 2*index+2, mid+1, end, num);

    }
    void build(vector<T> &arr)
    {
        build(0, 0, arr.size() - 1, arr);
    }

    T query(T l)
    {
        return query(0, 0, this->n - 1, --l);
    }

    void update(T x, T y, T q, T num) {
        update(y-1, y - 2 + q, --x, 0, 0, this->n - 1, num);
    }
};


void solve()
{
    int n, m;
    cin>>n>>m;
    vi a(n), b(n);
    read(a);
    read(b);
    SegmentTree<int> segtree(b);
    int count = 0;
    while(m--) {
        count++;
        int x;
        cin>>x;
        if(x == 2) {
            int l;
            cin>>l;
            int temp = segtree.query(l);
            debug(temp);
            if(temp != -1) cout<<a[temp];
            else cout<<b[--l];
            cout<<endl;
        } else {
            int x, y, k;
            cin>>x>>y>>k;
            segtree.update(x, y, k, count);
            print(segtree.tree);
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