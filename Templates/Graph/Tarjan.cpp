const int N = 1e5; // nodes
int dfsno=0, pre[N], low[N], onstack[N];
int cno, comp[N]; // forms toposort: largest cno=root
vector<int> adj[N];
stack<int> stk;
void dfs(int u) {
  if (pre[u] > 0) return;
  pre[u] = low[u] = ++dfsno;
  stk.push(u); onstack[u] = true;
  for (int v: adj[u]) {
    if (pre[v] == 0) dfs(v), low[u] = min(low[u], low[v]);
    else if (onstack[v]) low[u] = min(low[u], pre[v]);
  }
  if (pre[u] == low[u]) {
    int v; do {
      v = stk.top(); stk.pop();
      onstack[v] = false; comp[v] = cno;
    } while (v != u);
    ++cno;
  }
}
// for (int i=0;i<n;i++) dfs(i);
