// using CD = complex<DBL>; // SLOW
// using Poly = vector<CD>; 
const DBL PI = acos(-1);
void fft(Poly& a, bool invert) {
  const int n = a.size(); // HAS TO BE POWER OF 2
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) {j ^= bit;}
    j ^= bit;
    if (i < j) {swap(a[i], a[j]);}
  }
  for (int len = 2; len <= n; len <<= 1) {
    DBL ang = 2 * PI / len * (invert ? -1 : 1);
    CD wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) { CD w(1);
      for (int j = 0; j < len / 2; j++) {
        CD u = a[i+j], v = a[i+j+len/2] * w;
        a[i+j] = u + v; a[i+j+len/2] = u - v;
        w = w * wlen;
      }
    }
  } if (invert) { for (CD& x: a) x = x / n; }
}
void multiply(const Poly& a, const Poly& b, Poly& prod);