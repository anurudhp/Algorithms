// test if W weight is possible, c[i] is freq of i
// Push frequency of X to (X * 2)
int solve(int W){
  v.clear(); dp.reset();
  for(int i=1; i<=W; ++i){
    if(c[i] == 0) continue;
    if(c[i] & 1){ --c[i]; v.push_back(i); }
    else{
      --c[i]; --c[i];
      v.push_back(i); v.push_back(i);
    } int temp = (i << 1), inc = (c[i] >> 1);
    if(temp <= W) c[temp] += inc;
  }
  dp.set(0); for(auto it:v) dp |= (dp << it);
  return dp.test(W);
}