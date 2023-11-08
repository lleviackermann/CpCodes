#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()

int entry = -1;
bool dfs(int source,vector<int> adjList[],vector<int>& visited,vector<int>& dist,int d){
    // cout<<source;
    for(auto it : adjList[source]){
        if(visited[it] == 0){
            visited[it] = source;
            dist[it] = d;
            if(dfs(it,adjList,visited,dist,d+1)){
                return true;
            }
        }else{
            if(it!=visited[source]){
                // cout<<it;
                entry = it;
                return true;
            }
        }

    }
    return false;

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;cin>>t;
    while(t--){
        int n ,a,b;
        cin>>n>>a>>b;

        vector<int> adjList[n+1];
        for(int i=0;i <n; ++i){
            int u,v;cin>>u>>v;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        if(a == b){
            cout<<"NO\n";
            continue;
        }
        vector<int> visited(n+1,0);
        vector<int> dist(n+1,0);
        visited[b] = -1;
        dist[b] = 0;
        dfs(b,adjList,visited,dist,1);
        // cout<<entry<<endl;
        int val = dist[entry];
        // cout<<entry<<' '<<val<<endl;
        for(auto &it: visited){
            it =0;
        }
        for(auto &it: dist){
            it = 0;
        }
        visited[a] = 1;
        dist[a] = 0;
        queue<pair<int,int>> q;
        q.push({a,0});
        int store ;
        while(!q.empty()){
            int u = q.front().first;
            int d = q.front().second;
            q.pop();
            for(auto it : adjList[u]){
                if(!visited[it]){
                    visited[it] = 1;
                    dist[it] = d + 1;
                    if(it == entry){
                        store = d +1;
                    }
                    q.push({it,d+1});
                }
            }
        }
        // cout<<store<<endl;
        if(store > val){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
    }
    return 0;
}