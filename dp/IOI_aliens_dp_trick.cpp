#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e3 + 3;

double X[MAX], Y[MAX], dp[MAX][MAX], mid;
int p[MAX][MAX];
int N, A, B;

double solve(){
	for(int i=1; i<=N; ++i){
		for(int j=0; j<=A; ++j){
			double &d = dp[i][j];
			int &pick = p[i][j];
			d = dp[i - 1][j], pick = 0;

			if(j && d < dp[i - 1][j - 1] + X[i]){
				d = dp[i - 1][j - 1] + X[i];
				pick = 1;
			}

			if(d < dp[i - 1][j] + Y[i] - mid){
				d = dp[i - 1][j] + Y[i] - mid;
				pick = 2;
			}

			if(j && d < dp[i - 1][j - 1] + X[i] + Y[i] - (X[i] * Y[i]) - mid){
				d = dp[i - 1][j - 1] + X[i] + Y[i] - (X[i] * Y[i]) - mid;
				pick = 3;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> N >> A >> B;

	for(int i=1; i<=N; ++i) cin >> X[i];
	for(int i=1; i<=N; ++i) cin >> Y[i];

	double low = 0, high = 1;

	for(int i=0; i<50; ++i){
		mid = (low + high) / 2;
		solve();
		int pos = A, c = 0;
		for(int i=N; i>0; --i){
			if(p[i][pos] == 1) --pos;
			else if(p[i][pos] == 2) ++c;
			else if(p[i][pos] == 3) --pos, ++c;
		}
		if(c > B) low = mid;
		else high = mid;
	}

	mid = high;
	solve();

	printf("%0.5f\n", dp[N][A] + high * B);
		
	return 0;
}