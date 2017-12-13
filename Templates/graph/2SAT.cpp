// 2-SAT: compute SCCs. if x & !x are in same SCC, then not possible
// else assign values (pref. false) in toposort order
// impl. trick (node nos.): x_i = 2*i, x_i' = 2*i+1
[u => v: edge u --> v]
[u or v: ~u => v, ~v => u]
[u xor v: (u or v) and (~u or ~v)];
[u eq v: (u or ~v) and (~u or v)]
[u: u or u];
vector<int> revadj[NODES], adj[NODES], top_sort, working;
int marked[NODES], comp[NODES], c = 0;
stack<int> finishing;
void dfs1(int v) {
  marked[v] = true;
  for (auto i: adj[v]){
    if (marked[i] == 0) dfs1(i);
  }
  top_sort.push_back(v);
  finishing.push(v);
}
void dfs2(int v) {
  marked[v] = true;
  for (auto i: revadj[v]){
    if (marked[i] == 0) dfs2(i);
  }
  comp[v] = c;
}// in main
for(int i=2; i<=(2*m+1); ++i){
  if(!marked[i]) dfs1(i);
}
memset(marked, 0, sizeof marked);
while(finishing.size()) {
  if(!marked[finishing.top()]){
    c++;
    dfs2(finishing.top());
  } finishing.pop();
}
for(int i=2; i<=(2*m+1); ++i) {
  if(comp[i] == comp[i^1]) {
    printf("No\n");
    return 0;
  }
}
memset(marked, 0, sizeof marked);
for(auto &z: top_sort){
  if(marked[z>>1] == 0) {
    marked[z>>1] = 1;
    if((z & 1) == 0) working.push_back(z>>1);
  }
}
printf("Yes\n%d\n", working.size());
for(auto &z: working) {
  printf("%d ", z);
}