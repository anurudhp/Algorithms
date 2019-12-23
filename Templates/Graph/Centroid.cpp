//call dfsMCT,change solve and dfs1
vi vpart[L], g[L]; //H: depth 
bool vis[L];//par:parent in cent
int SZ[L], par[L], part[L], H[L], cpart;//cpart:no of parts in cent
//vpart[i]:nodes in part i
int dfsSZ(int v, int p = -1) { 
  SZ[v] = 1;
  for(int u: g[v]) if(!vis[u] && u!=p) SZ[v]+=dfsSZ(u, v);
  return SZ[v]; } 
int dfsFC(int v, int r, int p = -1) {
  for(int u: g[v]) if(!vis[u] && u!=p && SZ[u] > SZ[r] / 2)
    return dfsFC(u, r, v);
  return v; } 
void dfs1(int v, int r, int p) {
  if(p == r) part[v] = ++cpart, vpart[cpart].clear(); 
  else if(p != -1) part[v] = part[p];
  if(p != -1) vpart[cpart].push_back(v);
  for(int u: g[v]) 
    if(!vis[u] && u != p) H[u] = H[v] + 1, dfs1(u, r, v); } 
void solve(int r,int szr) { 
  H[r] = cpart = 0; 
  dfs1(r, r, -1);
  rep(i, 1, cpart + 1) { /* update all */ 
    for(int u: vpart[i]) /* add i part */; 
  }
  rep(i, 1, cpart+1) { 
      for(int u: vpart[i]) /* rem i part */;
      for(int u: vpart[i]) /* update ans */;
      for(int u: vpart[i]) /* add i part */;
  } 
  /* ans for root */ ; 
  // if the container used for storing isn't local.
  rep(i, 1, cpart + 1) { /* remove all */ 
    for(int u: vpart[i]) /* remove i part */;  } } 
void dfsMCT (int u, int p = -1) { 
  dfsSZ(u);
  int r = dfsFC(u, u); par[r] = p; 
  solve(r, SZ[u]); vis[r] = true;
  for(int u: g[r]) if(!vis[u]) dfsMCT(u,r); }