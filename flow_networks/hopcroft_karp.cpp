class HopcroftKarp {
public:
  static const int INF = 1e9;

private:
  int U, V, nil;
  vector<int> pairU, pairV, dist;
  vector< vector<int> > adj;

  bool bfs() {
    queue<int> q;
    for (int u = 0; u < U; u++) {
      if (pairU[u] == nil) {
        dist[u] = 0;
        q.push(u);
      } else {
        dist[u] = INF;
      }
    }
    dist[nil] = INF;
    while (not q.empty()) {
      int u = q.front(); q.pop();
      if (dist[u] >= dist[nil]) continue;
      for (int v: adj[u]) {
        if (dist[pairV[v]] == INF) {
          dist[pairV[v]] = dist[u] + 1;
          q.push(pairV[v]);
        }
      }
    }
    return dist[nil] != INF;
  }
  bool dfs(int u) {
    if (u == nil) return true;
    for (int v: adj[u]) {
      if (dist[pairV[v]] == dist[u] + 1) {
        if (dfs(pairV[v])) {
          pairV[v] = u;
          pairU[u] = v;
          return true;
        }
      }
    }
    dist[u] = INF;
    return false;
  }
public:
  HopcroftKarp(int U_, int V_) {
    U = U_, V = V_;
    nil = U;
    adj.resize(U + 1);
    pairU.resize(U + 1);
    pairV.resize(V);
    dist.resize(U + 1);
  }
  void addEdge(int u, int v) {
    adj[u].push_back(v);
  }
  int maxMatch() {
    fill(pairU.begin(), pairU.end(), nil);
    fill(pairV.begin(), pairV.end(), nil);
    int res = 0;
    while (bfs()) {
      for (int u = 0; u < U; u++) {
        if (pairU[u] == nil && dfs(u)) res++;
      }
    }
    return res;
  }
};
