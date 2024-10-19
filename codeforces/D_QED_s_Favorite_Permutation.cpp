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

const int nmax = 2e5+2;
vector<array<int, 2>> seg(2*nmax, {(int)1e9, 1});

int n_new;
void build(vi& temp) {
    for(int i = 0; i < n_new; i++) seg[i + n_new] = {temp[i], temp[i]}; 
    for(int i = n_new - 1; i >= 0; i--) {
        seg[i] = {min(seg[i << 1][0], seg[i << 1 | 1][0]), max(seg[i << 1][1], seg[i << 1 | 1][1])};
    }
}

array<int, 2> query(int l, int r) {
    l += n_new, r += n_new;
    array<int, 2> ans = {(int)1e9, 0};
    for(; l < r; l >>= 1, r >>= 1) {
        if(l & 1) {
            ans[0] = min(ans[0], seg[l][0]);
            ans[1] = max(ans[1], seg[l][1]);
            l++;
        }
        if(r & 1) {
            --r;
            ans[0] = min(ans[0], seg[r][0]);
            ans[1] = max(ans[1], seg[r][1]);
        }
    }
    return ans;
}

void solve()
{
    ll q;
    int n;
    cin >> n >> q;
    n_new = n + 1;
    vl arr(n);
    read(arr);
    vi temp(n+1, 0);
    for(int i = 0; i < n; i++) temp[arr[i]] = i + 1;
    build(temp);
    string s;
    cin >> s;
    vi left(n+1, -1), right(n+1, -1);
    for(int i = 0; i < n;) {
        int st = i;
        i++;
        while(i < n) {
            if(i && s[i-1] == 'L' && s[i] == 'R') {
                break;
            }
            i++;
        }
        left[st+1] = i;
        right[i] = st+1;
    }
    print(left);
    print(right);
    // auto tem = query(1, 2);
    // debug2(tem[0], tem[1]);
    set<int> fal;
    // auto check = [&]()
    set<int> st;
    for(int i = 1; i <= n; i++) {
        if(left[i] != -1) {
            st.insert(left[i]);
            auto [fir, sec] = query(i, left[i] + 1);
            if(fir < i || sec > left[i]) fal.insert(i);
        }
    }
    auto update = [&](int ind) {
        st.insert(left[ind]);
        auto [fir, sec] = query(ind, left[ind] + 1);
        if(fir < ind || sec > left[ind]) fal.insert(ind);
        else if(fal.count(ind)) fal.erase(ind);
    };
    print(fal);
    while(q--) {
        int ind;
        cin >> ind;
        // --ind;
        int tr = ind - 1;
        if(left[ind] != -1) {
            int cur_r = left[ind];
            int prev_l = right[ind-1];
            left[prev_l] = ind;
            right[ind-1] = -1;
            right[ind] = prev_l;
            right[cur_r] = ind + 1;
            left[ind + 1] = cur_r;
            left[ind] = -1;
        } else if(right[ind] != -1) {
            int cur_l = right[ind];
            left[cur_l] = ind - 1;
            right[ind-1] = cur_l;
            left[ind] = left[ind+1];
            right[left[ind]] = ind;
            left[ind+1] = -1;
            right[ind] = -1;
        } else if(s[ind-1] == 'R' && s[ind] == 'R') {
            auto it = st.upper_bound(ind);
            int in = right[*it];
            debug(in);
            int nex = left[in];
            left[in] = ind;
            right[ind] = in;
            right[nex] = ind + 1;
            left[ind + 1] = nex;
        } else if (s[ind-1] == 'L' && s[ind-2] == 'L') {
            auto it = st.upper_bound(ind);
            int in = right[*it];
            debug(in);
            int nex = left[in];
            left[in] = ind - 1;
            right[ind - 1] = in;
            right[nex] = ind;
            left[ind] = nex;
        }
        if(s[tr] == 'L') s[tr] = 'R';
        else s[tr] = 'L';
        if((s[ind-2] == 'R' && (s[ind-1] == 'L' || s[ind-1] == 'R') || (s[ind-2] == 'L' && s[ind-1] == 'L'))) {
            if(left[ind] != -1 && right[ind-1] != -1) {
                left[right[ind-1]] = left[ind];
                right[left[ind]] = right[ind-1];
                right[ind-1] = -1;
                left[ind] = -1;
            }
        }
        if((s[ind-1] == 'R' && (s[ind] == 'L' || s[ind] == 'R')) || (s[ind - 1] == 'L' && s[ind] == 'L')) {
            if(left[ind+1] != -1 && right[ind] != -1) {
                left[right[ind]] = left[ind+1];
                right[left[ind+1]] = right[ind];
                right[ind] = -1;
                left[ind+1] = -1;
            }
        }
        if(left[ind] != -1) update(ind);
        else fal.erase(ind);
        // else store.erase()
        if(right[ind] != -1) update(right[ind]);
        else st.erase(ind);
        if(left[ind-1] != -1) update(ind-1);
        else fal.erase(ind-1);
        if(right[ind-1] != -1) update(right[ind-1]);
        else st.erase(ind-1);
        if(left[ind+1] != -1) update(ind+1);
        else fal.erase(ind+1);
        if(right[ind+1] != -1) update(right[ind+1]);
        else st.erase(ind+1);
        auto it = st.upper_bound(ind);
        update(right[*it]);
        // if(left[ind])
        debug(ind);
        print(left);
        print(right);
        // debug(s);
        // debug(s[tr]);
        assert(tr >= 0 && tr < s.size());
        // s[tr] = (s[tr] == 'L' ? 'R' : 'L');
        print(fal);
        if(fal.size()) cout << "NO\n";
        else cout << "YES\n";
    }
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