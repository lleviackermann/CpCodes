#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T> 
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

const int N = 1e6+3;  
ll n_;  
int t[2 * N];

void build() {  
  for (int i = n_ - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  
  for (t[p += n_] += value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  
  int res = 0;
  for (l += n_, r += n_; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}

void solve()
{
    ll n;
    cin >> n;
    vi arr(n);   
    read(arr);
    vi ano = arr;
    sort(all(ano));
    unordered_map<int, int> store_indices;
    int tem_nex = 0;
    for(int i = 0; i < n; i++) {
        if(i && ano[i] != ano[i-1]) ++tem_nex;
        if(i && ano[i] != ano[i-1]) store_indices[ano[i]] = tem_nex;
        if(i == 0) store_indices[ano[i]] = tem_nex;
    }

    if(is_sorted(all(arr))) {
        cout << 0 << endl;
        return;
    }
    ll ans = n * n;
    vi pre_mi(n), pre_ma(n), suf_mi(n), suf_ma(n);
    for(int i = 0; i < n; i++) {
        if(i) pre_mi[i] = min(pre_mi[i-1], arr[i]), pre_ma[i] = max(pre_ma[i-1], arr[i]);
        else pre_mi[i] = pre_ma[i] = arr[i];
    }
    for(int i = n-1; i >= 0; i--) {
        if(i != n-1) suf_mi[i] = min(suf_mi[i+1], arr[i]), suf_ma[i] = max(suf_ma[i+1], arr[i]);
        else suf_mi[i] = suf_ma[i] = arr[i];
    }
    vi sum(n);
    sum[0] = 1;
    for(int i = 1; i < n; i++) sum[i] = sum[i-1] + (arr[i] >= arr[i-1]);
    
    n_ = tem_nex+1;
    for(int i = 0; i < 2*n_; i++) t[i] = 0;

    auto no_inter = [&](int pre, int suf) {
        if(suf == pre + 1) return true;
        int mid = sum[suf-1] - sum[pre];
        int mi = suf_mi[suf];
        // debug2(mid, mi);
        return (mid == suf - pre - 1 && mi >= pre_ma[suf-1] && pre_ma[pre] <= suf_mi[pre+1]);
    };

    // debug(no_inter(1, 5));

    for(int i = 0; i < n-1; i++) {
        modify(store_indices[arr[i]], 1);
        ll curr = 1ll * (i + 1) * (i + 1);
        if(suf_mi[i+1] >= pre_ma[i] && sum[n-1] - sum[i] == n-1-i) {
            // debug(i);
            ans = min(ans, curr);
            continue;
        }
        if(suf_mi[i+1] >= pre_ma[i]) {
            int low = i + 1, high = n-1;
            int tem = n*10;
            while(low <= high) {
                int mid = (low + high) / 2;
                if(no_inter(i, mid)) tem = mid, low = mid + 1;
                else high = mid - 1;
            }
            debug2(i, tem);
            // assert(tem < n);
            curr += 1ll * (n - tem) * (n - tem);
        } else {
            int lesser = query(0, store_indices[suf_mi[i+1]]+1);
            lesser = (i + 1) - lesser;
            lesser += (n - 1 - i);
            curr += 1ll * lesser * lesser;
        }
        debug2(i, curr);
        ans = min(ans, curr);
    }
    for(int i = 0; i < 2*n_; i++) t[i] = 0;

    for(int i = n-1; i > 0; i--) {
        modify(store_indices[arr[i]], 1);
        ll curr = 1ll * (n - i) * (n - i);
        if(pre_ma[i-1] <= suf_mi[i] && sum[i-1] == i) {
            // debug(i);
            ans = min(ans, curr);
            continue;
        }
        if(pre_ma[i-1] <= suf_mi[i]) {
            int low = 0, high = i - 1;
            int tem = n * 10;
            while(low <= high) {
                int mid = (low + high) >> 1;
                if(no_inter(mid, i)) tem = mid, high = mid - 1;
                else low = mid + 1;
            }
            debug2(tem, i);
            // assert(tem < i);
            curr += 1ll * (tem + 1) * (tem + 1);
        } else {
            int lesser = query(0, store_indices[pre_ma[i-1]]);
            lesser += i;
            curr += 1ll * lesser * lesser;
        }
        debug2(i, curr);
        ans = min(ans, curr);
    }
    
    cout << ans << endl;
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