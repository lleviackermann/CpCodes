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

int func(set<int>& se, int curr) {
    auto it = se.lower_bound(curr);
    if(it == se.end()) return -1;
    return *it;
};
void solve()
{
    int n;
    cin >> n;
    vi fir(n+1), sec(n+1), thi(n+1);
    auto get_input = [&](vi &arr) {
        for(int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
    };
    vi ind1(n+1), ind2(n+1), ind3(n+1);
    auto appoint = [&](vi& arr, vi& ind) {
        for(int i = 1; i <= n; i++) ind[arr[i]] = i; 
    };
    get_input(fir);
    appoint(fir, ind1);
    get_input(sec);
    appoint(sec, ind2);
    get_input(thi);
    appoint(thi, ind3);
    vector<pair<char, int>> ans;
    vector<int> dp(n+1, -1), dir(n+1, -1);
    set<int> str1, str2, str3;
    str1.insert(fir[1]);
    str2.insert(sec[1]);
    str3.insert(thi[1]);
    dp[1] = 0;
    for(int i = 2; i <= n; i++) {
        if(dp[i-1] != -1) {
            str1.insert(fir[i-1]);
            str2.insert(sec[i-1]);
            str3.insert(thi[i-1]);
        }
        int ind = func(str1, fir[i]);

        if(ind != -1 && dp[ind1[ind]] != -1) {
            dp[i] = ind1[ind];
            dir[i] = 0;
            continue;
        }
        ind = func(str2, sec[i]);
        if(ind != -1 && dp[ind2[ind]] != -1) {
            dp[i] = ind2[ind];
            dir[i] = 1;
            continue;
        }
        ind = func(str3, thi[i]);
        if(ind != -1 && dp[ind3[ind]] != -1) {
            dp[i] = ind3[ind];
            dir[i] = 2;
            continue;
        }
    }
    if(dp[n] == -1) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    int num = n;
    while(num > 1) {
        char an = 'q';
        if(dir[num] == 1) an = 'k';
        else if(dir[num] == 2) an = 'j';
        ans.push_back({an, num});
        num = dp[num];
    }
    reverse(all(ans));
    cout << ans.size() << endl;
    for(auto &[ch, in] : ans) cout << ch << " " << in << endl;
    

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