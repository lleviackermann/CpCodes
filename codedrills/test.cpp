#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) begin(x), end(x)

const int MX = 2e6;

int check(vector<pair<int, int>> & ans) {
    int n = ans.size();
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        assert(ans[i].first <= MX);
        assert(ans[i].second <= MX);
        for (int j=i+1;j<n;++j) {
            int now = abs((ans[i].first - ans[j].first) * (ans[i].second - ans[j].second));
            int s = sqrtl(now);
            if(s*s==now) {
                // cout<< "AYSDDfg\n";
                // cout << ans[i].first << ' ' << ans[i].second << endl;
                // cout << ans[j].first << ' ' << ans[j].second << endl;
                cnt++;
            }
        }
    }

    return cnt;
}

void solve() {
    int k;
    cin>>k;
    const int K = k;
    vector<pair<int,int>> ans;
    pair<int, int> lst = {1, 1}; 
    int j = 1;
    while (k > 0) {
        for(;j<=3000;j++)
        {
            if(((j*(j+1))/2) > k) {
                int left=k-((j*(j+1))/2);
                for(int i=0;i<j;i++)
                {
                    // cout << "ADDING " << lst.first + i <<  ' ' << lst.second + i << endl;
                    ans.push_back({lst.first + i, lst.second + i});
                }
                k -= ((j*(j-1))/2);
                lst.first = ans.back().first + 809;
                lst.second = ans.back().second + 811;
                break;
            }
        }
        // cout << "LAST HERRE" << lst.first << ' ' << lst.second << endl;
        j = 1;
    }
    
    for(int l=ans.size();l<2023;l++)
    {
        ans.push_back(lst);
        lst.first+=809;
        lst.second+=811;
    }
 
    // cout << check(ans) << endl;
    // assert(K == check(ans));

    for(int p=0;p<2023;p++)
    {
        cout<<ans[p].first<<" "<<ans[p].second<<"\n";
    }
    cout<<"-1\n";
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while(T--) solve();
}