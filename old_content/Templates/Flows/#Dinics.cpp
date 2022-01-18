struct Dinic { using FT = int;
  static const FT INF = 1 << 30; // CHOOSE CAREFULLY!
  struct Edge { int from, to; FT cap, flow = 0;
    Edge(int from, int to, FT cap) : from(from), to(to), cap(cap) {}
  }; 
  int n, m = 0, src, dest; FT LIM = 1;
  vector<Edge> edges; vector<VI> adj; VI level, ptr; 
  Dinic(int n) : n(n), adj(n), level(n), ptr(n) {}
  void add_edge(int u, int v, FT cap) {
    edges.EB(u, v, cap); adj[u].PB(m); m++;
    edges.EB(v, u, 0);   adj[v].PB(m); m++;
  }
  bool bfs() { fill(ALL(level), -1); level[src] = 0; 
    VI q(n+10); int qh = 0, qt = -1; q[++qt] = src;
    while (qh <= qt) { // QUEUE be careful
      int u = q[qh++]; // QUEUE be careful
      for (int id : adj[u]) { int v = edges[id].to;
        if (edges[id].cap - edges[id].flow < LIM) continue;
        if (level[v] != -1) continue;
        level[v] = level[u] + 1;
        q[++qt] = v; // QUEUE be careful
      }
    } return level[dest] != -1;
  }
  FT dfs(int u, FT pushed) {
    if (pushed == 0) return 0;
    if (u == dest) return pushed;
    for (int& cid = ptr[u]; cid < SZ(adj[u]); cid++) {
      int id = adj[u][cid]; int v = edges[id].to;
      if (level[u] + 1 != level[v]) continue;
      FT tr = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
      if (tr > 0) {
        edges[id].flow += tr; edges[id ^ 1].flow -= tr;
        return tr;
    } } return 0;
  }
  FT max_flow(int s, int t) { src = s, dest = t; FT f = 0;
    // for (LIM = INF >> 1; LIM > 0; LIM >>= 1) // SCALING
      while (bfs()) {  fill(ALL(ptr), 0);
        while (FT pushed = dfs(s, INF)) f += pushed;
      } 
    return f;
  }
};
