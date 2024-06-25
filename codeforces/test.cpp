#include <bits/stdc++.h>
#define ll long long

using namespace std;

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}



int bounty(int input1) {
    const ll mod = 1e4 + 7;
    long long ans = 9;
    long long sum = 0;
    vector<ll> factorial(input1+1, 1);
    vector<ll> inverse_fact(input1+1, 1);
    for(ll i = 1; i <= input1; i++) factorial[i] = factorial[i-1] * i % mod;
    inverse_fact[input1] = binpow(factorial[input1], mod-2, mod);
    for(ll i = input1-1; i >= 0; i--) inverse_fact[i] = inverse_fact[i+1] * (i+1) % mod;
    for(ll i = 2; i <= input1-1; i++) {
        ll temp = factorial[input1-1] * inverse_fact[i] % mod;
        temp = temp * inverse_fact[input1-1-i] % mod;
        temp = temp * binpow(9, input1-1-i, mod) % mod;
        sum = (sum + temp) % mod;
    }
    ans = ans * sum % mod;
    return (int) ans;
}

int main() {
    int n;
    cin >> n;
    cout << bounty(n);
}