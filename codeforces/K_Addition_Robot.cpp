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

vector<array<ll, 2>> matrix_mult(vector<array<ll, 2>>& fir, vector<array<ll, 2>>& sec) {
    vector<array<ll, 2>> ans(2);
    ans[0][0] = (fir[0][0] * sec[0][0] + fir[0][1] * sec[1][0]) % mod;
    ans[0][1] = (fir[0][0] * sec[0][1] + fir[0][1] * sec[1][1]) % mod;
    ans[1][0] = (fir[1][0] * sec[0][0] + fir[1][1] * sec[1][0]) % mod;
    ans[1][1] = (fir[1][0] * sec[0][1] + fir[1][1] * sec[1][1]) % mod;
    return ans;
}

vector<array<ll, 2>> modify(char c) {
    vector<array<ll, 2>> ans(2);
    ans[0][0] = 1, ans[1][1] = 1, ans[0][1] = 1, ans[1][0] = 0;
    if(c == 'B') ans[1][0] = 1, ans[0][1] = 0;
    return ans;
}

vector<array<ll, 2>> identity_mat() {
    vector<array<ll, 2>> ans{{1, 0}, {0, 1}};
    return ans;
}

void print_arr(vector<array<ll, 2>>& temp) {
    for(auto [fir, sec] : temp) {
        cout << fir << " " << sec << endl;
    }
}

class segmentTree {
private:
    vector<vector<array<ll, 2>>> segtree;
    vector<int> lazy;
    int n;   

    void push(int index, int start, int end) {
        if(!lazy[index]) return;
        swap(segtree[index][0][0], segtree[index][1][1]);
        swap(segtree[index][1][0], segtree[index][0][1]);
        if(start != end) {
            int mid = (start + end) >> 1;
            lazy[index + 1] ^= 1;
            lazy[index + 2 * (mid - start + 1)] ^= 1;
        }
        lazy[index] = 0;
    }

    void update(int index, int start, int end, int left, int right) {
        push(index, start, end);
        if(left > end || right < start) return;
        if(start >= left && end <= right) {
            lazy[index] ^= 1;
            push(index, start, end);
            return;
        }
        int mid = (start + end) >> 1;
        update(index + 1, start, mid, left, right);
        update(index + 2 * (mid - start + 1), mid + 1, end, left, right);
        segtree[index] = matrix_mult(segtree[index + 1], segtree[index + 2 * (mid - start + 1)]);
    }

    vector<array<ll, 2>> query(int index, int start, int end, int left, int right) {
        push(index, start, end);
        if(left > end || right < start) return identity_mat();
        if(start >= left && end <= right) return segtree[index];
        vector<array<ll, 2>> fir, sec;
        int mid = (start + end) >> 1;
        fir = query(index + 1, start, mid, left, right);
        sec = query(index + 2 * (mid - start + 1), mid + 1, end, left, right);
        return matrix_mult(fir, sec);
    }

    void build(int index, int start, int end, string &s) {
        if(start == end) {
            assert(index < segtree.size());
            assert(start < s.size());
            segtree[index] = modify(s[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(index + 1, start, mid, s);
        build(index + 2 * (mid - start + 1), mid + 1, end, s);
        segtree[index] = matrix_mult(segtree[index + 1], segtree[index + 2 * (mid - start + 1)]);
    }

public:

    segmentTree(string s) {
        n = s.size();
        segtree.resize(2*n+1);
        lazy.resize(2*n+1, 0);
        debug2(segtree.size(), lazy.size());
        build(0, 0, n-1, s);
    }

    void update(int l, int r) {
        update(0, 0, n-1, l -1, r - 1);
    }

    array<ll, 2> query(ll l, ll r, ll a, ll b) {
        vector<array<ll, 2>> temp = query(0, 0, n-1, l - 1, r - 1);
        // print_arr(temp);
        ll fir = (temp[1][1] * a % mod) + (temp[0][1] * b % mod);
        ll sec = (temp[1][0] * a % mod) + (temp[0][0] * b % mod);
        return {fir % mod, sec % mod};
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    segmentTree seg(s);
    while(q--) {
        int flag, l, r;
        cin >> flag >> l >> r;
        if(flag == 1) {
            seg.update(l, r);
        } else {
            ll a, b;
            cin >> a >> b;
            array<ll, 2> ans = seg.query(l, r, a, b);
            cout << ans[0] << " " << ans[1] << endl;
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
    
    #ifndef ONLINE_JUDGE
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}