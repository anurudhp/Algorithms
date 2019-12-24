void WalshHadamard(poly& P, bool invert) {
  for (len = 1; 2 * len <= SZ(P); len <<= 1) {
    for (i = 0; i < SZ(P); i += 2 * len) {
      FOR(j, 0, len) {
        auto u = P[i+j], v = P[i+len+j];
        P[i+j] = u + v, P[i+len+j] = u - v; // XOR [inv:same]
    //  P[i+j] = v, P[i+len+j] = u+v; AND [inv: v-u, u]
      } }
  } if (invert) for (auto& x: P) x /= SZ(P); }
