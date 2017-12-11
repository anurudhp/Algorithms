// Min-Cost Max Flow

// Set value for NODES and INF(also check in spfa function), call addEdge(u, v, capacity, cost)
// and for the answer use the loop in the end of main.

#include <bits/stdc++.h>
#define fr(x) scanf("%d", &x)
using namespace std;

const int NODES = 256, INF = 600000000;
int dis[NODES], prev2[NODES], inQ[NODES];

struct edge {
	int to, cap, cost;
};

vector<edge> e;
vector<int> g[NODES];

void addEdge(int u, int v, int cap, int cost) {
	g[u].push_back(e.size());
	e.push_back({v, cap, cost});
	g[v].push_back(e.size());
	e.push_back({u, 0, -cost});
}

int spfa(int start, int sink) {
	queue<int> q;
	memset(dis, 64, sizeof(dis));
	dis[start] = 0;
	prev2[start] = -1;
	inQ[start] = 1;
	q.push(start);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inQ[u] = 0;
		for(auto&v:g[u]) {
			if(e[v].cap && dis[e[v].to] > dis[u] + e[v].cost) {
				prev2[e[v].to] = v;
				dis[e[v].to] = dis[u] + e[v].cost;
				if(!inQ[e[v].to]) q.push(e[v].to);
				inQ[e[v].to] = 1;
			}
		}
	}
	if(dis[sink] > INF) {
		return INF;
	}
	int temp = prev2[sink], aug;
	aug = e[temp].cap;
	while(temp!=-1) {
		aug = min(aug, e[temp].cap);
		temp = prev2[e[1^temp].to];
	}
	temp = prev2[sink];
	while(temp!=-1) {
		e[temp].cap -= aug;
		e[1^temp].cap += aug;
		temp = prev2[e[1^temp].to];
	}
	return (dis[sink]*aug);
}

signed main() {
	int n, m;

	// Problem Specific Code
	fr(n);
	fr(m);
	int s = n + 1;
	int t = n + 2;
	vector<int> balance(110);
	addEdge(n, 1, 1000000000, 0);

	int ans = 0;
	for(int i=1; i<=m; ++i) {
		int a, b, c, f;
		fr(a);
		fr(b);
		fr(c);
		fr(f);
		balance[a] += f;
		balance[b] -= f;
		if(f <= c) {
			addEdge(a, b, c - f, 1);
			addEdge(a, b, 1000000000, 2);
			addEdge(b, a, f, 1);
		}
		else {
			ans += f - c;
			addEdge(a, b, 1000000000, 2);
			addEdge(b, a, f - c, 0);
			addEdge(b, a, c, 1);
		}
	}

	int sumB = 0;
	for(int i=1; i<=n; ++i) {
		if(balance[i] > 0) {
			addEdge(i, t, balance[i], 0);
			sumB += balance[i];
		}
		else {
			addEdge(s, i, -balance[i], 0);
		}
	}

	// Max Flow Loop, Currently min cost is returned
	while(1) {
		int temp = spfa(s, t);
		if(temp == INF) break;
		ans += temp;
	}
	printf("%d\n", ans);
	return 0;
}