vector <int> g[N], Tree[N]; // g is an edge-list 
int U[M], V[M], W[M], dsu[N], t, arr[N];
bool vis[N], is_bridge[M]; 
int f(int x) { return dsu[x] = (x == dsu[x]) ? x: f(dsu[x]); }
int adj(int v, int e) { return U[e] ^ V[e] ^ v; }
bool merge(int a, int b) { 
  a = f(a), b = f(b);
  if(a == b) return false;
  dsu[a] = b;
  return true; 
}
int dfs0(int v, int edge){
  vis[v] = true, arr[v] = t++;
  int dbe = arr[v]; //useforbridges
  for(int e: g[v]) {
    int to = adj(v, e);
    if(!vis[to]) dbe = min(dbe, dfs0(to, e));
    else if(e != edge) dbe = min(dbe, arr[to]);
  }
  if((dbe == arr[v]) && (edge != -1)) is_bridge[edge] = true;
  else if(edge != -1) merge(U[edge], V[edge]);
  return dbe; 
}
void build_tree(int n, int m){
  rep(i, 1, n + 1) dsu[i] = i;
  rep(i, 1, n + 1) if(!vis[i]) dfs0(i, -1);
  rep(i, 1, m + 1) {
    if(f(U[i]) != f(V[i])) {
      Tree[f(U[i])].push_back(f(V[i])); 
      Tree[f(V[i])].push_back(f(U[i]));
    }
  }
}