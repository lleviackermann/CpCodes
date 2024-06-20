#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10,mod=1e9+7;
int trie[N][2],cnt[N][2];
int tot=0;
int newNode(){
    int x=++tot;
    trie[x][0]=trie[x][1]=0;
    cnt[x][0]=cnt[x][1]=0;
    return x;
}
void add(int x,int d,int t=1){
    int p=1;
    cnt[p][d]+=t;
    for(int i=30;i>=1;i--){
        int u=(x>>(i-1)&1);
        if(!trie[p][u]){
            trie[p][u]=newNode();
        }
        p=trie[p][u];
        cnt[p][d]+=t;
    }
}
int query(int x,int d){
    int p=1;
    if(!cnt[p][d]){
        return 0;
    }
    int ans=0;
    for(int i=30;i>=1;i--){
        int u=(x>>(i-1)&1);
        if(cnt[trie[p][u^1]][d]){
            ans|=(1<<(i-1));
            p=trie[p][u^1];
        }
        else p=trie[p][u];
    }
    return ans;
}
void solve(){
    int n,m; cin>>n>>m;
    vector<pair<int,int>>g[n+1];
    for(int i=1;i<n;i++){
        int a,b,c; cin>>a>>b>>c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    vector<int>a(n+1),d(n+1);
    function<void(int,int)>dfs;
    dfs=[&](int u,int fa)->void{
        for(auto now:g[u]){
            int x=now.first,w=now.second;
            if(x==fa) continue;
            d[x]=d[u]^1;
            a[x]=a[u]^w;
            dfs(x,u);
        }
    };
    dfs(1,0);
    tot=0;
    newNode();
    for(int i=1;i<=n;i++){
        add(a[i],d[i]);
    }
    int w=0;
    while(m--){
        char op; cin>>op;
        if(op=='^'){
            int y; cin>>y;
            w^=y;
        }
        else{
            int u,x; cin>>u>>x;
            add(a[u],d[u],-1);
            cout<<max(query(a[u]^x,d[u]),query(a[u]^x^w,d[u]^1))<<" ";
            add(a[u],d[u]);
        }
    }
    cout<<'\n';
}
signed main(){
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);int t;cin>>t;while(t--)solve();
}
