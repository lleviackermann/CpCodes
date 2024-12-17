#include <bits/stdc++.h>

using namespace std;

long long dist[100001], sub[100001], sum[100001];

vector<vector<int>> tre(100001);
const int l = 21;
vector<vector<long long>> up, store, childs;

void dfs1(int u, int v, int cnt) {
    sub[u] = 1;
    sum[u] = 0;
    dist[u] = cnt;
    up[u][0] = v;
    for (int i = 1; i <= l; ++i)
        up[u][i] = up[up[u][i-1]][i-1];

    for(auto &nei : tre[u]) {
        if(nei == v) continue;
        dfs1(nei, u, cnt + 1);
        sub[u] += sub[nei];
        sum[u] += sum[nei] + sub[nei];
    }
}

void preprocess(int root, int n) {
    up.assign(n+1, vector<long long>(l + 1));
    store.assign(n+1, vector<long long>(l+1, 1e18));
    childs.assign(n+1, vector<long long>(l + 1, 1e9));
    dfs1(root, root, 0);
    for(int j = 2; j <= n; j++) {
        int par = up[j][0];
        int remain_child = sub[par] - sub[j];
        int remain_sum = sum[par] - sum[j] - sub[j];
        store[j][0] = remain_sum + remain_child * 2;
        childs[j][0] = remain_child;
    }
    for(int i = 1; i <= l; i++) {
        for(int j = 1; j <= n; j++) {
            if(dist[j] < (1 << i)) continue;
            int par = up[j][i-1];
            store[j][i] = store[j][i-1] + store[par][i-1] + childs[par][i-1] * ((1 << (i-1)));
            childs[j][i] = childs[j][i-1] + childs[par][i-1];
        }
    }
}

int getKthAncestor(int node, int k) {
    int temp = node;
    for(int i = l; i >= 0; i--) {
        if(!(k & (1<<i))) continue;
        temp = up[temp][i];
        if(temp == -1) return temp;
    }
    return temp;
}

long long fin_ans = 1e18;
long long getKthValue(int node, int k) {
    long long ans = sum[node] + sub[node];
    long long temp = node;
    long long curr = 0;
    for(int i = l; i >= 0; i--) {
        if(!(k & (1<<i))) continue;
        ans += store[node][i] + childs[node][i] * curr;
        curr += (1 << i);
        node = up[node][i];
        if(ans == -1) return ans;
    }

    return ans;
}

void get_val(int curr) {
    int low = 0, high = dist[curr];

    int tem = 0, par = 0;
    while(low <= high) {
        int mid = (low + high) / 2;
        int manc = getKthAncestor(curr, mid);
        if(dist[manc] > mid + 1) tem = mid, par = manc, low = mid + 1;
        else high = mid - 1;
    }
    if(tem == 0) {
        long long v = sum[1] - sub[curr] * dist[curr] + sub[curr];
        fin_ans = min(fin_ans, v);
        // cout << "curr " << curr << " v " << v << endl;
        return;
    }
    long long ano = getKthValue(curr, tem);
    long long v = sum[1] - sum[par] - sub[par] * dist[par] + ano;
    // cout << "cr " << curr << " par " << par << " plus " << ano << " v " << v << endl;
    fin_ans = min(fin_ans, v);
}


int get_ans(int n, int m, int two, vector<vector<int>>& edges) {
    for(int i = 0; i < m; i++) {
        tre[edges[i][0]].push_back(edges[i][1]);
        tre[edges[i][1]].push_back(edges[i][0]);
    }
    long long ans = 1e18;
    preprocess(1, n);
    cout << sum[1] << endl;
    ans = sum[1];
    for(int i = 1; i <= n; i++) {
        if(dist[i] <= 1) continue;
        get_val(i);
        
    }
    return (int)fin_ans;
}

int main() {
    // vector<vector<int>> edges{{1, 2}, {1, 3}, {2, 4}, {4, 5}, {4, 6}, {5, 7}, {5, 8}, {8, 9}, {3, 10}, {10, 11}, {10, 12}, {11, 13}, {11, 15}, {15, 16}, {12, 14}};

    vector<vector<int>> edges{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}};
    int n, m, two;
    cin >> n >> m >> two;
    vector<vector<int>> edges;
    for(int i = 0; i < m; i++) {
        int fir, sec;
        cin >> fir >> sec;
        edges.push_back({fir, sec});
    }
    cout << get_ans(n, m, two, edges) << endl;
}