#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T> 
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define endl "\n"
#define fo(i, n) for (i = 0; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n; k++)
#define pb push_back
#define ll long long
#define mp make_pair
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, arr) for (auto it = arr.begin(); it != arr.end(); it++)
#define PI 3.1415926535897932384626
#define suprit ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0);
#define line cout << endl;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef map<ll, ll> ml;
typedef map<string, ll> msl;
typedef map<ll, string> mls;
typedef unordered_map<ll, ll> uml;
typedef unordered_map<string, ll> umsl;
typedef unordered_map<ll, string> umls;
typedef set<ll> sl;
typedef set<pair<ll, ll>> spl;
typedef ordered_set<ll> osl;
typedef ordered_set<pair<ll, ll>> ospl;

const ll mod = 1e9 + 7;

bool comp2(pair<ll, ll> &arr, pair<ll, ll> &b)
{
	if (arr.first == b.first)
		return arr.second < b.second;
	return arr.first < b.first;
};

template <typename T> void read(T i, T n, vector<T> &arr) { for(T j = i; j < n; j++) cin >> arr[j]; }
template <typename T> void read(vector<T> &arr) { for(auto &j : arr) cin>>j; }

#ifndef ONLINE_JUDGE

template <typename T, typename V> void print(set<pair<T, V>> &arr) { for(auto &it : arr) cout<<it.first<<" "<<it.second<<endl; line}
template <typename T, typename V> void print(pair<T, V>& pa) { cout<<pa.first<<" "<<pa.second<<endl; }
template <typename T> void print(T i, T last, vector<T> &arr) { for(T j = i; j < last; j++) cout<<arr[j]<<" "; line} 
template <typename T> void print(T i, vector<T> &arr) { for(T j = i; j < arr.size(); j++) cout<<arr[j]<<" "; line} 
template <typename T> void print(vector<T> &arr) { for(auto &i : arr) cout<<i<<" "; line}
template <typename T, typename V> void print(unordered_map<T, V>& arr) { for(auto &it : arr) cout<<it.first<<" "<<it.second<<endl; line}
template <typename T, typename V> void print(map<T, V>& arr) { for(auto &it : arr) cout<<it.first<<" "<<it.second<<endl;}
template <typename T> void print(unordered_set<T> &arr) { for(auto &it : arr) cout<<it<<" "; line }
template <typename T> void print(ordered_set<T> &arr) { for(auto &it : arr) cout<<it<<" "; line }
template <typename T> void print(set<T> &arr) { for(auto &it : arr) cout<<it<<" "; line }
template <typename T, typename... Args> void print(T t, Args... args) { cout << t << " "; print(args...); }
template <typename T> void print(T t) { cout<<t<<"\n"; }
#define debug(x) cout<<#x<<" "<<x<<endl;
#define debug2(x, y) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<endl;
#define debug3(x, y, z) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<" "<<#z<<" "<<z<<endl;
#define debug4(x, y, z, a) cout<<#x<<" "<<x<<" "<<#y<<" "<<y<<" "<<#z<<" "<<z<<" "<<#a<<" "<<a<<endl;

#else

#define print(x) 
#define debug(x)
#define debug2(x, y)
#define debug3(x, y, z)
#define debug4(x, y, z, a)

#endif

// vector<int> find_left_heights(int N, vector<int> &heights) {
// 	int sz = heights.size();

// 	stack<int> dynammic;
// 	dynammic.push(N-1);

// 	vector<int> final_left(N, -1);
// 	int temp = N - 2;
// 	while(temp >= 0) {
// 		int another = heights[temp];
// 		for(; dynammic.size() > 0 && another < heights[dynammic.top()]; dynammic.pop()) {
// 			final_left[dynammic.top()] = another;
// 		}
// 		dynammic.push(temp);
// 		--temp;
// 	}
// 	return final_left;
// }

// vector<int> findLeftHeights(int N, const vector<int>& heights) {
//     vector<int> temporary(N, -1);
//     stack<int> index_collect;

//     for (int i = N - 1; i >= 0; --i) {
//         while (!index_collect.empty() && heights[i] < heights[index_collect.top()]) {
//             temporary[index_collect.top()] = heights[i];
//             index_collect.pop();
//         }
//         index_collect.push(i);
//     }

//     return temporary;
// }

vector<int> findLeftHeights(int numBuildings, const vector<int>& buildingHeights) {
    vector<int> result(numBuildings, -1);
    stack<int> indices;
	indices.push(numBuildings-1);

    for (int se = numBuildings - 2; se >= 0; --se) {
        int var = buildingHeights[se];
		for(; indices.size() > 0 && var < buildingHeights[indices.top()]; indices.pop()) {
			result[indices.top()] = var;
		}
		indices.push(se);
    }
    return result;
}


// int dp[502][502];
// int recur(string& word1, string& word2, int ind1, int ind2)
// {
//     if (ind1 == 0)
//         return ind2;

//     if (ind2 == 0)
//         return ind1;

//     if (dp[ind1][ind2] != -1)
//         return dp[ind1][ind2];

//     if (word1[ind1 - 1] == word2[ind2 - 1]) {
//         return dp[ind1][ind2] = recur(word1, word2, ind1 - 1, ind2 - 1);
//     }

// 	return dp[ind1][ind2] = 1 + min(recur(word1, word2, ind1, ind2 - 1), min(recur(word1, word2, ind1 - 1, ind2), recur(word1, word2, ind1 - 1, ind2 - 1)));
// }

// int minDistance(string& word1, string& word2) {
// 	memset(dp, -1, sizeof(dp));
// 	return recur(word1, word2, word1.size(), word2.size());
// }

void distinctAlphabetsCount(const string &input) {
	map<char, int> keys;
	for(int ch = 0; ch < input.size(); ch++) {
		keys[input[ch]]++;
	}
	for(auto pa : keys) {
		cout << pa.first << ": " << pa.second << endl;
	}
}

int minDistance(const string& str, const string& ttr) {
	int s = str.size(), t = ttr.size();

	vector<vector<int>> memo(s+1, vector<int>(t+1, 0));
	for(int st = 0; st <= s; st++) memo[st][0] = st;
	for(int en = 0; en <= t; en++) memo[0][en] = en;

	for(int st = 1; st <= s; st++) {
		for(int en = 1; en <= t; en++) {
			if(str[st-1] == ttr[en-1]) memo[st][en] = memo[st-1][en-1];
			else memo[st][en] = 1 + min({memo[st-1][en-1], memo[st-1][en], memo[st][en-1]});
		}
	}
	return memo[s][t];
}


void printAnagrams(const vector<string>& strarray, const string& str) {
	// vector<string> temporary;
	// for(auto str : strings) temporary.push_back(str);

	// string copystr = specificString;

	// sort(copystr.begin(), copystr.end());
	// reverse(copystr.begin(), copystr.end());

	// int cnt = 0;
	// for(auto word : temporary) {
	// 	sort(word.begin(), word.end());
	// 	reverse(word.begin(), word.end());
	// 	if(word == copystr) cout << strings[cnt] << endl;
	// 	cnt++;
	// }

	auto countfreq = [&](const string &word) -> vector<int> {
		vector<int> ans(26, 0);
		for(auto c : word) {
			int x = c - 'a';
			ans[x]++;
		}
		return ans;
	};

	vector<int> original = countfreq(str);
	for(int i = 0; i < strarray.size(); i++) {
		vector<int> temp = countfreq(strarray[i]);
		if(temp == original) cout << strarray[i] << endl;
	}
}

void solve()
{
	int n;
	cin >> n;
	// vector<string> arr(n);
	// read(arr);
	// string temp;
	// cin >> temp;
	// printAnagrams(arr, temp);
	vi arr(n);
	read(arr);
	vi ans = findLeftHeights(n, arr);
	for(auto i : ans) cout << i << " ";
	cout << endl;
	// string s, t;
	// cin >> s >> t;
	// cout << minDistance(s, t) << endl;
	// string s;
	// cin >> s;
	// distinctAlphabetsCount(s);

}

int main()
{ 
	suprit;
	clock_t start = clock();

	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
	clock_t end = clock();
	
	#ifndef ONLINE_JUDGE
	double elapsed = double(end - start) / CLOCKS_PER_SEC;
	cout << setprecision(10) << elapsed << endl;
	#endif
	return 0;
}