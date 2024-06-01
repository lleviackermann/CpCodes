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

int lcs(int x, int y, int diff) {
    set<int> fir;
    int temp = x;
    while(temp >= 1) fir.insert(temp), temp /= 2;
    int dist = 0;
    int lcans = -1;
    temp = y;
    while(temp >= 1) {
        if(fir.count(temp)) {
            lcans = temp;
            break;
        }
        temp /= 2;
        dist++;
    }
    temp = x;
    while(temp != lcans) temp /= 2, dist++;
    if(dist > diff || ((dist & 1) ^ (diff & 1))) return -1;
    return lcans;
}

void solve()
{
    int n;
    cin >> n;
    vi arr(n);
    read(arr);
    int cnt = 0;
    for(auto i : arr) cnt += (i == -1);
    if(cnt == n) {
        for(int i = 1; i <= n; i++) {
            cout << (i & 1 ? 1 : 2) << " ";
        }
        line
        return;
    }
    int prev = -1;
    int fir = 1e9, sec = -1;
    for(int i = 0; i < n; i++) {
        if(arr[i] != -1) {
            fir = min(i, fir);
            sec = max(i, sec);
        }
        if(prev != -1 && arr[i] != -1) {
            int diff = i - prev;
            int lcans = lcs(arr[prev], arr[i], diff);
            debug(lcans);
            if(lcans == -1) {
                cout << "-1\n";
                return;
            }
            int x = arr[prev];
            prev++;
            while(x != lcans) {
                x /= 2; 
                arr[prev++] = x;
            }
            --prev;
            int dist = 0;
            int temp = arr[i];
            while(temp != lcans) dist++, temp /= 2;
            debug2(dist, prev);
            int di = i - prev;
            int ind = i - 1;
            if(di > dist) {
                int flag = 0;
                int te = arr[i];
                while(di != dist) {
                    te = (flag ? te / 2 : te * 2);
                    arr[ind--] = te;
                    flag ^= 1;
                        di--;
                }
            }
            int te = arr[i];
            while(ind > prev) te /= 2, arr[ind--] = te;
            prev = i;
        } else if(prev == -1 && arr[i] != -1) prev = i;
    }
    int te = arr[fir];
    fir--;
    int flag = 1;
    while(fir >= 0) {
        te = (flag ? 2 * te : te / 2);
        arr[fir--] = te;
        flag ^= 1;
    }
    te = arr[sec];
    sec++;
    flag = 1;
    while(sec < n) {
        te = (flag ? 2 * te : te / 2);
        arr[sec++] = te;
        flag ^= 1;
    }
    for(auto i : arr) cout << i << " ";
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