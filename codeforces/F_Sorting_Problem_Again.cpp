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

const int nmax = 5e5 + 2;
int mis[2*nmax], mas[2*nmax];

void build(int ind, int st, int en, vi& arr) {
    if(st == en) {
        mis[ind] = mas[ind] = arr[st];
        return;
    }
    int mid = (st + en) / 2;
    build(ind+1, st, mid, arr);
    build(ind + 2 * (mid - st + 1), mid + 1, en, arr);
    mis[ind] = min(mis[ind+1], mis[ind + 2 * (mid - st + 1)]);
    mas[ind] = max(mas[ind+1], mas[ind + 2 * (mid - st + 1)]);
}

pi query(int ind, int st, int en, int l, int r) {
    if(en < l || st > r) return {1e9+5, -1e9-5};
    if(l <= st && en <= r) return {mis[ind], mas[ind]};

    int mid = (st + en) / 2;
    pi fir = query(ind+1, st, mid, l, r);
    pi sec = query(ind + 2 * (mid - st + 1), mid + 1, en, l, r);
    return {min(fir.first, sec.first), max(fir.second, sec.second)};
}

void update(int ind, int st, int en, int target, int val) {
    if(en < target || st > target) return;
    if(st == en) {
        mis[ind] = mas[ind] = val;
        return;
    }
    int mid = (st + en) / 2;
    if(mid >= target) update(ind+1, st, mid, target, val);
    else update(ind + 2 * (mid - st + 1), mid + 1, en, target, val);
    mis[ind] = min(mis[ind+1], mis[ind + 2 * (mid - st + 1)]);
    mas[ind] = max(mas[ind+1], mas[ind + 2 * (mid - st + 1)]);
}

void solve()
{
    int n;
    cin >> n;
    vi arr(n+1, 0);
    for(int i = 1; i <= n; i++) cin >> arr[i];
    build(0, 0, n, arr);
    set<int> store;
    for(int i = 2; i <= n; i++) if(arr[i] < arr[i-1]) store.insert(i);

    // auto find_pos = [&](int l, int r, int val) -> int {
    //     int ans = 
    // };
    print(store);

    auto get_ans = [&]() {
        if(store.empty()) {
            cout << -1 << " " << -1 << endl;
            return;
        }
        int low = *store.begin(), high = *store.rbegin();
        debug2(low, high);
        if(low == 2 && high == n) {
            cout << "1 " << n << endl;
            return;
        }
        low = (low == 1 ? low : low - 1);
        auto [mi, ma] = query(0, 0, n, low, high);
        debug2(mi, ma);
        print(arr);
        int l = 1, r = low - 1, fir = low;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(arr[mid] <= mi) l = mid + 1;
            else r = mid - 1, fir = mid;
        }
        l = high + 1, r = n;
        int sec = high;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(arr[mid] < ma) sec = mid, l = mid + 1;
            else r = mid - 1;
        }
        cout << fir << " " << sec << endl;
    };
    get_ans();
    int q;
    cin >> q;
    while(q--) {
        int pos, val;
        cin >> pos >> val;
        debug2(pos, val);
        int bef = arr[pos];
        arr[pos] = val;
        update(0, 0, n, pos, val);
        if(pos != 1 && arr[pos-1] > bef && arr[pos-1] <= val) store.erase(pos);
        if(pos != n && bef > arr[pos+1] && val <= arr[pos+1]) store.erase(pos+1);
        if(pos != 1 && arr[pos-1] > val) store.insert(pos);
        if(pos != n && arr[pos] > arr[pos+1]) store.insert(pos+1);
        print(store);
        get_ans();
    }
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 1;
    cin >> t;
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