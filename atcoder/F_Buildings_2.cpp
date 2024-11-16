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

int segtree[500001];
int n;
vi height;

void build() {
    for(int i = n; i < 2 * n; i++) {
        segtree[i] = i - n;
    }
    for(int i = n-1; i >= 0; i--) {
        auto fir = segtree[i << 1 | 1], sec = segtree[i << 1];
        auto &curr = segtree[i];
        if(height[fir] > height[sec]) curr = fir;
        else if(height[fir] < height[sec]) curr = sec;
        else curr = max(fir, sec);
    }
}

int query(int l, int r) {
    int ans = -1;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if(l & 1) {
            if(ans == -1) ans = segtree[l];
            else if(height[ans] < height[segtree[l]]) ans = segtree[l];
            else if(height[ans] == height[segtree[l]]) ans = max(ans, segtree[l]);
            l++;
        } 
        if(r & 1) {
            --r;
            if(ans == -1) ans = segtree[r];
            else if(height[ans] < height[segtree[r]]) ans = segtree[r];
            else if(height[ans] == height[segtree[r]]) ans = max(ans, segtree[r]);
        }
    }
    return ans;
}

void solve()
{
    int q;
    cin >> n >> q;
    height.resize(n);
    read(height);
    build();
    // print(height);
    vl ans(n, 0), ano(n, 0);
    stack<int> st;
    st.push(n-1);
    for(int i = n-2; i >= 0; i--) {
        while(st.size() && height[st.top()] < height[i]) st.pop(), ano[i]++;
        if(st.size() && height[st.top()] > height[i]) ans[i] = ans[st.top()] + 1;
        // if(st.size() && st.top() == i+1) ano[i]++;
        st.push(i);
    }
    // for(int i = 0; i < 2*n; i++) cout << segtree[i] << " ";
    // cout << endl;
    while(q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        int ind = query(l, r+1);
        debug3(l, r, ind);
        cout << (ans[ind] ? ans[ind] - 1 : 0) + ano[ind] << endl;
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