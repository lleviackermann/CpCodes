#include<stdio.h>

#define N 200000
#define M (2*N)

int n,t,head[N],nxt[M],vv[M],st[N];

void link(int i,int j)
{
    static int ii=1;
    nxt[ii]=head[i];
    vv[ii]=j;
    head[i]=ii++;
}

int dp[N];
void dfs(int u,int p)
{
    dp[u]='L';
    for(int j=head[u];j;j=nxt[j])if(vv[j]-p)
    {
        dfs(vv[j],u);
        if(dp[vv[j]]=='L')
            dp[u]='W';
    }
}

int main()
{
    scanf("%d%d",&n,&t);
    for(int i=1,u,v;i<n;++i)
        scanf("%d%d",&u,&v),link(--u,--v),link(v,u);

    for(int i=0;i<t;++i)
        scanf("%d",st);

    int rt=--st[0];
    dfs(rt,rt);
    puts(dp[rt]=='W'?"Ron":"Hermione");
}

