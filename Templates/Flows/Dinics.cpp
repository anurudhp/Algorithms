struct Dinic {
  typedef int FT;
  static const FT INF = 1e9;
  struct FlowEdge { int v, u; FT cap, flow = 0;
    FlowEdge(int v, int u, FT cap) : v(v), u(u), cap(cap) {}
  };
  int n, m = 0, src, dest;
  vector<FlowEdge> edges; vector<vector<int>> adj;
  vector<int> level, ptr; queue<int> q;

  Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}
  void add_edge(int v, int u, FT cap) {
    edges.EMB(v, u, cap); adj[v].PB(m);
    edges.EMB(u, v, 0); adj[u].PB(m + 1);
    m += 2;
  }
  bool bfs() {
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int id : adj[v]) {
        if (edges[id].cap - edges[id].flow < 1) continue;
        if (level[edges[id].u] != -1) continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    } return level[dest] != -1;
  }
  FT dfs(int v, FT pushed) {
    if (pushed == 0) return 0;
    if (v == dest) return pushed;
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid];
      int u = edges[id].u;
      if (level[v]+1 != level[u] || edges[id].cap-edges[id].flow < 1)
        continue;
      FT tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0) continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    } return 0;
  }
  FT max_flow(int s, int t) {
    src = s, dest = t; FT f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0; q.push(s);
      if (!bfs()) break;
      fill(ptr.begin(), ptr.end(), 0);
      while (FT pushed = dfs(s, INF)) f += pushed;
    } return f;
  }
};
