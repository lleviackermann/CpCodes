/**
 *    author:  devangsvaghani
 *    created: 03.10.2024 13:18:48
**/

#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define all(x) (x).begin(), (x).end()
#define F first
#define S second
#define f(i, x, n) for (ll i = x; i < n; i++)
#define rf(i, x, n) for (ll i = x; i >= n; i--)

const ll mod = 1e9+7;
const ll mod2 = 998244353;
const ll N = 1e6+5;

void init(){
    
}

void solve(){
    ll n, k;
    cin >> n >> k;
    
    vector<ll> v(n);
    f(i, 0, n) cin >> v[i];
    
    bool flag = true, flag1 = true;
    f(i, 0, n){
        flag1 &= (v[i] == k);
        flag &= (v[i] % k == 0);
    }
    
    if(flag1){
        cout << "0\n";
        return;
    }
    
    if(flag){
        cout << 1 << "\n";
        return;
    }
    
    ll prev = k;
    ll ans = 0;
    
    f(i, 0, n){
        if(v[i] == prev){
            
        }else{
            ans += (prev != k);
            prev = v[i];
        }
    }
    
    ans += (prev != k);
    
    cout << min(ans, 2ll) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    // #ifndef ONLINE_JUDGE
    //   freopen("input.txt", "r", stdin);
    //   freopen("output.txt", "w", stdout);
    //   freopen("Error.txt", "w", stderr);
    // #endif

    init();
    
    ll t = 1;
    cin >> t;
    for (ll T = 1; T <= t; T++) {
        // debug(T);
        solve();
    }
    return 0;
}