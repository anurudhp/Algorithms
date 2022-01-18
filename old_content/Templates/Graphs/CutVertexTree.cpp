const int N = 2e5;
VI g[N], cutVtree[N], st; //g[v]: edge-list, Take N = 2*required
int a[N], b[N], compNo[N], col[N];
int low[N], in[N], L[N], extra[N], T, C;
bool cutV[N]; // true for cut-vertices.
int adj(int u, int i) { return a[i] ^ b[i] ^ u; }
void dfs(int v) {
  int ch = 0;
  low[v] = in[v] = T++;
  for(int e: g[v]) {
    int u = adj(v, e);
    if (in[u] == -1) {
      L[u] = L[v] + 1, st.PB(e), dfs(u);
      low[v] = min(low[v], low[u]);
      if (in[v] == 0 || low[u] >= in[v]) {
        if (in[v]||ch) cutV[v] = true;
        ++C;
        while(SZ(st)) {
          int ed = st.back();
          col[ed] = C, st.pop_back();
          if (ed == e) break;
        }
      }
    } else if (L[u] < L[v] - 1) { // back-edge.
      low[v] = min(low[v], in[u]), st.PB(e);
    }
    ++ch;
  }
  return;
}  
void run(int n) {
  SET(in, -1); st.resize(0); C = 0;
  FOR(i, 1, n + 1) if (in[i] == -1) T = 0, dfs(i);
} 
void build_tree(int n) {
  run(n);
  VI temp;
  SET(extra, 0);
  FOR(i, 1, n + 1) {
    temp.clear();
    for(int e: g[i]) {
      temp.PB(col[e]);
    }
    sort(ALL(temp));
    temp.erase(unique(ALL(temp)), temp.end());
    if (temp.empty()) {
      compNo[i] = C + i, extra[C + i] = 1;
    } else if (SZ(temp) == 1) { // belongs to only 1 component.
      compNo[i] = temp[0], extra[temp[0]] = 1;
    } else { // cutVertex
      compNo[i] = C + i, extra[C + i] = 1;
      for(int u: temp) {
        extra[u] = 1;
        cutVtree[C + i].PB(u);
        cutVtree[u].PB(C + i);
      }
    }
  }
  return;
} 