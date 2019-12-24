void WalshHadamard(poly& P, bool invert) {
  for (int len = 1; 2 * len <= SZ(P); len <<= 1) {
    for (int i = 0; i < SZ(P); i += 2 * len) {
      FOR(j, 0, len) {
        auto u = P[i+j], v = P[i+len+j];
        P[i+j] = u + v, P[i+len+j] = u - v; // XOR
      }
  } } if (invert) for (auto& x: P) x /= SZ(P);
}
