// when opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j]
for(int i=1; i<=K; ++i) opt[N + 1][i] = N;
for(int j=1; j<=K; ++j){
  for(int i=N; i>0; --i){ //reverse to get opt[i + 1][j]
    dp[i][j] = 0; int low = max(1LL, opt[i][j - 1]), high = opt[i + 1][j];
    for(int k=low; k<=high; ++k)
      if(dp[k - 1][j - 1] + pre[k][i] > dp[i][j])
        dp[i][j] = dp[k - 1][j - 1] + pre[k][i], opt[i][j] = k;
  }
} // complexity is K * N, second N loop is amortized
