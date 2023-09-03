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

const ll mod = 998244353;

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

struct node {
    node* child[2];
    int count;
    node() {
        count = 0;
        for(auto &a : child) a = nullptr;
    }
};

class Trie {
public:
    node* root = new node();
    
    
    void insert(ll num) {
        node* tra = root;
        root->count = root->count + 1;
        for(int i = 29; i >= 0; i--) {
            int x = num & (1 << i);
            if(x) x = 1;
            // cout<<x<<" ";
            if(!tra->child[x]) tra->child[x] = new node();
            tra = tra->child[x];
            tra->count++;
        }
    }

    ll numer() {
        ll ans = 0;
        queue<pair<node*, ll>> arr;
        node* temp = root;
        arr.push({temp, 1});
        while(!arr.empty()) {
            node * ano = arr.front().first;
            ll cou = arr.front().second;
            arr.pop();
            if(ano->child[0] != nullptr && ano->child[1] != nullptr) {
                ll fir = ano->child[0]->count;
                ll sec = ano->child[1]->count;
                // cout<<fir<<" "<<sec<<" cou " << cou<< endl;
                fir = fir * sec;
                // if(cou % 2) {
                    ans = ans + fir * (cou + cou + 1);
                // } else {
                    // ans = ans + fir * (cou + cou + 1);
                // }
            }
            if(ano->child[0]!=nullptr) arr.push({ano->child[0], cou});
            if(ano->child[1]!=nullptr) arr.push({ano->child[1], cou+1});
        }
        return ans;
    }
    
    
};


void solve()
{
    ll n;
    cin>>n;
    vl arr(n);
    read(arr);
    ll deno = n * n;
    Trie trie;
    map<ll, ll> m;
    for(auto &i : arr) trie.insert(i), m[i]++;
    // cout<<trie.root->count<<endl;
    ll ans = trie.numer();
    debug(ans);
    for(auto i : arr) {
        ll sec = m[i];
        if(sec==0) continue;
        // cout<<i<<" ";
        int cou = 1;
        for(int j = 0; j < 30; j++) {
            if(i & (1 << j)) cou++;
        }
        ans = ans + sec * sec * cou;
        m[i] = 0;
    }
    deno = binpow(deno, mod-2, mod);
    ans = ans % mod;
    // ans = 21;
    debug(ans);
    ans = ans * deno % mod;
    cout<<ans<<endl;
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
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    
    #ifndef ONLINE_JUDGE
    cout << setprecision(10) << elapsed << endl;
    #endif
    return 0;
}