// Set value for NODES and INF(also check in spfa function), call addEdge(u, v, capacity, cost)
// and for the answer use the loop in the end of main.
const int NODES = 256, INF = 600000000, INF2 = 1000000000;
int dis[NODES], prev2[NODES], inQ[NODES];
struct edge { int to, cap, cost; };
vector<edge> e; vector<int> g[NODES];
void addEdge(int u, int v, int cap, int cost) {
	g[u].push_back(e.size()); e.push_back({v, cap, cost});
	g[v].push_back(e.size()); e.push_back({u, 0,  -cost});
}
int spfa(int start, int sink) {
	memset(dis, 64, sizeof(dis));
	dis[start] = 0; prev2[start] = -1; inQ[start] = 1;
	queue<int> q; q.push(start);
	while(!q.empty()) {
		int u = q.front(); q.pop(); inQ[u] = 0;
		for(auto& v: g[u])
			if(e[v].cap && dis[e[v].to] > dis[u] + e[v].cost) {
				prev2[e[v].to] = v;
				dis[e[v].to] = dis[u] + e[v].cost;
				if (!inQ[e[v].to]) q.push(e[v].to);
				inQ[e[v].to] = 1;
			} }
	if (dis[sink] > INF) return INF;
	int temp = prev2[sink], aug;
	aug = e[temp].cap;
	while(temp!=-1) {
		aug = min(aug, e[temp].cap);
		temp = prev2[e[1^temp].to]; }
	temp = prev2[sink];
	while(temp!=-1) {
		e[temp].cap -= aug;
		e[1^temp].cap += aug;
		temp = prev2[e[1^temp].to]; }
	return (dis[sink]*aug); }
while(true) /*** in main ***/
	int temp = spfa(s, t); // min cost is returned
	if(temp == INF) break; ans += temp;
