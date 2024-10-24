/**
 *    author:  tourist
 *    created: 19.10.2024 09:59:19
**/
#undef _GLIBCXX_DEBUG

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int64_t low, high;
    int md;
    cin >> low >> high >> md;
    high += 1;
    int64_t ans = 0;
    for (int len = 0; len <= 8; len++) {
      for (int mid = 1; mid <= 9; mid++) {
        vector<pair<int, int>> a;
        auto Gen = [&](auto&& self, int v, int w, int lim) -> void {
          if (v == len) {
            a.push_back({w % md, w});
            return;
          }
          for (int d = 1; d <= lim; d++) {
            // int ex = (v == 0 ? lim : lim - 1);
            // if (d != ex) {
            //   continue;
            // }
            self(self, v + 1, w * 10 + d, d);
          }
        };
        Gen(Gen, 0, 0, mid - 1);
        sort(a.begin(), a.end());
        int64_t p10 = 1;
        for (int i = 0; i < len; i++) {
          p10 *= 10;
        }
        auto Calc = [&](auto&& self, int v, int64_t sum, int64_t coeff, int lim) -> void {
          if (v == len) {
            int needle = int((md - sum % md) % md);
            // low <= sum + x < high
            int64_t from = max<int64_t>(0, low - sum);
            int64_t to = min(p10, high - sum);
            if (from < to) {
              auto it1 = lower_bound(a.begin(), a.end(), make_pair(needle, int(from)));
              auto it2 = lower_bound(a.begin(), a.end(), make_pair(needle, int(to)));
              ans += int(it2 - it1);
            }
            return;
          }
          for (int d = 1; d <= lim; d++) {
            // int ex = (v == 0 ? lim : lim - 1);
            // if (d != ex) {
            //   continue;
            // }
            self(self, v + 1, sum + coeff * d, coeff * 10, d);
          }
        };
        Calc(Calc, 0, mid * p10, p10 * 10, mid - 1);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
