pair<T, T> extended_gcd(T a, T b) { // ax + by = gcd(a, b)
  T x0 = 1, x1 = 0, y0 = 0, y1 = 1, r0 = a, r1 = b;
  while (r1 != 0) { T q = r0 / r1, temp;
    temp = r1, r1 = r0 - q * r1, r0 = temp;
    temp = x1, x1 = x0 - q * x1, x0 = temp;
    temp = y1, y1 = y0 - q * y1, y0 = temp;
  } return {x0, y0}; // gcd(a, b) = r0
}
