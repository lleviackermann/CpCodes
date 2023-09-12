#include <iostream>
#include <bits/stdc++.h>
// using namespace std;
#define int long long

const int LOG = 30;
const int MAXN = 100005;

int left[LOG][MAXN];
int right[LOG][MAXN];
int lval[LOG][MAXN];
int rval[LOG][MAXN];
int n;

int calc(int l, int r) {
  int total = 0;
  for(int i = 0; i < LOG; i++) {
    int ct = lval[i][l-1] + rval[i][r+1] + ((n-r)*(l-1) - (left[i][l-1]*right[i][r+1]));
    //std::cout << i << " " << ct << std::endl;
    total += ct*(1ll << i);
  }
//   std::cout<<l<<" "<<r<<" "<<total<<std::endl;
  return total;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while(t--) {
    int k;
    std::cin >> n >> k;

    int a[n+1];
    for(int i = 1; i <= n; i++)
      std::cin >> a[i];

    for(int i = 0; i < LOG; i++) {
      int b[n+2];
      int last = 0;
      //std::cout << " @ " << i << std::endl;
      for(int j = 1; j <= n; j++) {
        b[j] = (a[j] >> i)&1;
        if(b[j])
          last = j;
        left[i][j] = j-last;
        lval[i][j] = lval[i][j-1] + j-left[i][j];
        //std::cout << left[i][j] << ":" << lval[i][j] << " ";
      }
      //std::cout << std::endl;
      last = n+1;
      rval[i][n+1] = 0;
      right[i][n+1] = 0;
      for(int j = n; j >= 1; j--) {
        if(b[j])
          last = j;
        right[i][j] = last-j;
        rval[i][j] = rval[i][j+1] + (n-j+1)-right[i][j];
        //std::cout << right[i][j] << ":" << rval[i][j] << " ";
      }
      //std::cout << std::endl;
    }

    
    int ans = 0;
    int l = 1;
    for(int i = 1; i <= n; i++) {
    
      while(l <= i && calc(l, i) <= k)
        l++;
      ans += l-1;
    }

    std::cout << ans << "\n";
    /*
    for(int i = 1; i <= n; i++) {
      for(int j = i; j <= n; j++) {
        std::cout << "#" <<  i << " " << j << ": " << std::endl;
        int ret = calc(i, j);
        std::cout << "##" << ret << std::endl;
      }
    }
    */
  }

  return 0;
}

