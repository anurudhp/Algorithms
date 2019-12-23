// Solves systems of linear modular equations.
// Build a matrix of coefficients and call run(mat, R, C, mod).
// If no solution,returns -1, else returns # of free variables.
// If i-th variable free,row[i]=-1,else it’s value = ans[i].
// Time complexity: O(R * C^2) - MAXC is the number of columns
// * uses: modpow(a, n, m): a^n % m
typedef long long LL;
const int MAXC = 1001;int row[MAXC];LL ans[MAXC];
LL inv(LL x, LL mod) { return modpow(x, mod-2, mod); }

int run(LL mat[][MAXC], int R, int C, LL mod) {
  for (int i=0;i<C;i++) row[i] = -1;
  int r = 0;
  for (int c=0;c<(C);++c) {
    int k = r;
    while (k < R && mat[k][c] == 0) ++k;
    if(k==R)continue;
    for (int j = (0); j < (C+1); ++j) swap(mat[r][j],mat[k][j]);
    LL div=inv(mat[r][c],mod);
    for (int i = (0); i < (R); ++i) if(i!=r){
      LL w = mat[i][c]*(mod-div)%mod;
      for (int j = (0); j < (C+1); ++j) mat[i][j] = (mat[i][j] + mat[r][j] * w) % mod;
    }
    row[c] = r++;
  }
  for (int i=0;i<C;++i) {
    int r = row[i];
    ans[i] = r==-1 ? 0 : (mat[r][C] * inv(mat[r][i],mod)) % mod;
  }
  for (int i=r;i<R;++i) if(mat[i][C]) return -1;
  return C - r;
}
