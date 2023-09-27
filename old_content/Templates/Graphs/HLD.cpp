vector<PII> g[MAXN];
const int null_val = INT_MIN; //null value eg. -inf for max
int head[MAXN], pos[MAXN], sz[MAXN], par[MAXN], h[MAXN], idx = 0;
//init sz=subtree size, par=parent node, h=node depth, call hld(root, -1, root, null_val);
void hld(int u, int par, int headno, int edgeval) {
  // remove edgeval if values are on nodes
  head[u] = headno; pos[u] = idx++;
  //update segtree at pos[u] to edgeval/node value
  int best = -1, bestedge;
  for(auto&v: g[u]) {
    if(v.first == par) continue;
    if(best == -1 || sz[v.first] > sz[best]) {
      best = v.first; bestedge = v.second;
    }
  }
  if(best != -1) hld(best, u, headno, bestedge);
  for(auto&v: g[u]) {
    if(v.first == par || v.first == best) continue;
    hld(v.first, u, v.first, v.second);
  }
}
int queryhld(int a, int b) { int ans = null_val;
  while(head[a] != head[b]) {
    if(h[head[a]] > h[head[b]]) swap(a, b);
    //update ans with query(pos[head[b]], pos[b])
    b = par[head[b]];
  } if(h[a] > h[b]) swap(a, b);
  //update ans with query(pos[a]+1, pos[b]), 
  // in case of node values, use pos[a], pos[b]
  return ans;
}
