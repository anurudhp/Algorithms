VI mobius(int N) { VI mu(N + 1, 1);
  vector<bool> ispr(N + 1, 1);
  for(int i=2; i<=N; ++i) {
    if(!ispr[i]) continue;
    for(int j=i; j<=N; j+=i) { ispr[j] = 0; mu[j] *= -1; }
    if (i*1ll*i > N) continue;
    for(int j = i*i, ii = i*i; j<=N; j+=ii) mu[j] = 0;
  }
  return mu;
}
VI DirichletConvolution(const VI &A, const VI &B, int N) {
  VI ans(N+1,0); // H(n) = sum{x,y:x*y=n} A[x]*B[y] for [1,N]
  FOR(i,1,N+1) for(int j=i;j<=N;j+=i) ans[j] += A[i]*B[j/i];
  return ans;
}
