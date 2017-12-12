// C[a][c]+C[b][d]<=C[a][d]+C[b][c] with a<=b<=c<=d, When A[i]<=A[i+1]
// A[i] is best position to calculate DP for i
// Use: set DP[1], arr.pb({N+1,1}), change <= to >= for Max       
for each i:
  insert(i);
  int pos=lower_bound(arr.begin(),arr.end(),make_pair(i,0)) - arr.begin();
  pos = arr[pos].second; dp[i] = cost(pos, i);
void insert(int idx){
  while(true){
    if(arr.size() > 1){
      auto X = arr[arr.size() - 1], Y = arr[arr.size() - 2];
      int L = Y.second, H = N + 1, LL = idx, HH = N + 1;
      while(L < H){
        int mid = (L + H) >> 1;
        if(cost(Y.second, mid) <= cost(X.second, mid)) L = mid + 1;
        else H = mid;
      }
      while(LL < HH){
        int mid = (LL + HH) >> 1;
        if(cost(X.second, mid) <= cost(idx, mid)) LL = mid + 1;
        else HH = mid;
      }
      if(L > LL){
        arr.pop_back(); continue;
      } else break;
    } else break;
  } auto X = arr[arr.size() - 1]; int L = idx, H = N + 1;
  while(L < H){
    int mid = (L + H) >> 1;
    if(cost(X.second, mid) <= cost(idx, mid)) L = mid + 1;
    else H = mid;
  }
  if(L > N) return;
  else{ arr[arr.size() - 1].first = L - 1; arr.push_back({N + 1, idx});}
}