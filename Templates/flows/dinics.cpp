class Dinics {
public: typedef int FT; // can use float/double
	static const FT INF = 1e9; // maximum capacity
	static const FT EPS = 0; // minimum capacity/flow change
	int nodes, src, dest;
	vector<int> dist, q, work;
	struct Edge { int to, rev; FT f, cap; };
	vector< vector<Edge> > g;

	bool dinic_bfs() {
	  fill(dist.begin(), dist.end(), -1);
	  dist[src] = 0;
	  int qt = 0;
	  q[qt++] = src;
	  for (int qh = 0; qh < qt; qh++) {
	    int u = q[qh];
	    for (int j = 0; j < (int) g[u].size(); j++) {
	      Edge &e = g[u][j]; int v = e.to;
	      if (dist[v] < 0 && e.f < e.cap)
	        dist[v] = dist[u] + 1; q[qt++] = v;
	    }
	  }  return dist[dest] >= 0;
	}
	int dinic_dfs(int u, int f) {
	  if (u == dest) return f;
	  for (int &i = work[u]; i < (int) g[u].size(); i++) {
	    Edge &e = g[u][i];
	    if (e.cap <= e.f) continue;
	    int v = e.to;
	    if (dist[v] == dist[u] + 1) {
	      FT df = dinic_dfs(v, min(f, e.cap - e.f));
	      if (df > 0) { e.f += df, g[v][e.rev].f -= df;
	        return df; }
	    }
	  } return 0;
	}

	Dinics(int n): dist(n, 0), q(n, 0), work(n, 0), g(n), nodes(n) {}
	// *** s->t (cap); t->s (rcap)
	void addEdge(int s, int t, FT cap, FT rcap = 0) {
	  g[s].push_back({t, (int) g[t].size(), 0, cap});
	  g[t].push_back({s, (int) g[s].size() - 1, 0, rcap});
	} // ***
	FT maxFlow(int _src, int _dest) {
	  src = _src, dest = _dest;
	  FT result = 0, delta;
	  while (dinic_bfs()) {
	    fill(work.begin(), work.end(), 0);
	    while ((delta = dinic_dfs(src, INF)) > EPS) result += delta;
	  } return result;
	}
};
