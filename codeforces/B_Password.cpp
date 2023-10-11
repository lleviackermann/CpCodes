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

class DoubleHash {
public:
    string s;
    int n;
    vl prefixHash1, prefixHash2, basepower1, basepower2;
    ll p1, p2, modulo1, modulo2;
    // vl inverseValue1, inverseValue2;
    DoubleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash1.resize(n+1, 0);
        prefixHash2.resize(n+1, 0);
        basepower1.resize(n+1, 1);
        basepower2.resize(n+1, 1);
        // inverseValue1.resize(n+1, 0);
        // inverseValue2.resize(n+1, 0);
        p1 = 31, p2 = 43, modulo1 = 1e9+7, modulo2 = 1e9+9;
        computePrefixHash(p1, modulo1, prefixHash1, basepower1);
        computePrefixHash(p2, modulo2, prefixHash2, basepower2);
        // computeInverse(inverseValue1, p1, modulo1);
        // computeInverse(inverseValue2, p2, modulo2);
    }
 
    // void computeInverse(vl &inverse, ll p, ll modulo) {
    //     ll temp = binpow(p, n-1, modulo);
    //     inverse[n-1] = binpow(temp, modulo-2, modulo);
    //     for(ll i = n-2; i >=0; i--) inverse[i] = (inverse[i+1] * (p)) % modulo;
    // }

    void computePrefixHash(ll p, ll modulo, vl &prefix, vl &basepower) {
        for(int i = 1; i <= n; i++) basepower[i] = basepower[i-1] * p % modulo;
        for(ll i = 0; i < n; i++) {
            ll x = s[i] - 'a' + 1;
            prefix[i+1] = (prefix[i] + basepower[i] * x) % modulo;
        }
    }

    pl substrHash(ll l, ll r) {
        //indexing should be 0 based
        pl ans;
        ans.first = (prefixHash1[r+1] - prefixHash1[l] + modulo1) * basepower1[n-l] % modulo1;
        ans.second = (prefixHash2[r+1] - prefixHash2[l] + modulo2) * basepower2[n-l] % modulo2;
        // ans.first = (prefixHash1[r+1] - prefixHash1[l] + modulo1) * inverseValue1[l] % modulo1;
        // ans.second = (prefixHash2[r+1] - prefixHash2[l] + modulo2) * inverseValue2[l] % modulo2;
        return ans;
    }
};

class SingleHash {
public:
    string s;
    int n;
    vl prefixHash;
    ll p, modulo;
    vl basepower;
    // vl inverseValue;
 
    SingleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash.resize(n+1, 0);
        basepower.resize(n+1, 1);
        // inverseValue.resize(n+1,0);
        p = 31, modulo = 1e9+7;
        computePrefixHash();
        // computeInverse();
    }
    
    // void computeInverse() {
    //     ll temp = binpow(p, n-1, modulo);
    //     inverseValue[n-1] = binpow(temp, modulo-2, modulo);
    //     for(ll i = n-2; i >=0; i--) inverseValue[i] = (inverseValue[i+1] * (p)) % modulo;
    // }

    void computePrefixHash() {
        ll power_p = 1;
        for(int i = 1; i <= n; i++) basepower[i] = basepower[i-1] * p % modulo;
        // print(basepower);
        for(ll i = 0; i < n; i++) {
            ll x = s[i] - 'a' + 1;
            prefixHash[i+1] = (prefixHash[i] + basepower[i] * x) % modulo;
        }
    }

    ll substrHash(ll l, ll r) {
        ll ans = (prefixHash[r+1] - prefixHash[l] + modulo) * basepower[n-l] % modulo;
        // ll ans = (prefixHash[r+1] - prefixHash[l] + modulo) * inverseValue[l] % modulo;
        
        return ans;
    }
};

void solve()
{
    string s;
    cin>>s;
    SingleHash str(s);
    int n = s.length();
    // string ans = "";
    int ans = -1;
    vi indices;
    for(int i = 1; i < n; i++) {
        ll first = str.substrHash(0, i-1);
        ll second = str.substrHash(n-i, n-1);
        // debug2(s.substr(0,i),s.substr(n-i));
        // debug2(first, second);
        if(first == second) {
            indices.pb(i);
        }
    }
    int l = 0, r = indices.size() - 1;
    while(l <= r) {
        int mid = (l + r) / 2;
        int te = mid;
        mid = indices[mid];
        ll check = str.substrHash(0, mid-1);
        int flag = 0;
        for(int i = 1; i < n - mid; i++) {
            ll temp = str.substrHash(i, i+mid-1);
            if(temp == check) flag=1;
        }
        // mid = te;
        if(flag) ans = mid, l = te+1;
        else r = te - 1;
    }
    // debug(ans);
    if(ans==-1 || ans==0) cout<<"Just a legend\n";
    else cout<<s.substr(0, ans)<<endl;
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