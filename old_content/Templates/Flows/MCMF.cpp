template<typename FLOW, typename COST>
struct MCMF {
  const COST INFC = 1e9, EPSC = 0;
  const FLOW INFF = 1e9, EPSF = 0;
  struct Edge {int from, to; FLOW flow, cap; COST cost;};
  int nodes, src, dest, m=0;
  vector<vector<int>> adj; vector<Edge> edges;
  void add(int u, int v, FLOW cap, COST cost) {
    edges.PB({u, v, 0, cap, cost}); adj[u].PB(m++);
    edges.PB({v, u, 0, 0, -cost}); adj[v].PB(m++);
  }
  vector<COST> dis; vector<bool> inQ; VI par;
  pair<FLOW, COST> SPFA() {
    fill(ALL(dis), INFC); fill(ALL(inQ), false);
    queue<int> Q; dis[src]=0; Q.push(src); inQ[src]=true;
    while (!Q.empty()) { int u = Q.front(); Q.pop(); inQ[u]=false;
      for (int i: adj[u]) { auto& e = edges[i];
        if (e.cap-e.flow > EPSF && dis[e.to]-(dis[u]+e.cost) > EPSC) {
          dis[e.to] = dis[u]+e.cost; par[e.to] = i;
          if (!inQ[e.to]) { Q.push(e.to); inQ[e.to]=true;}
        } }
    } if (dis[dest] + EPSC >= INFC) return MP(0, 0);
    FLOW aug = INFF;
    for (int u = dest; u != src; u = edges[par[u]].from) {
      aug = min(aug, edges[par[u]].cap - edges[par[u]].flow);
    }
    for (int u = dest; u != src; u = edges[par[u]].from) {
      edges[par[u]].flow += aug; edges[par[u] ^ 1].flow -= aug;
    } return MP(aug, aug * dis[dest]);
  } 
  MCMF(int n, int s, int t): nodes(n), src(s), dest(t), 
       adj(n), dis(n), inQ(n), par(n) {}
  pair<FLOW, COST> mincostmaxflow() { pair<FLOW, COST> ans(0, 0);
    while (true) { auto cur = SPFA();
      if (cur.first <= EPSF) break;
      ans.first += cur.first; ans.second += cur.second;
    } return ans;
  }
};
