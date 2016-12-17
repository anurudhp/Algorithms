namespace Tarjan {
  vector<int> pre, low;
  vector<vector<int>> comps;
  vector<bool> onstack;
  stack<int> st;
  vector<int> *adj;
  int dfsno;

  void push(int u) { st.push(u); onstack[u] = 1; }
  int pop() { int v = st.top(); st.pop(); onstack[v] = 0; return v; }

  void dfs(int u) {
    pre[u] = low[u] = dfsno++;
    push(u);

    for (int v: adj[u]) {
      if (pre[v] == -1) {
        dfs(v);
        low[u] = min(low[u], low[v]);
      } else if (onstack[v]) {
        low[u] = min(low[u], pre[v]);
      }
    }
    if (low[u] == pre[u]) {
      comps.emplace_back();
      auto& curr = comps.back();
      int v;
      do curr.push_back(v = pop()); while (v != u);
    }
  }

  vector<vector<int>> computeSCC(int n, vector<int>* iadj) {
    pre = vector<int>(n, -1);
    low = vector<int>(n, -1);
    onstack = vector<bool>(n, false);
    st = stack<int>();
    comps.clear();

    dfsno = 0;
    adj = iadj;
    for (int u = 0; u < n; u++) if (pre[u] == -1) dfs(u);
    return comps;
  }
};
