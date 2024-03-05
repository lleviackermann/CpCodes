#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll query(ll x,ll y){
  cout<<"? "<<x<<" "<<y<<endl;
  ll d;
  cin>>d;
  return d;
}
void answer(ll x,ll y){
  cout<<"! "<<x<<" "<<y<<endl;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    int upperleft, bottomright, upperright, bottomleft;
    cout << "?"
         << " " << 1 << " " << 1 << endl;
    cout.flush();
    cin >> upperleft;
    cout << "?"
         << " " << n << " " << m << endl;
    cout.flush();
    cin >> bottomright;
    cout << "?"
         << " " << n << " " << 1 << endl;
    cout.flush();
    cin >> bottomleft;
    upperleft += 2;
    bottomright = n + m - bottomright;
    bottomleft += 1 - n;
    long long x1=(upperleft-bottomleft)/2,y1=(upperleft+bottomleft)/2,x2=(bottomright-bottomleft)/2,y2=(bottomright+bottomleft)/2;
    cerr<<x2<<" "<<y2;
    if(1<=x1&&x1<=n&&1<=y1&&y1<=m&&query(x1,y1)==0) answer(x1,y1);
    else answer(x2,y2);
}   

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}