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

class customCompare {
public:
    bool operator()(array<ll, 2>& below, array<ll, 2>& above)
    {
        debug3(below[0], below[1], below[2]);
        debug3(above[0], above[1], above[2]);

        if (below[0] < above[0]) {
            return true;
        }
        
        return false;
    }
};

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    if (n <= 3) {
        return true;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= n; i += 6) {

        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

const int nmax = 1e5+10;
vector<vector<array<ll, 3>>> tre(nmax);
void solve()
{
    ll n, m, s, e;
    cin >> n >> m >> s >> e;
    for(int i = 0; i < m; i++) {
        int st, en, cap, co;
        cin >> st >> en >> cap >> co;
        tre[st].push_back({en, cap, co});
    }
    priority_queue<array<ll, 2>, vector<array<ll, 2>>, customCompare> store;
    auto find_prime = [&](ll x) {
        for(ll i = x; i >= 2; i--) {
            if(isPrime(i)) return i;
        }
        return 1ll;
    };
    store.push({(ll)1e9, s});
    vl ste(n+1, 0);
    ste[s] = 1e9;
    while(store.size()) {
        auto [ma, ind] = store.top();
        // debug3(ma,sum, ind);
        store.pop();
        if(ma != ste[ind]) continue;
        if(ind == e) {
            break;
        }
        for(auto [en, cap, co] : tre[ind]) {
            if(min(ma, cap) > ste[en]) {
                // debug4(ind, en, cap, co);
                ste[en] = min(ma, cap);
                // debug3(ma, cap, ste[en]);
                store.push({ste[en], en});
            }
        }
    }
    if(ste[e] == 0) {
        cout << "0 0\n";
        return;
    }
    ste[e] = find_prime(ste[e]);
    priority_queue<pair<ll, ll>, vpl, greater<pl>> sum_store;
    vl sum(n+1, 1e17);
    sum[s] = 0;
    sum_store.push({0ll, s});
    while(sum_store.size()) {
        auto [su, ind] = sum_store.top();
        sum_store.pop();
        if(su != sum[ind]) continue;
        if(ind == e) {
            cout << ste[e] << " " << ste[e] * su << endl;
            return;
        }
        for(auto [en, cap, cos] : tre[ind]) {
            if(cap < ste[e] || sum[ind] + cos >= sum[en]) continue;
            sum[en] = sum[ind] + cos;
            sum_store.push({sum[en], en});
        }
    }
    cout << "0 0\n";
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