#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin>>n>>m;
    vector<vector<int>> mat(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x;
            cin>>x;
            mat[i].push_back(x);
        }
    }
    int ans = -1e9;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            
        }
    }
    cout<<ans<<endl;
    return 0;
}