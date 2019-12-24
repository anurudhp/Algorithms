// Expected complexity - O(n^1/4 log(n))
LL llmult(LL a, LL b, LL mod) {return ((__int128)a * b) % mod;}
LL f(LL x, LL c, LL mod) {return (llmult(x, x, mod) + c) % mod;}
LL rho(LL n, LL x0=2, LL c=1) { LL x = x0, y = x0, g = 1;
  while (g == 1) {
    x = f(x, c, n); y = f(y, c, n);
    y = f(y, c, n); g = __gcd(llabs(x - y), n);
  } return g;
}// if g = n => repeat with different x0/c, else g is a factor
