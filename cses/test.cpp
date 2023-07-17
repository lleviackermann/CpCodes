#include<iostream>
#include<map>
#include<vector>
#include<climits>
#include<queue>
#include<cmath>
#include<stack>
#include<string>
#include<algorithm>
#define pb push_back
#define N (lli)(1e6)
#define lli long long int
#define mod (lli)(1e9+7)
#define INF (11)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define pb push_back
using namespace std;
 
void buildTree1(vector<lli>&arr,vector<lli>&tree,lli ns,lli ne,lli index)
{
    if(ns==ne)
    {
        tree[index] = arr[ns]+ns;
        return;
    }
    
    lli mid = (ns+ne)/2;
    buildTree1(arr,tree,ns,mid,2*index);
    buildTree1(arr,tree,mid+1,ne,2*index+1);
    tree[index] = min(tree[2*index],tree[2*index+1]);
}
 
void buildTree2(vector<lli>&arr,vector<lli>&tree,lli ns,lli ne,lli index)
{
    if(ns==ne)
    {
        tree[index] = arr[ns] - ns;
        return;
    }
    
    lli mid = (ns+ne)/2;
    buildTree2(arr,tree,ns,mid,2*index);
    buildTree2(arr,tree,mid+1,ne,2*index+1);
    tree[index] = min(tree[2*index],tree[2*index+1]);
}
 
void update1(vector<lli>&arr,vector<lli>&tree,lli ns,lli ne,lli toUpd,lli updVal,lli index)
{
    // no overlap
    if(ne<toUpd or  ns>toUpd) return;
    
    // complete overlap
    if(ns==ne)
    {
        tree[index] = updVal + ns;
        return;
    }
    
    // partial overlap
    lli mid = (ns+ne)/2;
    update1(arr, tree, ns, mid, toUpd, updVal, 2*index);
    update1(arr, tree, mid+1, ne, toUpd, updVal, 2*index+1);
    tree[index] = min(tree[2*index],tree[2*index+1]);
}
 
void update2(vector<lli>&arr,vector<lli>&tree,lli ns,lli ne,lli toUpd,lli updVal,lli index)
{
    // no overlap
    if(ne<toUpd or  ns>toUpd) return;
    
    // complete overlap
    if(ns==ne)
    {
        tree[index] = updVal - ns;
        return;
    }
    
    // partial overlap
    lli mid = (ns+ne)/2;
    update2(arr, tree, ns, mid, toUpd, updVal, 2*index);
    update2(arr, tree, mid+1, ne, toUpd, updVal, 2*index+1);
    tree[index] = min(tree[2*index],tree[2*index+1]);
}
 
 
lli query(vector<lli>&arr,vector<lli>&tree,lli ns,lli ne,lli l ,lli r,lli index)
{
    // no overlap
    if(r<ns or l>ne) return LLONG_MAX;
    
    
    // complete overlap
    if(l<=ns and ne<=r) return tree[index];
    
    // partial overlap
    lli mid = (ns+ne)/2;
    lli left = query(arr, tree, ns, mid, l, r, 2*index);
    lli right = query(arr,tree,mid+1,ne,l,r,2*index+1);
    return min(left,right);
}
 
 
int main()
{
    lli n,q;
    cin>>n>>q;
    vector<lli>arr(n);
    for(lli i=0;i<n;i++) cin>>arr[i];
    vector<lli>tree1(4*n+1);
    vector<lli>tree2(4*n+1);
    cout<<arr[56]<<endl;
    buildTree1(arr, tree1, 0, n-1, 1);
    buildTree2(arr, tree2, 0, n-1, 1);
    
    lli t,a,b;
    while(q--)
    {
        cin>>t;
        if(t==2)
        {
            cin>>a;
            lli left = query(arr, tree2, 0, n-1, 0, a-1, 1);
            lli right = query(arr,tree1,0,n-1,a-1,n-1,1);
            cout<<min(left+(a-1),right-(a-1))<<endl;
            
        }
        else
        {
            cin>>a>>b;
            update1(arr, tree1, 0, n-1, a-1, b,1);
            update2(arr,tree2,0,n-1,a-1,b,1);
        }
    }
    
}