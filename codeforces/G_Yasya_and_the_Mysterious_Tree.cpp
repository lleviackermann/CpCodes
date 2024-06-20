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
#define trie fdskajfk
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

const int nmax = 2e5+10;
vector<vector<pi>> graph(nmax);

// binary trie implementation
struct trie {
    int bit;
    int cnt;
    trie* left;
    trie* right;

    trie(){
        bit = -1;
        cnt = 0;
        left = nullptr;
        right = nullptr;
    }

    trie(int flag) {
        bit = flag;
        cnt = 0;
        left = nullptr;
        right = nullptr;
    }

};

void solve()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= n; i++) graph[i].clear();
    for(int i = 1; i < n; i++) {
        int st, en, wt;
        cin >> st >> en >> wt;
        graph[st].push_back({en, wt});
        graph[en].push_back({st, wt});
    }

    trie* odd_dist = new trie();
    trie* even_dist = new trie();

    
    auto add_number = [&](int number, int odd) {
        trie* current;
        if(odd) current = odd_dist;
        else current = even_dist;
        for(int i = 30; i >= 0; i--) {
            if(number & (1 << i)) {
                if(current->right == nullptr) current->right = new trie(1);
                current = current->right;
            }
            else {
                if(current->left == nullptr) current->left = new trie(0);
                current = current->left;
            }
            current->cnt++;
        }
    };

    auto print_trie = [&](auto&& print_trie, trie* curr, int l, int num) -> void {
        if(l != 31 && curr->cnt <= 0) return;
        if(l > 0) {
            if(curr->right) print_trie(print_trie, curr->right, l-1, num | (max(0, curr->bit)<< l));
            if(curr->left) print_trie(print_trie, curr->left, l-1, num | (max(0, curr->bit) << l));
        } else {
            cout << (num | (curr->bit << l)) << endl;
            return;
        }
    };

    vi place(n+1, 0);
    vl xor_num(n+1, 0);
    auto erase = [&](int num) -> void {
        trie* current;
        if(place[num]) current = odd_dist;
        else current = even_dist;
        int l = 30;
        debug2(place[num], xor_num[num]);
        ll te = xor_num[num];
        while(l >= 0 && current != nullptr) {
            if(te & (1 << l)) current = current->right;
            else current = current->left;
            current->cnt--;
            assert(current->cnt >= 0);
            l--;
        }
    };
    
    auto dfs = [&](auto&& dfs, int xord, int dist, int u, int v) -> void {
        if(dist & 1) place[u] = 1;
        xor_num[u] = xord;
        if(dist & 1) add_number(xord, 1);
        else add_number(xord, 0);

        for(auto [nei, wei] : graph[u]) {
            if(nei == v) continue;
            dfs(dfs, xord ^ wei, dist ^ 1, nei, u);
        }
    };

    ll curr_xor = 0;
    auto calc_max = [&](int num, ll x) -> void {
        // print_trie(print_trie, odd_dist, 31, 0);
        erase(num);
        // print_trie(print_trie, odd_dist, 31, 0);
        ll prexor = xor_num[num] ^ x;
        if(place[num]) prexor ^= curr_xor;
        debug(prexor);
        ll ans = 0;
        ll curr = 0;
        trie* temp = even_dist;
        for(int i = 30; temp != nullptr && i >= 0; i--) {
            int pre_bit = (prexor & (1 << i));
            if(pre_bit) {
                if(temp->left && temp->left->cnt > 0) {
                    curr = curr | (1ll << i);
                    temp = temp->left;
                } else temp = temp->right;
            } else {
                if(temp->right && temp->right->cnt > 0) {
                    curr = curr | (1ll << i);
                    temp = temp->right;
                } else temp = temp->left;
            }
        }
        debug(curr);
        ans = curr;
        curr = 0;
        prexor = prexor ^ curr_xor;
        debug(prexor);
        temp = odd_dist;
        for(int i = 30; temp != nullptr && i >= 0; i--) {
            int pre_bit = (prexor & (1 << i));
            if(pre_bit) {
                if(temp->left && temp->left->cnt > 0) {
                    curr = curr | (1ll << i);
                    temp = temp->left;
                } else temp = temp->right;
            } else {
                if(temp->right && temp->right->cnt > 0) {
                    curr = curr | (1ll << i);
                    temp = temp->right;
                } else temp = temp->left;
            }
        }
        debug(curr);
        ans = max(ans, curr);
        cout << ans << " ";
        if(place[num]) add_number(xor_num[num], 1);
        else add_number(xor_num[num], 0);
    };
    dfs(dfs, 0, 0, 1, -1);
    // print_trie(print_trie, odd_dist, 31, 0);
    // debug(n);
    // print_trie(print_trie, even_dist, 31, 0);
    // erase(4);
    // print_trie(print_trie, odd_dist, 31, 0);
    while(m--) {
        char c;
        cin >> c;
        if(c == '^') {
            ll te;
            cin >> te;
            curr_xor ^= te;
        } else {
            ll vet, te;
            cin >> vet >> te;
            calc_max(vet, te);
        }
    }
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