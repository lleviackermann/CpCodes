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

class DoubleHash {
public:
    string s;
    int n;
    vl prefixHash1, prefixHash2, basepower1, basepower2;
    ll p1, p2, modulo1, modulo2;
    // vl inverseValue1, inverseValue2;
    DoubleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash1.resize(n+1, 0);
        prefixHash2.resize(n+1, 0);
        basepower1.resize(n+1, 1);
        basepower2.resize(n+1, 1);
        // inverseValue1.resize(n+1, 0);
        // inverseValue2.resize(n+1, 0);
        p1 = 31, p2 = 43, modulo1 = 1e9+7, modulo2 = 1e9+9;
        computePrefixHash(p1, modulo1, prefixHash1, basepower1);
        computePrefixHash(p2, modulo2, prefixHash2, basepower2);
        // computeInverse(inverseValue1, p1, modulo1);
        // computeInverse(inverseValue2, p2, modulo2);
    }
 
    // void computeInverse(vl &inverse, ll p, ll modulo) {
    //     ll temp = binpow(p, n-1, modulo);
    //     inverse[n-1] = binpow(temp, modulo-2, modulo);
    //     for(ll i = n-2; i >=0; i--) inverse[i] = (inverse[i+1] * (p)) % modulo;
    // }

    void computePrefixHash(ll p, ll modulo, vl &prefix, vl &basepower) {
        for(int i = 1; i <= n; i++) basepower[i] = basepower[i-1] * p % modulo;
        for(ll i = 0; i < n; i++) {
            ll x = s[i] - 'a' + 1;
            prefix[i+1] = (prefix[i] + basepower[i] * x) % modulo;
        }
    }

    pl substrHash(ll l, ll r) {
        //indexing should be 0 based
        pl ans;
        ans.first = (prefixHash1[r+1] - prefixHash1[l] + modulo1) * basepower1[n-l] % modulo1;
        ans.second = (prefixHash2[r+1] - prefixHash2[l] + modulo2) * basepower2[n-l] % modulo2;
        // ans.first = (prefixHash1[r+1] - prefixHash1[l] + modulo1) * inverseValue1[l] % modulo1;
        // ans.second = (prefixHash2[r+1] - prefixHash2[l] + modulo2) * inverseValue2[l] % modulo2;
        return ans;
    }
};
