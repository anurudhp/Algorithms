// http://codeforces.com/contest/165/submission/30179495

#include <bits/stdc++.h>

using namespace std;

const int LOG = 23;
const int MAX = (1 << 23);
const int MAXN = 1e6 + 6;

int N, X[MAX], A[MAXN], dp[MAX];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for(int i=1; i<=N; ++i){
		int x; cin >> x;
		X[x] = i;
		A[i] = x;
	}

	for(int i=0; i<LOG + 1; ++i){
		for(int j=0; j<MAX; ++j){
			dp[j] = X[j];
			if(j & (1LL << i)){
				if(dp[j] == 0) dp[j] = X[j ^ (1 << i)];
			}
		}
		for(int j=0; j<MAX; ++j) X[j] = dp[j];
	}

	for(int i=1; i<=N; ++i){
		int need = ((MAX - 1) ^ A[i]);
		int ans = X[need];
		cout << (ans ? A[ans] : -1) << ' ';
	}
} 

/*

S(mask, i) = S(mask, i - 1)
			 S(mask, i - 1) union S(mask ^ (1 << i), i - 1)  -> ith bit of mask is ON


All subsets of mask.

*/
