#include<bits/stdc++.h>
using namespace std;

int mod = 1e9+7;
long long binPowr(long long a,long long b){
    long long cur = 1;
    long long n = a;
    while(b>0){
        if(b&1){
            cur *= n%mod;
            cur%=mod;
        }
        b/=2;
        n *= n%mod;
        n%=mod;
    }
    cur%=mod;
    return cur;
}

int main() {
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    long long a,b,c;
    cin>>a>>b>>c;
    if(a==b){
        cout<<binPowr(c,b)<<endl;
        return 0;
    }
    long long ans = 1;
    ans *= binPowr(c,b);
    ans%=mod;
    a-=b;
    int x = a/b;
    int rem = a%b;
    long long cur = (c-1);
    long long nxt = binPowr(c,b-1);
    cur *= nxt%mod;
    cur%=mod;
    long long ex = binPowr(cur, x);
    ex%=mod;
    ans*=ex;
    ans%=mod;
    if(rem>0){
        ans*=(c-1);
        ans%=mod;
        ans*= binPowr(c,rem-1);
        ans%=mod;
    }
    cout<<ans<<endl;
    return 0;
}