vector<VI> adj; VI pre, low, onstack, comp;
int dfsno, compno; stack<int> stk;
void init(int n) { dfsno = compno = 0;
  adj.assign(n, VI()); stk = stack<int>(); onstack.assign(n, 0);
  pre.assign(n, -1); low.assign(n, -1); comp.assign(n, -1);
} void add_edge(int u, int v) { adj[u].PB(v); }
void dfs(int u) {
  pre[u] = low[u] = dfsno++;
  stk.push(u); onstack[u] = true;
  for (int v: adj[u]) {
    if (pre[v] == -1) { dfs(v); low[u] = min(low[u], low[v]); }
    else if (onstack[v]) { low[u] = min(low[u], pre[v]); }
  }
  if (pre[u] == low[u]) {
    int v; do {
      v = stk.top(); stk.pop(); 
      onstack[v] = false; comp[v] = compno;
    } while (v != u);
    ++compno;
  }
}
