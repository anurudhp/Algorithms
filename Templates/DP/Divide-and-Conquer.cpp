// Applicable when dp[k][i] = min_{j < i}(dp[k - 1][j] + cost(j, i)) and opt_k(i) <= opt_k(i + 1)
// This holds when cost(a, d) - cost(a, c) >= cost(b, d) - cost(b, c) for a <= b <= c <= d
ll cost(int i, int j); // cost to go from i to j, 1-indexed. call solve(2) onwards after computing dp[1]
void solve(int i, int l = 1, int r = n, int optl = 1, int optr = n) {
	if (l > r || optl > optr) return;
	int mid = (l + r)/2;
	pair<ll, int> best = {inf, -1};
	for (int j = optl; j <= min(mid, optr); j++) {
    pair<ll,int> cand(dp[i - 1][j] + cost(j, mid), j);
    if (best.second == -1) best = cand;
    else best = min(best, cand);
	}
  dp[i][mid] = best.first;
	solve(i, l, mid - 1, optl, best.second);
	solve(i, mid + 1, r, best.second, optr);
}
