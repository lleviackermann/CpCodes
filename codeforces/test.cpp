#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
#define SZ(x) (int)x.size()
int modpow(int x,int n,int mod){
	int res=1;
	for(;n;n>>=1,x=1ll*x*x%mod){
		if(n&1)res=1ll*res*x%mod;
	}
	return res;
}
int T,n,v;
vector<int>now;
int gao(int dep,vector<int>q){
	int sz=SZ(q);
	if(!sz)return 0;
	if(dep<0)return 1ll*sz*sz%mod;
	vector<int>nex[2];
	for(int i=0;i<sz;++i)
	nex[q[i]>>dep&1].push_back(q[i]);
	int cnt0=SZ(nex[0]),cnt1=SZ(nex[1]);
	int ans=(1ll*cnt1*cnt1%mod+3ll*cnt0*cnt1%mod)%mod;
	ans=(ans+gao(dep-1,nex[0]))%mod;
	ans=(ans+gao(dep-1,nex[1]))%mod;
	return ans;
}
void sol(){
	now.clear();
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		scanf("%d",&v);
		now.push_back(v);
	}
	int ans=gao(30,now);
    cout<<ans<<endl;
	ans=1ll*ans*modpow(1ll*n*n%mod,mod-2,mod)%mod;
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--){
		sol();
	}
	return 0;
}