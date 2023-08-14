class SingleHash {
public:
    string s;
    int n;
    vl prefixHash1, inverseValue1;
    ll p1, modulo1;
 
    SingleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash1.resize(n+1, 0);
        inverseValue1.resize(n+1, 0);
        p1 = 31, modulo1 = 1e9+7;
        computePrefixHash(p1, modulo1, prefixHash1);
        computeInverse(inverseValue1, p1, modulo1);
 
    }
 
    void computeInverse(vl &inverse, ll p, ll modulo) {
        ll temp = binpow(p, n-1, modulo);
        inverse[n-1] = binpow(temp, modulo-2, modulo);
        for(ll i = n-2; i >=0; i--) inverse[i] = (inverse[i+1] * (p)) % modulo;
    }
 
    void computePrefixHash(ll p, ll modulo, vl &prefix) {
        ll power_p = 1;
        for(ll i = 0; i < n; i++) {
            ll x = s[i] - 'a' + 1;
            prefix[i+1] = (prefix[i] + power_p * x) % modulo;
            prefix[i+1] = (prefix[i+1] + modulo) % modulo; 
            power_p = (power_p * p) % modulo;
 
        }
    }
 
    ll partialHash(ll l, ll r, ll modulo, ll p, vl &prefix, vl &inverse) {
        ll temp = (((prefix[r] - prefix[l-1]) % modulo) + modulo) % modulo;
        temp = (temp * inverse[l-1]) % modulo;
        return temp;
    }
 
    ll substrHash(ll l, ll r) {
        ll ans;
        ans = partialHash(l, r, modulo1, p1, prefixHash1, inverseValue1);
        return ans;
    }
 
    static ll getHash(string &t, ll p, ll modulo) {
        int len = t.length();
        ll ans = 0;
        ll power_p = 1;
        for(ll i = 0; i < len; i++) {
            ll x = t[i] - 'a' + 1;
            ans += x * power_p;
            power_p = (power_p * p) % modulo;
            ans %= modulo;
        }
        return ans;
    }
 
    static ll getHashString(string t) {
        ll ans;
        ans = getHash(t, 31, 1e9+7);
        return ans;
 
    }
};