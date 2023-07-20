class DoubleHash {
public:
    string s;
    int n;
    vl prefixHash1, prefixHash2, inverseValue1, inverseValue2;
    ll p1, p2, modulo1, modulo2;

    DoubleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash1.resize(n+1, 0);
        prefixHash2.resize(n+1, 0);
        inverseValue1.resize(n+1, 0);
        inverseValue2.resize(n+1, 0);
        p1 = 31, p2 = 43, modulo1 = 1e9+7, modulo2 = 1e9+9;
        computePrefixHash(p1, modulo1, prefixHash1);
        computePrefixHash(p2, modulo2, prefixHash2);
        computeInverse(inverseValue1, p1, modulo1);
        computeInverse(inverseValue2, p2, modulo2);

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

    pair<ll, ll> substrHash(ll l, ll r) {
        pl ans;
        ans.first = partialHash(l, r, modulo1, p1, prefixHash1, inverseValue1);
        ans.second = partialHash(l, r, modulo2, p2, prefixHash2, inverseValue2);
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

    static pair<ll, ll> getHashString(string t) {
        pl ans;
        ans.first = getHash(t, 31, 1e9+7);
        ans.second = getHash(t, 43, 1e9+9);
        return ans;

    }
};
