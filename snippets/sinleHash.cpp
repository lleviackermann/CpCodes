class SingleHash {
public:
    string s;
    int n;
    vl prefixHash1;
    ll p1, modulo1;
    vl basepower;
 
    SingleHash(string &temp) {
        s = temp;
        n = temp.length();
        prefixHash1.resize(n+1, 0);
        basepower.resize(n+1, 1);
        p1 = 31, modulo1 = 1e9+7;
        computePrefixHash(p1, modulo1, prefixHash1);
    }
 
    void computePrefixHash(ll p, ll modulo, vl &prefix) {
        ll power_p = 1;
        for(int i = 1; i <= n; i++) basepower[i] = basepower[i-1] * p % modulo;
        // print(basepower);
        for(ll i = 0; i < n; i++) {
            ll x = s[i] - 'a' + 1;
            prefix[i+1] = (prefix[i] + basepower[i] * x) % modulo;
        }
    }

    ll substrHash(ll l, ll r) {
        ll ans = (prefixHash1[r+1] - prefixHash1[l] + modulo1) * basepower[n-l] % modulo1;
        return ans;
    }
};