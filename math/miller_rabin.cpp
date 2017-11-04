// For n < 2^64; p = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37.

namespace MillerRabin {
  typedef long long LL;
  long long modpow(LL a, LL n, LL mod) {
    LL res = 1;
    for (; n > 0; n >>= 1) {
      if (n & 1) res = (res * a) % mod;
      a = (a * a) % mod;
    }
    return res;
  }

  // false => composite; true => maybe prime
  bool witness(LL N, int a, LL d) {
    LL x = modpow(a, d, N);
    if (x == 1 || x == N - 1) return true;
    for (; d != N - 1; d <<= 1) {
      x = (x * x) % N;
      if (x == 1) return false;
      if (x == N - 1) return true;
    }
    return false;
  }

  int wit[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  bool is_prime(LL N) {
    if (N <= 1) return false;
    LL d;
    for (d = N - 1; d % 2 == 0; d >>= 1);
    for (int p: wit) {
      if (p > N - 2) break;
      // is_prime = is_prime && witness(...)
      if (!witness(N, p, d)) return false;
    }
    return true;
  }
}
