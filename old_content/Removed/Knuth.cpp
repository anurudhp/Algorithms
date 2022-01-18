// If dp[i][j] = min_{i<k<j}{dp[i][k] + dp[k][j] + c[i][j]} and
// opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j], just iterate in this
// range to find in O(NK). This holds also if c satisfies
// c[a][d] - c[a][c] >= c[b][d] - c[b][c] and c[b][c] <= c[a][d].
