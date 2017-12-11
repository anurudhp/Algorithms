// https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/submissions/code/7084334

#include<bits/stdc++.h>
#define int unsigned long long int
using namespace std;

const int MAXN = 8e3 + 3;
const int MAXK = 810;
int A[MAXN], sum[MAXN], dp[MAXK][MAXN];
int N, K;

int get_sum(int x, int y){
    return sum[y] - sum[x-1];
}

void get(int lev, int start, int en, int left, int right){

	if(start > en) return;

	int mid = (start + en) >> 1;

	dp[lev][mid] = dp[lev - 1][max(left, lev - 1)] + (get_sum(max(left, lev - 1) + 1,mid) * (mid - max(left, lev - 1)));
	int op = max(left, lev - 1);

	for(int i=max(left, lev - 1) + 1; i <= min(right, mid - 1); ++i){
		if(dp[lev-1][i] + (get_sum(i+1,mid) * (mid - i)) < dp[lev][mid]){
			dp[lev][mid] = dp[lev-1][i] + get_sum(i+1,mid) * (mid - i);
			op = i;
		}
	}

	get(lev, start, mid - 1, left, op);
	get(lev, mid + 1, en, op, right);

}

signed main(){
	cin >> N >> K;
   
    K = min(K, N);
   
	for(int i=1; i<=N; ++i) cin >> A[i];
	
	for(int i=1; i<=N; ++i){
		sum[i] = sum[i-1] + A[i];
	}

	for(int i=1; i<=N; ++i) dp[1][i] = (i * get_sum(1,i));
	
	for(int i=2; i<=K; ++i){
		get(i, i, N, i-1, N-1);
	}

	cout << dp[K][N] << endl;

}