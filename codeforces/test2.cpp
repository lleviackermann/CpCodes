#include <bits/stdc++.h>

using namespace std;

void solve(int m, int n) {
    int fx, fy, ix, iy, jx, jy;
    cin>>fx>>fy>>ix>>iy>>jx>>jy;
    vector<vector<int>> distance(m+1, vector<int>(n+1, 1e9));
    queue<pair<int, pair<int, int>>> store;
    store.push({0, {ix, iy}});
    distance[ix][iy] = 0;
    int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
    while(store.size()) {
        int dist = store.front().first;
        int x = store.front().second.first, y = store.front().second.second;
        store.pop();
        if(x == jx && y == jy) break;
        if(dist > distance[x][y]) continue;
        for(int a = 0; a < 4; a++) {
            int nx = x + dx[a], ny = y + dy[a];
            if(nx < 1 || nx > m || ny < 1 || ny > n) continue;
            if(distance[nx][ny] > distance[x][y] + 1) {
                distance[nx][ny] = distance[x][y] + 1;
                store.push({distance[nx][ny], {nx, ny}});
            }
        }
    }
    vector<vector<int>> distance(m+1, vector<int>(n+1, 1e9));
    queue<pair<int, pair<int, int>>> store;
    store.push({0, {ix, iy}});
    distance[ix][iy] = 0;
    int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
    while(store.size()) {
        int dist = store.front().first;
        int x = store.front().second.first, y = store.front().second.second;
        store.pop();
        if(x == jx && y == jy) break;
        if(dist > distance[x][y]) continue;
        for(int a = 0; a < 4; a++) {
            int nx = x + dx[a], ny = y + dy[a];
            if(nx < 1 || nx > m || ny < 1 || ny > n) continue;
            if(distance[nx][ny] > distance[x][y] + 1) {
                distance[nx][ny] = distance[x][y] + 1;
                store.push({distance[nx][ny], {nx, ny}});
            }
        }
    }
}


int main() {
    int m, n, t;
    cin>>m>>n>>t;
    while(t--) {

    }
}