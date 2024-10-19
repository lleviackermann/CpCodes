#include <bits/stdc++.h>
using namespace std;

const int MAX_R = 800;
const int MAX_C = 800;
int grid[MAX_R][MAX_C];

// Function to count valid hops with score <= M
long long countHops(int R, int C, int M) {
    long long count = 0;
    // Iterate over every burrow (i1, j1)
    for (int i1 = 0; i1 < R; ++i1) {
        for (int j1 = 0; j1 < C; ++j1) {
            int bunny1 = grid[i1][j1];
            // Check in the window of size M around (i1, j1)
            for (int i2 = max(0, i1 - M); i2 <= min(R - 1, i1 + M); ++i2) {
                for (int j2 = max(0, j1 - M); j2 <= min(C - 1, j1 + M); ++j2) {
                    if (i1 == i2 && j1 == j2) continue;  // Skip the same burrow
                    int bunny2 = grid[i2][j2];
                    if (bunny1 != bunny2) {
                        // Check if the Chebyshev distance is <= M
                        if (max(abs(i2 - i1), abs(j2 - j1)) <= M) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}

void solve() {
    int T;
    cin >> T;
    int tt = 0;
    while (T--) {
        tt++;
        long long R, C, K;
        cin >> R >> C >> K;
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> grid[i][j];
            }
        }
        
        // Binary search for the K-th smallest score
        int left = 0, right = max(R, C);
        while (left < right) {
            int mid = (left + right) / 2;
            if (countHops(R, C, mid) >= K) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        // cout << left << endl;
        cout << "Case #" << tt << ": " << left << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
