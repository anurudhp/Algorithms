#include <bits/stdc++.h>
#define int long long int
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
vector<pair<int, int> > v[MAX], aux;
vector<int> tree[MAX], arr;
int start[MAX], en[MAX], sub[MAX], pos[MAX], par[MAX], is[MAX], lev[MAX];
int sum[4 * MAX];
int N, K, Q, timer, root, head[MAX], p[MAX], SIZE[MAX], SUB[MAX];

vector<pair<pair<int, int>, int> > edges;

vector<int> group[MAX]; 

void clear(){
	for(int i=1; i<=N; ++i){
		v[i].clear();
		group[i].clear();
		start[i] = en[i] = sub[i] = pos[i] = par[i] = is[i] = lev[i] = 0;
		head[i] = p[i] = SIZE[i] = SUB[i] = 0;
	} 
	memset(sum, 0, sizeof sum);
	timer = 0, root = 0;
}

int dfs(int cur, int p, int level = 1){
	lev[cur] = level;
	start[cur] = ++timer;
	for(auto it:v[cur]){
		if(it.first == p) continue;
		dfs(it.first, cur, level + 1);
		par[it.first] = cur;
		sub[cur] += sub[it.first];
	}
	en[cur] = ++timer;
	++sub[cur];
}
void update(int l, int r, int node, int pos, int val){
	if(l > pos || r < pos) return;
	if(l == r){
		sum[node] = val;
		return;
	}
	int mid = (l + r) >> 1;
	update(l, mid, node << 1, pos, val);
	update(mid + 1, r, 1 | node << 1, pos, val);
	sum[node] = (sum[node << 1] + sum[1 | node << 1]) % MOD;
}
void hld(int cur, int p, int h = 1){
	head[cur] = h;
	pos[cur] = ++timer;
	int sc = 0;
	for(auto it:v[cur]){
		if(it.first == p) continue; 
		if(sub[it.first] > sub[sc]) sc = it.first;
	}
	if(!sc) return;
	hld(sc, cur, h);
	for(auto it:v[cur]){
		if(it.first == p) continue;
		if(it.first == sc){
			update(1, N, 1, pos[it.first], it.second);
			continue;
		}
		hld(it.first, cur, it.first);
		update(1, N, 1, pos[it.first], it.second);
	}
}
int query(int l, int r, int node, int ql, int qr){
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return sum[node];
	int mid = (l + r) >> 1;
	return (query(l, mid, node << 1, ql, qr) + query(mid + 1, r, 1 | node << 1, ql, qr)) % MOD;
}
int LCA(int x, int y){
	while(true){
		if(head[x] == head[y]){
			if(lev[x] < lev[y]) return x;
			return y;
		}
		if(lev[head[x]] < lev[head[y]]) y = par[head[y]];
		else x = par[head[x]];
	}
}
void get_vertices(){
	sort(aux.begin(), aux.end());
	int len = aux.size();
	for(int i=1; i<len; ++i){
		int x = LCA(aux[i].second, aux[i - 1].second);
		aux.push_back({start[x], x});
	} 
	for(auto it:aux) is[it.second] = 0;
	vector<pair<int, int> >temp; temp.clear();
	for(auto it:aux){
		if(is[it.second]) continue;
		temp.push_back(it);
		is[it.second] = 1;
	}
	aux.clear();
	for(auto it:temp) aux.push_back(it), is[it.second] = 0;
	sort(aux.begin(), aux.end());	
}
int get_distance(int x, int y){
	int ans = 0;
	while(true){
		if(x == y) break;
		if(head[x] == head[y]){
			ans = ans + ((query(1, N, 1, min(pos[x], pos[y]), max(pos[x], pos[y])) - query(1, N, 1, min(pos[x], pos[y]), min(pos[x], pos[y]))) % MOD) + MOD;
			ans %= MOD;
			break;
		}
		if(lev[head[x]] < lev[head[y]]) swap(x, y);
		ans = (ans + query(1, N, 1, pos[head[x]], pos[x])) % MOD;
		x = par[head[x]];
	}
	return ans;
}
void first_dfs(int cur, int parent){
	SUB[cur] = SIZE[cur];
	for(auto it:tree[cur]){
		if(it != parent){
			first_dfs(it, cur);
			SUB[cur] = (SUB[cur] + SUB[it]) % MOD;
			p[it] = cur;
		}
	}
}
int solve(int total){
	edges.clear();
	get_vertices();
	root = aux[0].second;
	for(auto it:aux) tree[it.second].clear();
	stack<int> s; s.push(aux[0].second);
	for(int i=1; i<aux.size(); ++i){
		int cur = aux[i].second;
		while(true){
			if(en[s.top()] < start[cur]) s.pop();
			else break;
		}
		tree[s.top()].push_back(cur);
		edges.push_back({{s.top(), cur}, get_distance(s.top(), cur)});
		s.push(cur);
	}
	int ans = 0;
	first_dfs(root, 0);
	for(auto it:edges){
		int x = it.first.first, y = it.first.second, z = it.second;
		if(p[x] == y) swap(x, y);
		int X = total - SUB[y], Y = SUB[y];
		ans = (ans + (((X * 1LL * Y) % MOD) * 1LL * z) % MOD) % MOD;
	}
	ans = (ans + ans) % MOD;
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while(t--){
		cin >> N >> K;
		for(int i=1; i<=N; ++i){
			int x; cin >> x;
			group[x].push_back(i);
		}
		for(int i=1; i<N; ++i){
			int x, y, z;
			cin >> x >> y >> z;
			v[x].push_back({y, z});
			v[y].push_back({x, z});
		}
		timer = 0;
		dfs(1, 0);
		timer = 0;
		hld(1, 0);
		for(int i=1; i<=K; ++i){
			aux.clear();
			arr.clear();
			// group i has set of vertices for ith query
			for(auto it:group[i]){
				SUB[it] = 0;
				SIZE[it] = 1;
				aux.push_back({start[it], it});
				arr.push_back(it);
			}
			cout << solve(group[i].size()) << endl;
			for(auto it:group[i]) SIZE[it] = 0;
		}
		clear();
	}
}
