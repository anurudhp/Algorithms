void dfs(int cur, int parent){
  disc[cur] = low[cur] = ++t;
  visited[cur] = true;
  for(auto it:v[cur]){
    if(visited[it] == 0){
      dfs(it, cur);
      low[cur] = min(low[cur], low[it]);
      if(MAP[{cur, it}] > 1 or MAP[{it, cur}] > 1)arr.push_back({cur, it})
      else if(low[it] > disc[cur]);//these are bridge edges
      else arr.push_back({cur, it});
    }
    else if(it != parent){
      low[cur] = min(low[cur], disc[it]);
      arr.push_back({cur, it});
    }
  }
}
int find(int x){ return dsu[x] = (x == dsu[x]) ? x : find(dsu[x]); }
void join(int x, int y){ dsu[find(y)] = find(x);}
// returns a node in tree, tree is graph 
int bridge_tree(){
  int root = -1;
  for(int i=1; i<=N; ++i){ 
    dsu[i] = i;
    if(visited[i]) continue; else dfs(i, 0);
  }
  for(auto it:arr) join(it.first, it.second);
  for(int i=1; i<=N; ++i){
    for(auto it:v[i]){
      if(find(i) != find(it)) tree[find(i)].push_back(find(it));
    } if(find(i) == i) root = i;
  } return root;
}
void dfsLCA(int cur, int parent){
  start[cur] = ++t; dp[cur][0] = parent;
  lev[cur] = lev[parent] + 1;
  for(auto it:tree[cur]){
    if(it != parent) dfsLCA(it, cur);
  } finish[cur] = ++t;
}
bool isAncestor(int u,int a){
    if(u==a) return true;
    if(start[u]<start[a] && finish[u]>finish[a]) return true;
    return false;
}
pair<int, int> getCommonPath(int u,int a,int v,int b){
    if(!isAncestor(v,a)) return make_pair(0,0);
    int x=LCA(a,b);
    if(lev[v]<lev[u]){if(isAncestor(u,x)) return make_pair(u,x);}
    else{ if(isAncestor(v,x)) return make_pair(v,x);}
    return make_pair(0,0);
}//length of path along a,b - length of common path of (a,b) and (c,d) 
int get_answer(int a, int b, int c, int d){
    int u=LCA(a,b),v=LCA(c,d); int ret=getdist(a,b,u);
    pair<int, int> X;
    X=getCommonPath(u,a,v,c); ret -= getdist(X.F,X.S,LCA(X.F,X.S));
    X=getCommonPath(u,a,v,d); ret -= getdist(X.F,X.S,LCA(X.F,X.S));
    X=getCommonPath(u,b,v,c); ret -= getdist(X.F,X.S,LCA(X.F,X.S));
    X=getCommonPath(u,b,v,d); ret -= getdist(X.F,X.S,LCA(X.F,X.S));
    return ret;
}