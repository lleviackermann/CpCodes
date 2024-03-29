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

// const ll mod = 1e9 + 7;

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
    vl prefixHash1, prefixHash2, inverseValue1, inverseValue2;
    ll p1, p2, modulo1, modulo2;

    DoubleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash1.resize(n+1, 0);
        prefixHash2.resize(n+1, 0);
        inverseValue1.resize(n+1, 0);
        inverseValue2.resize(n+1, 0);
        p1 = 31, p2 = 43, modulo1 = 1e9+7, modulo2 = 1e9+9;
        computePrefixHash(p1, modulo1, prefixHash1);
        computePrefixHash(p2, modulo2, prefixHash2);
        computeInverse(inverseValue1, p1, modulo1);
        computeInverse(inverseValue2, p2, modulo2);

    }

    void computeInverse(vl &inverse, ll p, ll modulo) {
        ll temp = binpow(p, n-1, modulo);
        inverse[n-1] = binpow(temp, modulo-2, modulo);
        for(ll i = n-2; i >=0; i--) inverse[i] = (inverse[i+1] * (p)) % modulo;
    }

    void computePrefixHash(ll p, ll modulo, vl &prefix) {
        ll power_p = 1;
        for(ll i = 0; i < n; i++) {
            ll x = s[i] - 'a' + 1;
            prefix[i+1] = (prefix[i] + power_p * x) % modulo;
            prefix[i+1] = (prefix[i+1] + modulo) % modulo; 
            power_p = (power_p * p) % modulo;

        }
    }

    ll partialHash(ll l, ll r, ll modulo, ll p, vl &prefix, vl &inverse) {
        ll temp = (((prefix[r] - prefix[l-1]) % modulo) + modulo) % modulo;
        temp = (temp * inverse[l-1]) % modulo;
        return temp;
    }

    pair<ll, ll> substrHash(ll l, ll r) {
        pl ans;
        ans.first = partialHash(l, r, modulo1, p1, prefixHash1, inverseValue1);
        ans.second = partialHash(l, r, modulo2, p2, prefixHash2, inverseValue2);
        return ans;
    }

    static ll getHash(string &t, ll p, ll modulo) {
        int len = t.length();
        ll ans = 0;
        ll power_p = 1;
        for(ll i = 0; i < len; i++) {
            ll x = t[i] - 'a' + 1;
            ans += x * power_p;
            power_p = (power_p * p) % modulo;
            ans %= modulo;
        }
        return ans;
    }

    static pair<ll, ll> getHashString(string t) {
        pl ans;
        ans.first = getHash(t, 31, 1e9+7);
        ans.second = getHash(t, 43, 1e9+9);
        return ans;

    }
};

void solve()
{
    string pattern, word;
    cin>>pattern>>word;
    DoubleHash str(word);
    pl patternHash1 = DoubleHash::getHashString(pattern);

    int n = pattern.length();
    int len = word.length();
    for(int i = 0; i <= len-n; i++) {
        pl temp = str.substrHash(i+1, i+n);
        // print(temp);
        if(temp == patternHash1) cout<<i<<endl;
    }
    cout<<endl;
}

int main()
{ 
    suprit;
    clock_t start = clock();

    int t = 3;
    while (cin>>t)
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