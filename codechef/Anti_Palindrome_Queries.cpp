#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t; 
	cin >> t;
	
	while (t--) {
	    int n, q;
	    cin >> n >> q;
	       
	    vector <vector <int>> store(n + 1, vector <int> (3, 0));
	    vector <int> hash(3, 0);
	    for (int i = 0; i < n; i++) {
	        int x;
	        cin >> x;
	        x--;
	        hash[x]++;
	        store[i + 1] = hash;
	    }
	    
	    for (int i = 0; i < q; i++) {
	        int l, r;
	        cin >> l >> r;
	        
	        vector <int> mainHash(3, -1);
	        for (int j = 0; j < 3; j++) {
	            mainHash[j] = store[r][j] - store[l - 1][j];
	        }
	        
	        sort(mainHash.begin(), mainHash.end());
	        
	        if (mainHash[2] == mainHash[0] + mainHash[1]) {
	            cout << "Yes" << endl;
	        } else {
	            cout << "No" << endl;
	        }
	    }
	}
}