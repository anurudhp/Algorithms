LL adj[N][N]; // input, ONLY SET THIS
LL wt[N]; bool pres[N], A[N]; // temp-vars(dont-touch)
pair<LL, VI> mincut(int n) { // no.of.verts
  pair<LL, VI> res(INF, VI()); vector<VI> comp(n);
  for (int i = 0; i < n; i++) comp[i].push_back(i);
  fill(pres, pres + N, true);
  for (int ph = 0; ph < n - 1; ph++) {
    memset(A, 0, sizeof A); memset(wt, 0, sizeof wt);
    for (int i = 1, prev = -1; i <= n - ph; i++) {
      int sel = -1;
      for (int u = 0; u < n; u++)
        if (pres[u] && !A[u] && (sel==-1 || wt[u]>wt[sel])) sel=u;
      if (i == n - ph) { // last phase
        if (wt[sel]<res.first) res=make_pair(wt[sel], comp[sel]);
        comp[prev].insert(comp[prev].end(), ALL(comp[sel]));
        for (int u = 0; u < n; u++)
          adj[u][prev] = adj[prev][u] += adj[u][sel];
        pres[sel] = false;
      } else {
        for (int u = 0; u < n; u++) wt[u] += adj[u][sel];
        A[sel] = true; prev = sel;
      }
    }
  }
  return res; }
