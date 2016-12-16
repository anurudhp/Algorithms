#include <bits/stdc++.h>
using namespace std;

class Dinics {
public:
	typedef int flowType;
	static const flowType INF = 1e9; // maximum capacity
	static const flowType EPS = 0; // minimum capacity/flow change

private:
	int nodes, src, dest;
	vector<int> dist, q, work;
	struct Edge {
	  int to, rev;
	  flowType f, cap;
	};
	vector< vector<Edge> > g;

	bool dinic_bfs() {
	  fill(dist.begin(), dist.end(), -1);
	  dist[src] = 0;
	  int qt = 0;
	  q[qt++] = src;
	  for (int qh = 0; qh < qt; qh++) {
	    int u = q[qh];
	    for (int j = 0; j < (int) g[u].size(); j++) {
	      Edge &e = g[u][j];
	      int v = e.to;
	      if (dist[v] < 0 && e.f < e.cap) {
	        dist[v] = dist[u] + 1;
	        q[qt++] = v;
	      }
	    }
	  }
	  return dist[dest] >= 0;
	}
	int dinic_dfs(int u, int f) {
	  if (u == dest)
	    return f;
	  for (int &i = work[u]; i < (int) g[u].size(); i++) {
	    Edge &e = g[u][i];
	    if (e.cap <= e.f) continue;
	    int v = e.to;
	    if (dist[v] == dist[u] + 1) {
	      flowType df = dinic_dfs(v, min(f, e.cap - e.f));
	      if (df > 0) {
	        e.f += df;
	        g[v][e.rev].f -= df;
	        return df;
	      }
	    }
	  }
	  return 0;
	}

public:
	Dinics(int n): dist(n, 0), q(n, 0),
		work(n, 0), g(n), nodes(n) {}

	// s->t (cap); t->s (rcap)
	void addEdge(int s, int t, flowType cap, flowType rcap = 0){
	  g[s].push_back({t, (int) g[t].size(), 0, cap});
	  g[t].push_back({s, (int) g[s].size(), 0, rcap});
	}
	flowType maxFlow(int _src, int _dest) {
	  src = _src;
	  dest = _dest;
	  flowType result = 0;
	  while (dinic_bfs()) {
	    fill(work.begin(), work.end(), 0);
			flowType delta;
	    while ((delta = dinic_dfs(src, INF)) > EPS)
	      result += delta;
	  }
	  return result;
	}
};

class Bipartite: Dinics {
	int m, n;
	int s, t;
public:
	Bipartite(int m, int n, int dcap = 1): Dinics(m + n + 2) {
		this->m = m;
		this->n = n;
		s = 0, t = m + n + 1;
		for (int i = 1; i <= m; i++) Dinics::addEdge(s, i, dcap);
		for (int j = m + 1; j <= m + n; j++) Dinics::addEdge(j, t, dcap);
	}
	void addEdge(int i, int j, flowType cap = 1) {
		Dinics::addEdge(i + 1, j + m + 1, cap);
	}
	flowType maxMatch() {
		return Dinics::maxFlow(s, t);
	}
};

/* Usage:
	Dinics flow(<number of nodes>);
	flow.addEdge(<from>, <to>, <capacity>[, <reverse capacity>]);
	...
	result = flow.maxFlow(<source>, <sink>);

	Bipartite b(<lhs>, <rhs>[, <default capacity>]);
	b.addEdge(<from>, <to>[, <capacity>]);
	...
	result = b.maxMatch();
*/
