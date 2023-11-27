// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
// #pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;
typedef long long ll;
#define pb push_back
#define ff first
#define ss second
#define INF 6223372004895760000
#define NIL 0
#define int ll
// #define ll int
#define debug cout << "here\n";
using vll=vector<ll>;
using vi=vector<int>;
using vpl = vector<pair<ll, ll>>;
using pll = pair<ll, ll>;
ll mod = 1000000007;
ll mod2 = 998244353;
ll MOD = mod2;
ll tcnt = 1;
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
// #define ordered_set tree<pll, null_type,less<pll>, rb_tree_tag,tree_order_statistics_node_update>
const int MAXN = 200005;
ll ipow(ll base, ll k, ll M) {
    base %= M;
    k = k % (M - 1);
    ll total = 1;
    while(k) {
        if(k & 1) {
            total = (total * base) % M;
        }
        base = (base * base) % M;
        k >>= 1;
    }
    return total;
}

ll modu(ll a,ll b) {
  ll c = a % b;
  return (c < 0) ? c + b : c;
}
inline uint64_t modpow(uint64_t base, uint64_t exp, uint64_t modulus) {
    base %= modulus;
    uint64_t result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}
 
inline uint64_t modinv(uint64_t x, uint64_t mod) {
    return modpow(x, mod - 2, mod);
}
 
uint64_t fak[MAXN];
 
void precomp() {
    fak[0] = fak[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fak[i] = i*fak[i - 1];
        fak[i] %= MOD;
    }
}
 
inline uint64_t nCr(uint64_t n, uint64_t r) {
    uint64_t res = fak[n] * modinv(fak[r], MOD);
    res %= MOD; 
    res *= modinv(fak[n - r], MOD);
    res %= MOD;
    return res;
}

ll intlen(ll n) {
    ll cnt = 0;
    while(n) {
        n /= 10;
        cnt++;
    }
    return cnt;
}

ll invsix = modinv(6, mod);
ll dp[151][61][11][107][3];

void preprocess() {
    ll n,b,w,x;
    n = 150, b = 60, w = 10, x = 107;
    // for(ll i = n; i >= 0; i--){
    //     for(ll j = b; j >= 0; j--){
    //         for(ll k = w; k < 10; k++){
    //             for(ll l = x; l <= 100; l++){
    //                 for(ll p = 0; p<3; p++){
    //                     dp[i][j][k][l][p] = 0;
    //                 }
    //             }
    //         }
    //     }
    // }
    memset(dp, 0, sizeof(dp));
    dp[n][b][w][x][1] = 1;
    for(ll i = n; i >= 1; i--){
        for(ll j = b; j >= 1; j--){
            for(ll k = 0; k < 10; k++){
                for(ll l = 0; l <= 100; l++){
                    for(ll p = 1; p<7; p++){
                        if(p == 5)continue;
                        ll run = max(0ll, i - p);
                        ll kohli = min(l + p, 100ll);
                        // if(dp[i][j][k][l][1] > 0)cout << j << " " <<  p << " " << l << "\n";
                        if(((j%6 == 1 && (p%2 == 1))||(j%6 != 1 && (p%2 == 0)))){
                            dp[run][j - 1][k][kohli][1] += (dp[i][j][k][l][1]*invsix)%mod;
                            // if(dp[i][j][k][l][1] > 0)debug
                            dp[run][j - 1][k][l][0] += (dp[i][j][k][l][0]*invsix)%mod;
                            dp[run][j - 1][k][kohli][1] %= mod;
                            dp[run][j - 1][k][l][0] %= mod;
                            dp[run][j - 1][k][l][2] += (dp[i][j][k][l][2]*invsix)%mod;
                            dp[run][j - 1][k][l][2] %= mod;
                        }
                        else{
                            // if(dp[i][j][k][l][1] > 0)cout << "dpw\n";
                            dp[run][j - 1][k][l][1] += (dp[i][j][k][l][0]*invsix)%mod;
                            dp[run][j - 1][k][kohli][0] += (dp[i][j][k][l][1]*invsix)%mod;
                            dp[run][j - 1][k][l][1] %= mod;
                            dp[run][j - 1][k][kohli][0] %= mod;
                            dp[run][j - 1][k][l][2] += (dp[i][j][k][l][2]*invsix)%mod;
                            dp[run][j - 1][k][l][2] %= mod;
                        }
                    }
                    
                    if(j%6 == 1){
                        dp[i][j - 1][k + 1][l][1] += (dp[i][j][k][l][0]*invsix)%mod;
                        dp[i][j - 1][k + 1][l][1] %= mod;
                        dp[i][j - 1][k + 1][l][2] += (dp[i][j][k][l][1]*invsix)%mod;
                        dp[i][j - 1][k + 1][l][2] += (dp[i][j][k][l][2]*invsix)%mod;
                        dp[i][j - 1][k + 1][l][2] %= mod;
                    }
                    else{
                        dp[i][j - 1][k + 1][l][0] += (dp[i][j][k][l][0]*invsix)%mod;
                        dp[i][j - 1][k + 1][l][0] %= mod;
                        dp[i][j - 1][k + 1][l][2] += (dp[i][j][k][l][1]*invsix)%mod;
                        dp[i][j - 1][k + 1][l][2] += (dp[i][j][k][l][2]*invsix)%mod;
                        dp[i][j - 1][k + 1][l][2] %= mod;
                    }
                }
            }
        }
    }
}
void solve(){
    ll n,b,w,x;
    cin>>n>>b>>w>>x;
    ll ans = 0;

    for(ll i=0; i<b; i++){
        for(ll j = 0; j<10; j++){
                // cout << i << " " << j << " " << k << " " << dp[0][i][j][k][0] << " " << dp[0][i][j][k][1] << "\n";
                ans += dp[0][i][j][100][0];
                ans += dp[0][i][j][100][1];
                ans += dp[0][i][j][100][2];
                ans %= mod;
            
        }
    }
    cout << ans << "\n";
}

signed main(){
    // precomp();
    // fast
    // #ifndef ONLINE_JUDGE
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    // #endif
    ll tc = 1, cnt = 1;
    preprocess();
    // cout << setprecision(20);
    cin >> tc;
    while(tc--){
        // cout << "Case #" << cnt++ << ": ";
        solve();
        tcnt++;
    }
}