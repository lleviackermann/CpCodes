#undef local
#include <bits/stdc++.h>
#define all(v) v.begin(),v.end()
#define allr(v) v.rbegin(),v.rend()
#define fori(i,n) for(int i=0;i<n;i++)
#define ford(i,n) for(int i = n-1;i >= 0;i--)
#define pb push_back
#define ll long long int
//#define mod 998244353
#define pi pair<int,int>
#define pll pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
#define printVector(v) fori(;,v.size()) {cout << v[i] << " ";} cout << "\n";
std::mt19937 rng((unsigned int) std::chrono::steady_clock::now().time_since_epoch().count());
using namespace std;
#define int long long
const int mod = 1e9 + 7;
void solve(int ttt)
{
    int n,q;
    cin >> n >> q;
    vector<pi> attach;
    vector<pi> quers;
    fori(i,q)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int l,r;
            cin >> l >> r;
            attach.pb({l,r});
        }
        else
        {
            int l,r;
            cin >> l >> r;
            quers.pb({l,r});
        }
    }
    sort(all(attach));
    int sz = attach.size();
    vector<int> par(n+1);
    iota(all(par),0);
    if(sz)
    {
        int curL = attach[0].fi;
        int curR = attach[0].se;
        for(int i= 1;i < sz;i++)
        {
            if(max(curL,attach[i].fi) <= min(curR,attach[i].se)){
                curL = min(curL,attach[i].fi);
                curR  = max(curR,attach[i].se);
            }
            else
            {
                for(int p = curL;p <= curR;p++)
                {
                    par[p] = curL;
                }
                curL = attach[i].fi;
                curR = attach[i].se;
            }
        }
        for(int p = curL;p <= curR;p++)
        {
            par[p] = curL;
        }
    }
    vector<int> id(n+1,-1);
    int curId = 0;
    for(int i = 0;i <= n;i++)
    {
        if(par[i] == i)
        {
            id[i] =curId;
            curId++;
        }
    }
    vector<vector<int> > nwQuers(curId + 1);
    for(pi p:quers)
    {
        int r = id[par[p.se]];
        int l = id[par[p.fi]];
        nwQuers[r].pb(l);
        if(r == l)
        {
            cout << "0\n";
            return;
        }
    }
    vector<int> dp(curId,0);
    vector<int> dp2(curId, 0);
    dp[0] = 1;
    dp2[0] = 1;
    int prevMx = - 1;
    int cSum = 1,cSum1 = 1;
    for(int i = 1;i < curId;i++)
    {
        int mx = -1;
        if(nwQuers[i].size())
        {
            mx = *max_element(all(nwQuers[i]));
        }
        for(int j = prevMx + 1;j < mx;j++)
        {
            cSum = (cSum - dp2[j] + mod) % mod;
            cSum1 = (cSum1 - dp[j] + mod) % mod;
            dp[j] = 0;
            dp2[j] = 0;
        }
        dp[i] = cSum1;
        dp2[i] = cSum;
        cout<<dp[i]<<" "<<dp2[i]<<endl;
        cSum = (cSum + dp[i]) % mod;
        cSum1 = (cSum1 + dp2[i]) % mod;
        prevMx = max(prevMx,mx-1);
    }
    cout << (dp[curId-1] + dp2[curId-1])%mod << "\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int ttt;
    ttt = 1;
    //cin >> ttt;
    fori(i,ttt) solve(i);
}
