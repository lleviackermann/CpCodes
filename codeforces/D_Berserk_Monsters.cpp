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


void solve()
{
    int n;
    cin>>n;
    vi attack(n), damage(n);
    read(attack);
    read(damage);
    set<int> store;
    for(int i = 0; i < n; i++) store.insert(i);
    queue<int> prev;
    vector<int> died(n, 0);
    vector<int> ans(n, 0);
    for(int i = 0; i < n; i++) {
        int dam = (i != 0 ? attack[i-1] : 0) + (i != n-1 ? attack[i+1] : 0);
        if(dam > damage[i]) {
            prev.push(i);
            store.erase(i);
            died[i] = 1;
            ans[0]++;
        }
    }
    print(store);
    int count = 0;
    while(prev.size()) {
        int sz = prev.size();
        count++;
        queue<int> temp;
        for(int i = 0; i < sz; i++) {
            int to = prev.front();
            // debug(to);
            prev.pop();
            auto it = store.lower_bound(to);
            int las = -1, low = -1;
            if(it != store.end()) las = *it;
            if(it != store.begin()) {
                it--;
                low = *it;
            }
            // debug2(las, low);
            if(las != -1 && died[las] == 0) {
                int dama = (low == -1 ? 0 : attack[low]);
                it = store.upper_bound(las);
                if(it != store.end()) {
                    // debug3(to, dama, *it);
                    dama += attack[(*it)];
                }
                if(dama > damage[las]) {
                    ans[count]++;
                    debug(las);
                    died[las] = 1;
                    prev.push(las);
                    temp.push(las);
                }
            }
            if(low != -1 && died[low] == 0) {
                int dama = (las == -1 ? 0 : attack[las]);
                it = store.lower_bound(low);
                if(it != store.begin()) {
                    it--;
                    // debug3(to-1, dama, *it);
                    dama += attack[*it];
                }
                if(dama > damage[low]) {
                    died[low] = 1;
                    ans[count]++;
                    debug(low);
                    prev.push(low);
                    temp.push(low);
                }
            }
        }
        sz = temp.size();
        for(int i = 0; i < sz; i++) {
            int to = temp.front();
            temp.pop();
            // cout<<to<<" ";
            store.erase(to);
        }
        // line
        print(store);
    }
    for(auto i : ans) cout<<i<<" ";
    line
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