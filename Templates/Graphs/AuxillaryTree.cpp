namespace AuxillaryTree { const int N = 2e5, LOGN = 20;
  // clear auxNodes, mark, aux; 
  // auxNodes contains nodes of current aux tree 
  vector <PII> g[N], aux[N];  // aux is adjList of auxtree. 
  VI auxNodes;  // dists is distance from 1 to any node. 
  int P[LOGN][N], depth[N], timer, st[N], en[N], n; 
  bool rem[N], mark[N]; //mark contains marked nodes
  LL dists[N]; 
  void dfs0 (int v, int par = 1) { 
    P[0][v] = par; st[v] = timer++; //adj list is pair
    for(auto x: g[v]) { 
      int u = x.ST; LL w = x.ND;
      if(u == par) continue;
      depth[u] = depth[v] + 1, dists[u] = dists[v] + w;
      dfs0(u, v);
    } en[v] = timer;//*******set mark = false after all processing
  } 
  void pre() { 
    timer = 1; dfs0(1);
    FOR(i, 1, LOGN) FOR(j, 1, n + 1) P[i][j] = P[i - 1][P[i - 1][j]];
  }
  bool ancestor(int par, int u) { return ((st[par] < st[u]) && (en[par] >= en[u])); }
  bool cmp(int x, int y) { return st[x] < st[y]; }
  int LCA(int x, int y) { 
    if(depth[x] < depth[y]) swap(x, y);
    for(int i = LOGN - 1; i >= 0; i--) {
      if(depth[P[i][x]] >= depth[y]) x = P[i][x];
    }
    if(x == y) return x;
    for(int i = LOGN - 1; i >= 0; i--) {
      if(P[i][x] != P[i][y]) x = P[i][x], y = P[i][y];
    }
    return P[0][x];
  } 
  int dist(int u, int par){
    if(depth[u] < depth[par]) swap(u, par);
    return dists[u] - dists[par];
  } 
  int createtree() { 
    for(auto v: auxNodes) mark[v] = true, rem[v] = true;
    sort(ALL(auxNodes), cmp); 
    FOR(i, 0, SZ(auxNodes) - 1) { 
      int lc = LCA(auxNodes[i], auxNodes[i + 1]);
      if(mark[lc]) continue; 
      auxNodes.push_back(lc); 
      mark[lc] = true; 
    }
    sort(ALL(auxNodes), cmp);//***call pre,clear auxNodes,create tree,dfs
    for(int u: auxNodes) aux[u].clear(); 
    stack <int> sta; sta.push(auxNodes[0]);
    FOR(i, 1, SZ(auxNodes)){
      int u = auxNodes[i]; 
      while(!ancestor(sta.top(), u)) sta.pop();
      int v = sta.top(); 
      LL w = dist(u, v); // edge weight of the tree 
      aux[u].push_back({v, w});
      aux[v].push_back({u, w});
      sta.push(u); 
    } return auxNodes[0];
  }
}