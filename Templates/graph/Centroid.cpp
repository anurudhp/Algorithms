void dfs_size(int cur, int p){ size[cur] = 1; ++tot;
  for(auto it:v[cur])
    if(it != p && done[it] == 0) dfs_size(it, cur), size[cur] += size[it];
}
int find(int cur, int par){
  for(auto it:v[cur]){
    if(done[it] || it == par) continue;
    if(size[it] > (tot >> 1)) return find(it, cur);
  } return cur; }
void decompose(int cur){ tot = 0; dfs_size(cur, 0); cur = find(cur, 0);
  // do dfs on children
  done[cur] = 1;  for(auto it:v[cur]) if(!done[it]) decompose(it);
}