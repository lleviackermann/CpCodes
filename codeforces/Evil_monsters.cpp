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

// const int nmax = 2e5; 
// ll segtree[4*nmax+10];

// void build(int ind, int st, int en, vl& cnt) {
//     if(st == en) {
//         segtree[ind] = cnt[st];
//         return;
//     }
//     int mid = (st + en) / 2;
//     build(2*ind+1, st, mid, cnt);
//     build(2*ind+2, mid+1, en, cnt);
//     segtree[ind] = segtree[2*ind+1] + segtree[2*ind+2];
// }

// ll query(int ind, int st, int en, int l, int r) {
//     if(en < l || st > r) return 0;
//     if(st >= l && en <= r) return segtree[ind];
//     int mid = (st + en) / 2;
//     ll first = query(2*ind+1, st, mid, l, r);
//     ll sec = query(2*ind+2, mid+1, en, l, r);
//     return first + sec;
// }


// void update(int ind, int st, int en, int toup, int val) {
//     if(en < toup || st > toup) return;
//     if(st == en) {
//         assert(toup == st);
//         segtree[ind] += val;
//         return;
//     }
//     int mid = (st + en) / 2;
//     update(2*ind+1, st, mid, toup, val);
//     update(2*ind+2, mid+1, en, toup, val);
//     segtree[ind] = segtree[2*ind+1] + segtree[2*ind+2];
// }

class segtree {
    vector<ll> tree, coordinates;
public:
    segtree(vector<ll>& val)
        : coordinates(val)
    {}

    void compress() {
        sort(coordinates.begin(), coordinates.end());
        coordinates.erase(unique(coordinates.begin(), coordinates.end()), coordinates.end());
        tree.resize(2 * coordinates.size(), 0);
    }

    void update(int value, int incr) {
        int indx = lower_bound(coordinates.begin(), coordinates.end(), value) - coordinates.begin();
        indx += tree.size() / 2;
        tree[indx] += incr;
        while (indx > 1) {
            indx >>= 1;
            tree[indx] = tree[2 * indx] + tree[2 * indx + 1];
        }
    }

    ll query(int value_l, int value_r) {
        int l = lower_bound(coordinates.begin(), coordinates.end(), value_l) - coordinates.begin();
        int r = lower_bound(coordinates.begin(), coordinates.end(), value_r) - coordinates.begin();
        l += tree.size() / 2, r += tree.size() / 2;
        ll ans = 0;
        while (r > l) {
            if (l & 1) ans += tree[l++];
            if (r & 1) ans += tree[--r];
            l >>= 1, r >>= 1;
        }
        return ans;
    }
};


void solve()
{
    ll n, q;
    cin >> n >> q;
    const int N = 1e5+1;
    vl heros[N], ans(q, 0), strengths;
    ll total = 0;
    vector<vector<pl>> events(N);
    for(int i = 0; i < n; i++) {
        ll st, en, stre;
        cin >> st >> en >> stre;
        total += (en - st + 1);
        events[st].emplace_back(1, stre);
        if(en + 1 < N) events[en+1].emplace_back(-1, stre);
        strengths.push_back(stre);
    }
    vl arr;
    for(int i = 0; i < q; i++) {
        ll pos, stre;
        cin >> pos >> stre;
        arr.push_back(stre);
        strengths.push_back(stre);
        heros[pos].push_back(i);
    }

    segtree tre(strengths);
    tre.compress();
    for(int i = 1; i < N; i++) {
        for(auto& [value, stre] : events[i]) {
            tre.update(stre, value);
        }   
        int ma_stre = 0;
        for(auto num : heros[i]) {
            debug3(i, num, ma_stre);
            int temp = arr[num];
            if(temp > ma_stre) {
                ans[num] = tre.query(ma_stre+1, temp);
                ma_stre = temp;
            }
            debug(ans[num]);
        }
    }
    for(int i = 0; i < q; i++) {
        ans[i] += (i ? ans[i-1] : 0);
        cout << total - ans[i] << " ";
    }
    line
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