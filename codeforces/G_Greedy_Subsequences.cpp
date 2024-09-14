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

const int nmax = 1000007;
vvi tre;
int tin[nmax], tout[nmax];
int timer = 0;
void dfs(int u) {
    tin[u] = ++timer;
    for(int nei : tre[u]) {
        dfs(nei);
    }
    tout[u] = timer;
}

class SegmentTree {
private:
    vl ma;
    ll lazy[3*nmax+1];
    int n;

    void applylazy(int index, int start, int end) {
        if(!lazy[index]) return;
        ma[index] += lazy[index];
        int mid = (start + end) >> 1;
        if(start != end) {
            lazy[index + 1] += lazy[index];
            lazy[index + 2 * (mid - start + 1)] += lazy[index];
        }
        lazy[index] = 0;
    }

    void update(int index, int start, int end, int l, int r, int flag) {
        // debug4(start, end, l, r);
        if(start > end) return;
        applylazy(index, start, end);
        if(start > r || end < l) return;
        if(start >= l && end <= r) {
            lazy[index] += flag;
            applylazy(index, start, end);
            return;
        }
        int mid = (start + end) >> 1;
        update(index+1, start, mid, l, r, flag);
        update(index +  2 * (mid - start + 1), mid + 1, end, l, r, flag);
        ma[index] = max(ma[index + 1], ma[index + 2 * (mid - start + 1)]);
    }

public:
    SegmentTree() {
        n = timer + 1;
        ma.resize(2 * (timer + 1), 0);
    }

    int get_ans() {
        return ma[0];
    }

    void update(int u, int flag) {
        assert(tin[u] <= tout[u]);
        update(0, 0, n-1, tin[u], tout[u], flag);
        // for(int i = 0; i < 2*timer; i++) cout << ma[i] << " \n"[i==2*timer-1]; 
    }
};


void solve()
{
    int n, k;
    cin >> n >> k;
    vi arr(n);
    read(arr);
    tre.resize(n+1);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        while(st.size() && arr[st.top()] < arr[i]) {
            tre[i].push_back(st.top());
            st.pop();
        }
        st.push(i);
    }
    while(st.size()) tre[n].push_back(st.top()), st.pop();
    dfs(n);
    // for(int i = 0; i <= n; i++) debug3(i, tin[i], tout[i]);
    SegmentTree seg;
    // seg.update(0, 1);
    for(int i = 0; i < k-1; i++) {
        seg.update(i, 1);
    }

    for(int i = k-1; i < n; i++) {
        seg.update(i, 1);
        cout << seg.get_ans() << " \n"[i==n-1];
        seg.update(i-k+1, -1);
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