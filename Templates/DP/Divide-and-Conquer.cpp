// Applicable when dp[k][i] =
// min_{j < i}(dp[k - 1][j] + cost(j, i)) and
// opt_k(i) <= opt_k(i + 1). This holds when
// cost(a, d) - cost(a, c) >= cost(b, d) - cost(b, c)
// call solve(i, 1, n, 1, n) for i = 2 to n after computing dp[1]
ll cost(int i, int j); // cost to go from i to j, 1-indexed.
void solve(int i, int l, int r, int optl, int optr) {
  if (l > r || optl > optr) return;
  int mid = (l + r)/2;
  pair<ll, int> best = {inf, -1};
  for (int j = optl; j <= min(mid, optr); j++) {
    pair<ll,int> cand(dp[i - 1][j] + cost(j, mid), j);
    if (best.second == -1) { best = cand; }
    else best = min(best, cand);
  }
  dp[i][mid] = best.first;
  solve(i, l, mid - 1, optl, best.second);
  solve(i, mid + 1, r, best.second, optr);
}
