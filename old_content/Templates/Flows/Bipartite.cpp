struct Bipartite { int L, R; // 0-based indexing for add_edge!
  Dinic net; 
  Bipartite(int l, int r): L(l), R(r), net(l+r+2) {}
  void add_edge(int u, int v) { net.add_edge(1+u, 1+L+v, 1); }
  int max_matching() { int s = 0, t= 1 + L + R;
    FOR(u, 0, L) net.add_edge(s, 1+u, 1);
    FOR(v, 0, R) net.add_edge(1+L+v, t, 1);
    return net.max_flow(s, t);
  } vector<PII> get_matched() { // call matching first!
    vector<PII> matched;
    FOR(u, 0, L) {
      for (int i: net.adj[1 + u]) { auto& e = net.edges[i];
        if (e.to > L && e.cap == 1 && e.flow == 1) {
          matched.EB(u, e.to - 1 - L); break;
    } } } return matched;
  } vector<bool> Z; // Z only for vertex-cover
  void vcdfs(int u, int w) { Z[u] = true;
    for (int i: net.adj[u]) {
      auto& e = net.edges[i], forwe = net.edges[i ^ w];
      if (e.to == 0 || e.to == 1 + L + R) continue;
      if (!Z[e.to] && forwe.cap - forwe.flow == 1 - w) {
        vcdfs(e.to, 1 ^ w);
    } }
  } VI vertex_cover() { // call matching first!
    Z.assign(L + R + 2, false); FOR(u, 0, L) Z[1 + u] = true;
    auto matched = get_matched();
    for (auto& e: matched) { Z[1 + e.first] = false; }
    FOR(u, 0, L) { if (Z[1 + u]) vcdfs(1 + u, 0); }
    VI cover; // Left: 0-indexed, Right: L-indexed
    FOR(u, 0, L) { if (!Z[1 + u]) cover.PB(u); } 
    FOR(v, 0, R) { if (Z[1 + L + v]) cover.PB(L + v); }
    return cover;
  }
};