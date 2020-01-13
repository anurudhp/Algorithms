const int mod = 998244353, root_pw = 1 << 20;
const int root = 973800541, root_1 = 595374802;
void NTT(VI& a, bool invert) { const int n = SZ(a);
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) { j ^= bit; }
    j ^= bit;
    if (i < j) { swap(a[i], a[j]); }
  }
  for (int len = 2; len <= n; len <<= 1) {
    int wlen = invert ? root_1 : root;
    for (int i = len; i < root_pw; i <<= 1) {
      wlen = (wlen*1ll*wlen) % mod;
    } for (int i = 0; i < n; i += len) { int w = 1;
      for (int j = 0; j < len / 2; j++) {
        int u = a[i+j], v = (a[i+j+len/2]*1ll*w) % mod;
        a[i+j] = u + v < mod ? u + v : u + v - mod;
        a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
        w = (w*1ll*wlen) % mod;
      }
    }
  }
  if (invert) { int n_1 = modpow(n, mod-2);
    for (int& x: a) x = (x*1ll*n_1) % mod;
  }
}
