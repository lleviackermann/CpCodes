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

class Segtree {
private:
    int n;

    struct node {
        int ma, mi;
        bool is_sort;

        node() {}

        node(int val) {
            ma = val, mi = val, is_sort = 1;
        }

        node(int ma, int mi, bool isso) : ma(ma), mi(mi), is_sort(isso) {}
    };
    vector<node> segtree;

    node merge(node& fir, node& sec) {
        node ans;
        ans.ma = max(fir.ma, sec.ma);
        ans.mi = min(fir.mi, sec.mi);
        if(!fir.is_sort || !sec.is_sort) {
            ans.is_sort = 0;
            return ans;
        }
        if(fir.ma <= sec.mi) ans.is_sort = 1;
        else ans.is_sort = 0;
        return ans;
    }

    void build(int ind, int st, int en, vector<int>& arr) {
        if(st == en) {
            segtree[ind] = node(arr[st]);
            return;
        }
        int mid = (st + en) >> 1;
        build(ind << 1, st, mid, arr);
        build(ind << 1 | 1, mid + 1, en, arr);
        segtree[ind] = merge(segtree[ind << 1], segtree[ind << 1 | 1]);
    }

    node query(int ind, int st, int en, int l, int r) {
        if(st > r || en < l) return {INT32_MIN, INT32_MAX, true};
        if(st >= l && en <= r) return segtree[ind];
        int mid = (st + en) >> 1;
        node fir = query(ind << 1, st, mid, l, r);
        node sec = query(ind << 1 | 1, mid + 1, en, l, r);
        return merge(fir, sec);
    }

public:
    Segtree(vector<int> arr) {
        n = arr.size();
        segtree.resize(4*n);
        build(1, 0, n-1, arr);
    }


    bool is_sorted_part(int i, int j) {
        node fin = query(1, 0, n-1, i, j);
        return fin.is_sort;
    }

    int get_min(int i, int j) {
        node fin = query(1, 0, n-1, i, j);
        return fin.mi;
    }

    int get_max(int i, int j) {
        node fin = query(1, 0, n-1, i, j);
        return fin.ma;
    }

    tuple<int, int, bool> get_all(int i, int j) {
        node fin = query(1, 0, n-1, i, j);
        return {fin.mi, fin.ma, fin.is_sort};
    }

};

void solve()
{
    ll n;
    cin >> n;
    vi arr(n);   
    read(arr);
    if(is_sorted(all(arr))) {
        cout << 0 << endl;
        return;
    }
    ll ans = 1e18;
    ordered_set<int> se;
    Segtree seg(arr);
    auto binary = [&](int pre, int suf, int fl) {
        if(suf == 0 || pre == n-1) return true;
        if(pre + 1 == suf) {
            int left_ma = seg.get_max(0, pre);
            int rig_mi = seg.get_min(suf, n-1);
            return left_ma <= rig_mi;
        }
        if(pre + 1 < suf) {
            auto [mi, ma, is_sort] = seg.get_all(pre + 1, suf - 1);
            if(!is_sort) return false;
            int left_ma = seg.get_max(0, pre);
            int rig_mi = seg.get_min(suf, n-1);
            return (left_ma <= mi && ma <= rig_mi); 
        }
        if(fl == 0) {
            int rig_mi = seg.get_min(pre+1, n-1);
            int cnt = pre - suf + 1;
            int ele = *(se.find_by_order(pre - cnt));
            return ele <= rig_mi;
        }
        int lef_ma = seg.get_max(0, suf-1);
        int cnt = pre - suf + 1;
        if(cnt == se.size()) {
            return true;
        }
        int ele = *(se.find_by_order(cnt));
        return lef_ma <= ele;
    };

    for(ll prefix = 0; prefix < n-1; prefix++) {
        ll curr = (prefix + 1) * (prefix + 1);
        se.insert(arr[prefix]);
        int low = 0, high = n-1;
        ll temp = 1e18;
        while(low <= high) {
            int mid = (low + high) >> 1;
            if(binary(prefix, mid, 0)) {
                temp = (n - mid);
                low = mid + 1;
            } else high = mid - 1;
        }
        assert(temp <= n);
        curr += temp * temp;
        ans = min(ans, curr);
    }
    se.clear();
    for(int suffix = n-1; suffix > 0; suffix--) {
        ll cn = n - suffix;
        ll curr = cn * cn;
        se.insert(arr[suffix]);
        int low = 0, high = n-1;
        ll temp = 1e18;
        while(low <= high) {
            int mid = (low + high) >> 1;
            if(binary(mid, suffix, 1)) {
                temp = mid + 1;
                high = mid - 1;
            } else low = mid + 1;
        }
        assert(temp <= n);
        debug2(suffix, temp);
        curr += temp * temp;
        ans = min(ans, curr);
    }

    for(ll i = 1; i < n; i++) {
        // if(i * i > ans) break;
        auto [pmi, pma, pis] = seg.get_all(0, i-1);
        auto [smi, sma, sis] = seg.get_all(i, n-1);
        if(pis) {
            if(pma <= smi) ans = min(ans, (n - i) * (n - i));
        } else if(sis) {
            if(pma <= smi) ans = min(ans, i * i);
        }
    }
    ans = min(ans, n * n);
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