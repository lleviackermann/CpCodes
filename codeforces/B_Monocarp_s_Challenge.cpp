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


class Segtree {
private:
    int n;
    vector<int> seg, lay;

    pair<int, int> nex(int num) {
        return {2 * num + 1, 2 * num + 2};
    }

    void forward(int ind, int st, int en) {
        int& curr = lay[ind];

        if(curr == 0) return;
        seg[ind] = (en - st + 1) * curr;
        if(st != en) {
            auto [fir, sec] = nex(ind);
            lay[fir] += curr;
            lay[sec] += curr;
        } else seg[ind] = (seg[ind] + 10) % 10;
        curr = 0;
    }

    int getsum(int l, int r, int ind, int st, int en) {
        forward(ind, st, en);
        if(st > r || en < l) return 0;
        if(st >= l && en <= r) return seg[ind];
        int mid = (st + en) >> 1;
        auto [fir, sec] = nex(ind);
        int ans = getsum(l, r, fir, st, mid);
        ans += getsum(l, r, sec, mid + 1, en);
        return ans;
    }

    void update(int l, int r, int val, int ind, int st, int en) {
        forward(ind, st, en);
        if(st > r || en < l) return;
        if(st >= l && en <= r) {
            lay[ind] += val;
            forward(ind, st, en);
            return;
        }
        int mid = (st + en) >> 1;
        auto [fir, sec] = nex(ind);
        update(l, r, val, fir, st, mid);
        update(l, r, val, sec, mid+1, en);
        seg[ind] = seg[fir] + seg[sec];
    }

public:
    Segtree(string &s) {
        n = s.size();
        seg.resize(4*n+10, 0);
        lay.resize(4*n + 10, 0);
        build(s, 0, n-1, 0);
    }

    void build(string& s, int st, int en, int ind) {
        if(st == en) {
            seg[ind] = s[st] - '0';
            return;
        }
        int mid = (st + en) >> 1;
        auto [fir, sec] = nex(ind);
        build(s, st, mid, fir);
        build(s, mid + 1, en, sec);
        seg[ind] = seg[fir] + seg[sec];
    }

    int getsum(int l, int r) {
        return getsum(l, r, 0, 0, n-1);
    }

    int find_inc(int ind) {
        int low = 0, high = ind;
        int num = 0;
        while(low <= high) {
            int mid = (low + high) / 2;
            int tem = getsum(mid, ind);
            if(tem == 9 * (ind - mid + 1)) num = ind - mid + 1, high = mid - 1;
            else low = mid + 1;
        }
        return num;
    }

    int find_dec(int ind) {
        int low = 0, high = ind;
        int num = 0;
        while(low <= high) {
            int mid = (low + high) / 2;
            int tem = getsum(mid, ind);
            if(tem == 0) num = ind - mid + 1, high = mid - 1;
            else low = mid + 1;
        }
        return num;
    }

    void update(int l, int r, int val) {
        update(l, r, val, 0, 0, n-1);
    }

};

void solve() {
    int n, q;
    cin >> n >> q;

    string a;
    string b;
    cin >> a >> b;

    string sum(n, '0');

    int rem = 0;
    for (int i = n - 1; i >= 0; i--) {
        int first = a[i] - '0';
        int second = b[i] - '0';
        sum[i] = (((first + second + rem) % 10) + '0'); 
        rem = (first + second + rem) / 10;
    }
    debug(sum);

    Segtree segt(sum);

    auto ge = [](char c) {
        return c - '0';
    };

    for (int i = 0; i < q; i++) {
        int type, pos, newDigit;
        cin >> type >> pos >> newDigit;
        pos--;
        // if(ge(a[pos]))
        if(type == 1) {
            if(ge(a[pos]) == newDigit) {
                cout << segt.getsum(pos, pos) << " 0" << endl;
                continue;
            }
        } else {
            if(ge(b[pos]) == newDigit) {
                cout << segt.getsum(pos, pos) << " 0" << endl;
                continue;
            }
        }
        int prev_car = 0;
        int down = segt.getsum(pos, pos);
        int a_ = ge(a[pos]), b_ = ge(b[pos]);
        debug3(down, a_, b_);
        if((a_ + b_ + 1) % 10 == down) prev_car = 1;
        int old_val = a_ + b_ + prev_car;
        int cur_car = 0;
        if(a_ + b_ + prev_car > 9) cur_car = 1;
        int diff = 2;
        if(type == 1) {
            a[pos] = newDigit + '0';
            a_ = ge(a[pos]);
        } else {
            b[pos] = newDigit + '0';
            b_ = ge(b[pos]);
        }
        int newval = a_ + b_ + prev_car;
        int new_car = newval / 10;
        int newdig = newval % 10;
        debug4(a, b, newdig, prev_car);
        debug4(old_val, cur_car, newval, new_car);
        // int change = ((newval % 10) >= old_val ? (newval % 10) - old_val : )
        segt.update(pos, pos, (newval % 10) - old_val);
        if(new_car == cur_car || pos == 0) {
            cout << newdig << " " << 2 << endl;
            continue;
        }
        // if(pos == 0) continue;
        if(new_car == 1) {
            int num = segt.find_inc(pos-1);
            segt.update(max(0, pos-1-num), pos-1, 1);
            cout << newdig << " " << num + 3 << endl;
        } else {
            int num = segt.find_dec(pos-1);
            segt.update(max(0, pos-1-num), pos-1, -1);
            cout << newdig << " " << num + 3 << endl;
        }
    }
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