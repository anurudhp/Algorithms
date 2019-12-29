// 1-indexed sequences
// given: B[1...m] (=> padding `B[i] = 0` for `i > m`)
// compute: A[i] = \sum{j = 1...i-1} A[j] * B[i-j]
void online(const Poly& B, CD a1, int n, Poly& A) {
  const int m = SZ(B) - 1;
  A.assign(n + 1, 0); A[1] = a1;
  auto bst = B.begin(), ast = A.begin();
  FOR(i, 1, n) { A[i + 1] += A[i] * B[1];
    if (i + 2 <= n) A[i + 2] += A[i] * B[2];
    for (int pw = 2; i % pw == 0 && pw + 1 <= m; pw <<= 1) {
      Poly blockA(ast + i - pw, ast + i);
      Poly blockB(bst + pw + 1, bst + min(pw * 2, m) + 1);
      Poly prod; multiply(blockA, blockB, prod);
      FOR(j, 0, SZ(prod)) {
        if (i + 1 + j <= n) A[i + 1 + j] += prod[j];
      }
    }
  }
}