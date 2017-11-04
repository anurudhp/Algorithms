// https://www.codechef.com/viewplaintext/16084415
// Values are associated with edges -> Values are associated with child node
// Query from x to y is exclusive of LCA

#include <bits/stdc++.h>
#define int long long int

using namespace std;

const int MAX = 1e5 + 5;

int N, Q, timer = 0;
int lev[MAX], p[MAX], sub[MAX], pos[MAX], head[MAX], s[4 * MAX], back[MAX], val[MAX];
vector<pair<int, int> > v[MAX];
vector<pair<pair<int, int>, int> > e;

void clear(){
	timer = 0;
	for(int i=1; i<=N; ++i){
		v[i].clear();
		lev[i] = p[i] = sub[i] = pos[i] = head[i] = back[i] = val[i] = 0;
	}
	memset(s, 0, sizeof s);
	e.clear();
}

int func(int x) {
	int cnt = __builtin_popcount(x);
	int x1 = ((1LL<<cnt) - 1);
	int y1 = (x1<<(50-cnt));
	return (x1 ^ y1);
}


void dfs(int cur, int par){
	lev[cur] = lev[par] + 1;
	p[cur] = par;
	sub[cur] = 1;
	for(auto it:v[cur]){
		if(it.first != par){
			dfs(it.first, cur);
			sub[cur] += sub[it.first];
		}
	}
}

void hld(int cur, int par, int h = 1){
	pos[cur] = ++timer;
	back[timer] = cur;
	head[cur] = h;
	int sc = 0;
	for(auto it:v[cur]){
		if(it.first != par){
			if(sub[it.first] > sub[sc]) sc = it.first;
		}
	}
	if(!sc) return;
	hld(sc, cur, h);
	for(auto it:v[cur]){
		if(it.first == par || it.first == sc) continue;
		hld(it.first, cur, it.first);
	}
}

void build(int l, int r, int node){
	if(l == r){
		s[node] = func(val[back[l]]);
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, node << 1);
	build(mid + 1, r, 1 | node << 1);
	s[node] = max(s[node << 1], s[1 | node << 1]);
}

int query(int l, int r, int node, int ql, int qr){
	if(l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return s[node];
	int mid = (l + r) >> 1;
	return max(query(l, mid, node << 1, ql, qr), query(mid + 1, r, 1 | node << 1, ql, qr));
}

void update(int l, int r, int node, int pos, int val){
	if(l > pos || r < pos) return;
	if(l == r){
		s[node] = func(val);
		return;
	} 
	int mid = (l + r) >> 1;
	update(l, mid, node << 1, pos, val);
	update(mid + 1, r, 1 | node << 1, pos, val);
	s[node] = max(s[node << 1], s[1 | node << 1]);
}

int get_distance(int x, int y){
	int ans = 0;
	while(head[x] != head[y]){
		if(lev[head[x]] < lev[head[y]]) swap(x, y);
		int l = pos[x];
		int r = pos[head[x]];
		if(l > r) swap(l, r);
		ans = max(ans, query(1, N, 1, l, r));
		x = p[head[x]];
	}
	if(x == y) return ans;
	if(lev[x] < lev[y]) swap(x, y);
	int l = pos[x];
	int r = pos[y];
	ans = max(ans, query(1, N, 1, min(l, r) + 1, max(l, r)));
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(false);

	int t; cin >> t;
	while(t--){
		cin >> N;
		for(int i=1; i<N; ++i){
			int x, y, z; cin >> x >> y >> z;
			e.push_back({{x, y}, z});
			v[x].push_back({y, z});
			v[y].push_back({x, z});
		}

		dfs(1, 0);
		hld(1, 0);

		for(auto &it:e){
			if(p[it.first.first] == it.first.second) swap(it.first.first, it.first.second);
			val[it.first.second] = it.second;
		}

		build(1, N, 1);

		cin >> Q;
		while(Q--){
			int ty; cin >> ty;
			if(ty == 1){
				int P, Q; cin >> P >> Q;
				--P;
				int x = e[P].first.first, y = e[P].first.second;
				update(1, N, 1, pos[y], Q);

			}
			else{
				int x, y; cin >> x >> y;
				cout << get_distance(x, y) << endl;
			}
		}

		clear();

	}
	
	return 0;
}
