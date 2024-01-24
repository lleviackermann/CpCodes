#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define yes cout<<"YES"<<endl
#define no cout<<"NO"<<endl
using vct = vector<int>;
using pr = pair<int, int>;
#define mod 1e9+7
ll Stoi(string s)
{
    int n=s.size();
    ll b=1,ans=0;
    for(int i=n-1;i>=0;i--)
    {
        ans=ans+(s[i]-'0')*b;
        b=b*10;
    }
    return ans;
}
bool isPalindrome(ll num) {
    ll original = num;
    ll reverse = 0;
    while (num > 0) {
        int digit = num % 10;
        reverse = reverse * 10 + digit;
        num /= 10;
    }
    return original == reverse;
}

// Permutations and Combinations Start
long long int factNum(long long int n)
{
    long long int facti = 1;
    for (long long int i = 1; i <= n; i++)
        facti *= i;
    return facti;
}
void factArray(long long int a[], long long int n)
{
    a[0] = 1;
    for (long long int i = 1; i <= n; i++)
        a[i] *= a[i - 1];
}
long long int combination(long long int n, long long int r)
{
    long long int num = 1, den = 1;
    if (r > n / 2)
        r = n - r;
    n++;
    for (long long int i = 1; i <= r; i++)
    {
        num *= n - i;
        den *= i;
    }
    return num / den;
}
long long int permutation(long long int n, long long r)
{
    long long int num = 1;
    for (long long int i = n - r + 1; i <= n; i++)
        num *= i;
    return num;
}
// Permutations and Combinatios End
// Map
void unMap(unordered_map<int, long long int> &mp,vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
        mp[v[i]]++;
}
// map end
// Prime Number Start
bool isPrime(long long int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    long long int k = (int)sqrt(n) + 1;
    for (long long int i = 5; i < k; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}
// Prime Number End
// GCD Start
long long int gcd(long long int a, long long int b)
{
    long long int temp;
    while (b)
    {
        temp = a;
        a = b;
        b = temp % a;
    }
    return a;
}
// GCD End
// Modular Arithmetic Start
long long int PowMod1(long long int a, long long int b)
{
    long long int ans = 1;
    a %= 1000000007;
    while (b)
    {
        if (b % 2)
            ans = ans * a % 1000000007;
        a = a * a % 1000000007;
        b >>= 1;
    }
    return ans;
}
long long int PowMod2(long long int a, long long int b)
{
    long long int ans = 1;
    a %= 998244353;
    while (b)
    {
        if (b % 2)
            ans = ans * a % 998244353;
        a = a * a % 998244353;
        b >>= 1;
    }
    return ans;
}
long long int FMod1(long long int n)
{
    long long int ans = 1;
    for (long long int i = 1; i <= n; i++)
        ans = ans * i % 1000000007;
    return ans;
}
long long int FMod2(long long int n)
{
    long long int ans = 1;
    for (long long int i = 1; i <= n; i++)
        ans = ans * i % 998244353;
    return ans;
}
long long int PMod1(long long int n, long long int r)
{
    long long int ans = 1;
    for (long long int i = n - r + 1; i <= n; i++)
        ans = ans * i % 1000000007;
    return ans;
}
long long int PMod2(long long int n, long long int r)
{
    long long int ans = 1;
    for (long long int i = n - r + 1; i <= n; i++)
        ans = ans * i % 998244353;
    return ans;
}
// Modular Arithmetic End


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);	
    int testcase;
    cin>>testcase;
    for(int ss=0;ss<testcase;ss++)
    {
       ll n;
       cin>>n;
  
       int k=(int)sqrtl(n);
    //   cout<<sqrtl(27)<<endl;
    
       if((n-k*k)&1)
       {
           k--;
       }
       cout<<(k+1)/2<<endl;
       



    }
	return 0;

}
