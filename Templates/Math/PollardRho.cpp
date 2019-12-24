//Expected complexity - O(n^1/4 log(n))
long long mult(long long a, long long b, long long mod) {return (__int128)a * b % mod;}
long long f(long long x, long long c, long long mod) {return (mult(x, x, mod) + c) % mod;}
long long rho(long long n, long long x0=2, long long c=1) {
  long long x = x0, y = x0, g = 1;
  while (g == 1) {
    x = f(x, c, n); y = f(y, c, n);
    y = f(y, c, n); g = gcd(abs(x - y), n);
}return g;}//if g = n => repeat with different x0/c, else g is the factor
