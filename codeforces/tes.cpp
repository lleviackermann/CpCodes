#include <bits/stdc++.h>

using namespace std;

int main() {
    long long r, x, y, nx, ny;
    cin >> r >> x >> y >> nx >> ny;
    
    double distance = sqrt((x - nx) * (x - nx) + (y - ny) * (y - ny));
    cout << ceil(distance / 2 * r) << endl;
    return 0;
}