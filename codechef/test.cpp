#include<bits/stdc++.h>
using namespace std;
#define ll long long

int mod = 1e9+7;

ll powr(int a,int b){
    ll ans = 1;
    while(b>0){
        if(b&1){
            ans*=a;
            ans%=mod;
        }
        a*=a;
        b/=2;
    }
    return ans;
}

int raisingPower(vector<int>& arr){
    ll maxi = 0;
    int ans = -1;
    int n=arr.size();
    for(int i=0;i<n-1;i++){
        ll cur = powr(arr[i],arr[i+1]);
        if(cur>maxi){
            ans=i+1;
            maxi=cur;
        }
    }
    return ans;
}
int main(){
    int n;
    cin>>n;
    vector<int> boxes(n);
    for(int i=0;i<n;i++) cin>>boxes[i];
    cout<<raisingPower(boxes)<<endl;
    return 0;
}