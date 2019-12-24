VI Mobius(int N) { // return mu(n) for n in [1,N]
  VI mu(N + 1, 0); mu[1] = 2;
  FOR(i, 2, N + 1) if (mu[i] == 0) {
    mu[i] = 1; LL ii = i*i;
    if (ii <= N) {
      for (int j = ii; j <= N; j += ii) {
        mu[j] = -1;
      }
    }
    for (int j = i << 1; j <= N; j += i) {
      if (mu[j] != -1) ++mu[j];
    }
  }
  FOR(i, 1, N + 1) {
    mu[i] = (mu[i] == -1) ? 0 : (mu[i] & 1) ? -1 : 1;
  }
  return mu;
} VI DirichletConvolution(const VI &A, const VI &B, int N) {
  VI ans(N+1,0); // H(n) = sum{x,y:x*y=n} A[x]*B[y] for [1,N]
  FOR(i,1,N+1) for(int j=i;j<=N;j+=i) ans[j] += A[i]*B[j/i];
  return ans;
}
