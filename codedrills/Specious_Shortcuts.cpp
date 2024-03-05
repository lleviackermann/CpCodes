#include <bits/stdc++.h>

using namespace std;

void shortest(vector<long long> &distance, int src, vector<vector<int>> &graph) {
    queue<int> store;
    distance[src] = 0;
    store.push(src);
    while(store.size()) {
        int to = store.front();
        store.pop();
        for(auto nei : graph[to]) {
            if(distance[nei] > distance[to] + 1) {
                distance[nei] = distance[to] + 1;
                store.push(nei);
            }
        }
    }
}

void solve() {
    int n, p, k, s, t;
    cin>>n>>p>>k>>s>>t;
    for(int i = 0; i < k; i++) {
        int x;
        cin>>x;
    }
    if(s > t) swap(s, t);
    int flag = 0;
    vector<vector<int>> graph(n+1);
    for(int i = 0; i < p; i++) {
        int st, en;
        cin>>st>>en;
        graph[st].push_back(en);
        graph[en].push_back(st);
        if(min(st, en) == s && max(st, en) == t) flag = 1;
    }
    vector<long long> disa(n+1, 1e9), disb(n+1, 1e9);
    shortest(disa, s, graph);
    shortest(disb, t, graph);
    // for(auto i : disa) cout<<i<<" ";
    // cout<<endl;
    // for(auto i : disb) cout<<i<<" ";
    // cout<<endl;
    vector<map<long long, long long>> freq(n+1);
    
    for(int i = 1; i <= n; i++) {
        freq[disa[i]][disb[i]]++;
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        for(auto ele : freq[i]) {
            long long fir = ele.first, sec = ele.second;
            ans += (sec * (sec - 1) / 2);
            if(freq[i].count(fir+1)) {
                ans += sec * freq[i][fir+1]; 
            }
            if(freq[i-1].count(fir)) {
                ans += sec * freq[i-1][fir];
            }
            if(freq[i-1].count(fir-1)) {
                ans += sec * freq[i-1][fir-1];
            }
            if(freq[i-1].count(fir + 1)) {
                ans += sec * freq[i-1][fir+1];
            }
        }
    }
    // cout<<ans<<endl;
    if(!flag) {
        graph[s].push_back(t);
        graph[t].push_back(s);
    }
    vector<long long> temp(n+1, 1e9);
    shortest(temp, s, graph);
    int count = 0;
    // for(auto i : temp) cout<<i<<" ";
    // cout<<endl;
    for(int i = 1; i <= n; i++) if(disa[i] != temp[i]) count++;
    if(count == 1) {
        temp.clear();
        temp.resize(n+1, 1e9);
        shortest(temp, t, graph);
        count = 0;
        for(int i = 1; i <= n; i++) if(disb[i] != temp[i]) count++;
        // for(auto i : temp) cout<<i<<" ";
        // cout<<endl;
        if(count == 1) ans++;
    }
    // cout<<ans<<endl;
    cout<<ans - p<<endl;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
}