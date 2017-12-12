 // Given a fixed array A of 2^N integers, we need to calculate ∀ x function F(x) = Sum of all A[i] such that x&i = i, i.e., i is a subset of x.
// if ith bit if off: S(mask, i) = S(mask, i - 1)
// S(mask, i - 1) union S(mask ^ (1 << i), i - 1)
for(int i = 0; i<(1<<N); ++i) F[i] = A[i];
for(int i = 0;i < N; ++i){ 
  for(int mask = 0; mask < (1<<N); ++mask){
  if(mask & (1<<i))
    F[mask] += F[mask^(1<<i)];
  }
}