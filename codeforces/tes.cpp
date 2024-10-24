#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,m,d,p;
const ll mod=1e9+7;
void solve()
{
    ll n,k;
    scanf("%lld%lld",&n,&k);
    ll cnt=0;
    ll l=0,r=1;
    while(1)
    {
        swap(l,r);
        (l+=r)%=k;
        cout << l << " " << r << endl;
        cnt++;
        if(!l) break;
    }
    cout << cnt << endl;
    printf("%lld\n",((n%mod)*cnt)%mod);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
	return 0;
}