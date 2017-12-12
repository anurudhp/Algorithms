// can loop from optl to optr OR l to r
// CANNOT LOOP FROM L TO OPTL
void solve(int j, int l, int r, int optl, int optr){
  if(l > r) return;
  int mid = (l + r) >> 1; dp[j][mid] = INF;
  int low = optl, high = min(optr, mid), opt = optl;
  for(int k=low; k<=high; ++k){
    if(dp[j][mid] < get(j, k, mid)) dp[j][mid] = get(j, k, mid), opt = k;
  } solve(j, l, mid - 1, optl, opt); solve(j, mid + 1, r, opt, optr);
} (< for MAX) and (> for MIN)