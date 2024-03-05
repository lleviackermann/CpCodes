#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)9e9

void solve(){
	int k, x, y; cin >> k >> x >> y;
	if (k == 1){
		cout << 0 << "\n";
		return;
	}

	int curr=1;
	while(curr*k<INF) curr*=k;
	bool yes=0;
	x=abs(x);
	y=abs(y);
	while(curr>0){
		if(x<y) swap(x,y);
		// cout<<curr<<' '<<yes<<' '<<x<<' '<<y<<'\n';
		if(curr<=x){
			x=x-curr;
			yes=1;
		}
		else{
			if(yes){
				x=curr-x;
			}
			else if(curr-x+y<x+y){
				x=curr-x;
				yes=1;
			}
		}
		curr/=k;
	}
	cout<<x+y<<'\n';
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t = 1;
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}