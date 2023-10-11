class DoubleHash {
public:
    string s;
    int n;
    vl prefixHash1, prefixHash2, basepower1, basepower2;
    ll p1, p2, modulo1, modulo2;

    DoubleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash1.resize(n+1, 0);
        prefixHash2.resize(n+1, 0);
        basepower1.resize(n+1, 1);
        basepower2.resize(n+1, 1);
        p1 = 31, p2 = 43, modulo1 = 1e9+7, modulo2 = 1e9+9;
        computePrefixHash(p1, modulo1, prefixHash1, basepower1);
        computePrefixHash(p2, modulo2, prefixHash2, basepower2);
    }
 
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
        return ans;
    }
};