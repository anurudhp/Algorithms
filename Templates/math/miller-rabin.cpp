// false => composite; true => maybe prime
bool witness(LL N, int a, LL d) {
  LL x = modpow(a, d, N);
  if (x == 1 || x == N - 1) return true;
  for (; d != N - 1; d <<= 1) {
    x = (x * x) % N;
    if (x == 1) return false;
    if (x == N - 1) return true;
  } return false;
} int wit[] = {2,3,5,7,11,13,17,19,23,29,31,37}; //n<2^64