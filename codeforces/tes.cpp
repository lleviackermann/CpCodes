#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    map<string,int> mapping;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        mapping[s]=i;
    }
    if(m==1){
        vector<pair<int,int>> store;
        while(q--){
            int sign,uid;
            string node;
            cin>>sign>>node>>uid;
            if(sign==1){
                if(store.size()){
                    cout<<false<<endl;
                }
                else{
                    store.push_back({mapping[node],uid});
                    cout<<true<<endl;
                }
            }
            else{
                if(store.size() && store[0].first == mapping[node] &&
                store[0].second == uid){
                    cout<<true<<endl;
                    store.pop_back();
                }
                else{
                    cout<<false<<endl;
                }
            }
        }
    }
    else{
        ll level = m;
        ll pa = 0;
        vector<ll> parent (n,-1);
        ll tem = 1;
        while(tem < n){
            ll lev = tem + level;
            int cnt = 0;
            while(tem <lev && tem <n){
                cnt++;
                parent[tem] = pa;
                tem++;
                if(cnt==m) pa++,cnt=0;
            }
            level *=m;
        }
        ll no_flag = -1e10 , des_flag = -1e10 +10;
        vector<ll> uid_store (n,no_flag);
        vector<ll> descending (n,0);
        set<int> locked_nodes;
        while(q--){
            int sign,uid;
            string node;
            cin>>sign>>node>>uid;
            int maped = mapping[node];
            if(sign == 1){
                bool pa_flag = false;
                int mp = maped;
                while(mp != -1){
                    if(uid_store[mp] != no_flag){
                        pa_flag=true;
                        break;
                    }
                    mp = parent[mp];
                }
                if(uid_store[maped]!=no_flag || pa_flag || descending[maped]>0){
                    cout<<"false"<<endl;
                }
                else{
                    mp= maped;
                    while(mp!= -1){
                        descending[mp]++;
                        mp=parent[mp];
                    }
                    uid_store[maped]=uid;
                    locked_nodes.insert(maped);
                    cout<<"true"<<endl;
                }
            }
            else if(sign == 2)
            {
                if(uid_store[maped]==uid){
                    int x = maped;
                    uid_store[maped]=no_flag;
                    while(maped != -1){
                        descending[maped]--;
                        maped = parent[maped];
                    }
                    locked_nodes.erase(x);
                    cout<<"true"<<endl;
                }
                else
                {
                    cout<<"false"<<endl;
                }
            } else {
                if(uid_store[maped] != no_flag) {
                    cout << "false" << endl;
                    continue;
                }
                vector<int> cur_node_desc;
                bool check = false;
                for(auto loc_nod : locked_nodes) {
                    int mp = loc_nod;
                    assert(uid_store[loc_nod] != no_flag);
                    while(mp != -1) {
                        if(mp == maped) {
                            if(uid_store[loc_nod] != uid) {
                                check = true;
                                break;
                            }
                            cur_node_desc.push_back(loc_nod);
                            break;
                        }
                        mp = parent[mp];
                    }
                }
                if(check) {
                    cout << "false" << endl;
                    continue;
                }
                for(auto loc_nod : cur_node_desc) {
                    int x = loc_nod;
                    uid_store[x]=no_flag;
                    locked_nodes.erase(loc_nod);
                    while(x != -1){
                        descending[x]--;
                        x = parent[x];
                    }
                }
                uid_store[maped] = uid;
                int mp= maped;
                while(mp!= -1){
                    descending[mp]++;
                    mp=parent[mp];
                }
                locked_nodes.insert(maped);
                cout << "true" << endl;
            }
        }
    }
}

int main() {
    int t=1;
    while(t--){
        solve();
    }
    return 0;
}