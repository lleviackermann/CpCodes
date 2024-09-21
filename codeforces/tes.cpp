#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <cstring>
#include <time.h>
#include <chrono>
#include <random>
#include <ctime>
#include <iomanip>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (i = 0; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
#define mp make_pair
#define ff second
#define ss first
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x));
#define sortall(x) sort(all(x))
#define tr(it, arr) for (auto it = arr.begin(); it != arr.end(); it++)
#define PI 3.1415926535897932384626
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
const double pi = 3.141592653589793238;
const ll mod = 1e9+7;

void solve() {
    int n;
    cin >> n;
    string ans;
    bool direction = true;

    map <string, int> store;
    while (ans.size() != n) {
        int response;
        if (direction) {
            // check 0 
            ans.push_back('0');
            if (store[ans] == 0) {
                cout << "? " + ans << "\n";
                cout.flush();
                cin >> response;
                store[ans] = response + 1;
            } else {
                response = store[ans] - 1;
            }

            if (response) {
                continue;
            }
            ans.pop_back();

            // check 1
            ans.push_back('1');
            if (store[ans] == 0) {
                cout << "? " + ans << "\n";
                cout.flush();
                cin >> response;
                store[ans] = response + 1;
            } else {
                response = store[ans] - 1;
            }
            if (response) {
                continue;
            }
            ans.pop_back();

            direction = false;
        } else {
            // check 0 
            ans.insert(ans.begin(), '0');
            if (store[ans] == 0) {
                cout << "? " + ans << "\n";
                cout.flush();
                cin >> response;
                store[ans] = response + 1;
            } else {
                response = store[ans] - 1;
            }
            if (response) {
                continue;
            }
            ans.erase(ans.begin());

            // check 1
            ans.insert(ans.begin(), '1');
            if (store[ans] == 0) {
                cout << "? " + ans << "\n";
                cout.flush();
                cin >> response;
                store[ans] = response + 1;
            } else {
                response = store[ans] - 1;
            }
            if (response) {
                continue;
            }
            ans.erase(ans.begin());
        }
    }

    cout << "! " << ans << "\n";
}

int main(){
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}