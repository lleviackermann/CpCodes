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

class SingleHash {
public:
    string s;
    int n;
    vl prefixHash;
    ll p, modulo;
    vl basepower;
    // vl inverseValue;
 
    SingleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash.resize(n+1, 0);
        basepower.resize(n+1, 1);
        // inverseValue.resize(n+1,0);
        p = 31, modulo = 1e9+7;
        computePrefixHash();
        // computeInverse();
    }
    
    // void computeInverse() {
    //     ll temp = binpow(p, n-1, modulo);
    //     inverseValue[n-1] = binpow(temp, modulo-2, modulo);
    //     for(ll i = n-2; i >=0; i--) inverseValue[i] = (inverseValue[i+1] * (p)) % modulo;
    // }

    void computePrefixHash() {
        ll power_p = 1;
        for(int i = 1; i <= n; i++) basepower[i] = basepower[i-1] * p % modulo;
        // print(basepower);
        for(ll i = 0; i < n; i++) {
            ll x = s[i] - 'a' + 1;
            prefixHash[i+1] = (prefixHash[i] + basepower[i] * x) % modulo;
        }
    }

    ll substrHash(ll l, ll r) {
        ll ans = (prefixHash[r+1] - prefixHash[l] + modulo) * basepower[n-l] % modulo;
        // ll ans = (prefixHash[r+1] - prefixHash[l] + modulo) * inverseValue[l] % modulo;
        
        return ans;
    }
};
