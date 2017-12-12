// v[node][i]: count of index <= i which went into left subtree
void build(int low, int high, int node){
  for(auto it:s[node >> 1])
    if(it >= low and it <= high) s[node].push_back(it);
  if(low == high) return; int mid = (low + high) >> 1;
  if(s[node].size()){
    if(s[node][0] > mid) v[node].push_back(0);
    else v[node].push_back(1);
    for(int i=1; i<s[node].size(); ++i){
      if(s[node][i] > mid) v[node].push_back(v[node].back());
      else v[node].push_back(v[node].back() + 1);     
    }
  } else return;
  build(low, mid, node << 1); build(mid + 1, high, 1 | node << 1);
}
int query(int low, int high, int node, int l, int r, int rank){
  if(low == high) return low;
  int mid = (low + high) >> 1, new_l = 0, new_r = 0, to_l = 0, to_r = 0;
  to_l = v[node][r];
  if(l) to_l = to_l - v[node][l - 1];
  to_r = r - l + 1 - to_l;
  if(to_l >= rank){ if(l) new_l = v[node][l - 1];
    new_r = new_l + to_l - 1;
    return query(low, mid, node << 1, new_l, new_r, rank);
  } else{ if(l) new_l = l - v[node][l - 1];
    new_r = new_l + to_r - 1;
    return query(mid + 1, high, 1 | node << 1, new_l, new_r, rank - to_l);
  }
} //MAIN
int mid = (1 + MAX) >> 1; for(int i=1; i<=N; ++i) s[1].push_back(A[i]);
if(s[1][0] > mid) v[1].push_back(0);
else v[1].push_back(1);
for(int i=1; i<N; ++i){
  if(s[1][i] > mid) v[1].push_back(v[1].back());
  else v[1].push_back(v[1].back() + 1);
} build(1, mid, 2); build(mid + 1, MAX, 3);
  

