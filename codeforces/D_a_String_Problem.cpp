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

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}



void solve()
{
    string s;
    cin >> s;
    ll n = s.size();
    ll p1 = 31, p2 = 6065621;
    vl power_1(n+1, 1), power_2(n+2, 1);
    const ll mod1 = 1e9 + 7, mod2 = 1e9 + 9;
    for(ll i = 1; i <= n; i++) power_1[i] = power_1[i-1] * p1 % mod1, power_2[i] = power_2[i-1] * p2 % mod2;
    vl prefix1(n), prefix2(n);
    for(int i = 0; i < n; i++) {
        ll ba1 = (i ? prefix1[i-1] : 0), ba2 = (i ? prefix2[i-1] : 0);
        ll val = s[i] - 'a';
        prefix1[i] = (ba1 + power_1[i] * val) % mod1;
        prefix2[i] = (ba2 + power_2[i] * val) % mod2; 
    }

    auto substr_hash = [&](int l, int r) -> pl {
        pl ans;
        ll ba1 = (l ? prefix1[l-1] : 0), ba2 = (l ? prefix2[l-1] : 0);
        ans.first = (prefix1[r] - ba1 + mod1) * power_1[n-l] % mod1;
        ans.second = (prefix2[r] - ba2 + mod2) * power_2[n-l] % mod2;
        return ans;
    };  

    vi indexes, counta;
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] != 'a') indexes.push_back(i), counta.push_back(cnt), cnt = 0;
        else cnt++;
    }
    if(indexes.size() == 0) {
        cout << n-1 << endl;
        return;
    }
    counta.push_back(cnt);
    int se = indexes.size();
    ll ans = 0;

    auto possible = [&](int num) -> ll {
        pl fir = substr_hash(indexes[0], indexes[num-1]);
        // debug2(fir.first, fir.second);
        vl temp_arr;
        temp_arr.push_back(counta[0]);
        for(int i = num; i < se; i += num) {
            if(fir != substr_hash(indexes[i], indexes[i+num-1])) return 0;
            temp_arr.push_back(counta[i]);
        }
        temp_arr.push_back(counta.back());
        ll temp_ans = 0;
        ll mi1 = 1e9, mi2 = 1e9, mi3 = 1e9;
        for(int i = 0; i < temp_arr.size(); i++) {
            if(i) mi2 = min(mi2, temp_arr[i]);
            if(i && i != temp_arr.size() - 1) mi3 = min(mi3, temp_arr[i]);
            if(i != temp_arr.size() - 1) mi1 = min(mi1, temp_arr[i]);
        }
        
        if(temp_arr.size() == 2) {
            temp_ans = (mi1 + 1) * (mi2 + 1);
        }
        else {
            for(int i = 0; i <= mi1; i++) {
                temp_ans += max(0ll, min(mi3 - i, mi2)) + 1;
            }
        }
        // debug2(num, temp_ans);
        return temp_ans;
    };
    for(int i = 1; i * i <= se; i++) {
        if(se % i) continue;
        // debug2(i, possible(i));
        ans += possible(i);
        
        if(i*i != se) ans += possible(se / i);

        // debug2(se/i, possible(se/i));
    }
    cout << ans << endl;
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