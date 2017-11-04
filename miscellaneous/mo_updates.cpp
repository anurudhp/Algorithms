// https://www.codechef.com/viewplaintext/12824787

#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 5;
const int LOG = 25;

int p[MAX][LOG + 1], in[MAX], out[MAX], lev[MAX], getNode[MAX], c[MAX], frq[MAX], fans[MAX], vis[MAX];
int timer = 0, BLOCK, N, Q, ans = 0;

map<int,int> M;

vector<int> v[MAX];
vector<int> w;
vector<pair<int, pair<int,int> > >qr;

struct query{
	int l, r, qtime, utime, lca;
};

query que[MAX];

int id[MAX], cc[MAX];
// 
void dfs(int cur, int par){
	p[cur][0] = par;
	lev[cur] = lev[par] + 1;
	in[cur] = ++timer;
	getNode[timer] = cur;
	for(auto it:v[cur]){
		if(it == par) continue;
		dfs(it, cur);
	}
	out[cur] = ++timer;
	getNode[timer] = cur;
}

int getLCA(int x, int y){
	if(lev[x] < lev[y]) swap(x, y);
	int d = lev[x] - lev[y];
	for(int i=0; i<LOG; ++i){
		if(p[x][i]){
			if((d & (1 << i))){
				x = p[x][i];
			}
		}
	}
	if(x == y) return x;
	for(int i=LOG-1; i>=0; --i){
		if((p[x][i] && p[y][i]) && (p[x][i] != p[y][i])){
			x = p[x][i];
			y = p[y][i];
		}
	}
	// assert(p[x][0] == p[y][0]);
	return p[x][0];
}

bool compare(query &x, query &y){
	if(x.l / BLOCK == y.l / BLOCK){
		if(x.r / BLOCK == y.r / BLOCK){
			return x.utime < y.utime;
		}
		return x.r / BLOCK < y.r / BLOCK;
	}
	return x.l / BLOCK < y.l / BLOCK;
}

int add(int node){
	int val = c[node];
	if(frq[val] == 0) ++ans;
	++frq[val];
}

int remove(int node){
	int val = c[node];
	if(frq[val] == 1) --ans;
	--frq[val];
}

void move(int idx){
	if(idx == 0) return;
	int node = getNode[idx];
	if(vis[node]) remove(node);
	else add(node);
	vis[node] ^= 1;
}

void refresh(int time){
	int node = id[time];
	if(vis[node]) remove(node);
	swap(c[node], cc[time]);
	if(vis[node]) add(node);
}

int main(){

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> Q;
	// assert(N*Q <= 20000000);
	for(int i=1; i<=N; ++i){
		cin >> c[i];
		w.push_back(c[i]);	
	} 
	for(int i=1; i<N; ++i){
		int x, y; cin >> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);
	}

	if(N <= 100000) BLOCK = 1750;
	if(N <= 90000) BLOCK = 1630;
	if(N <= 80000) BLOCK = 1510;
	if(N <= 10000) BLOCK = 390;
	dfs(1, 0);	
	
	for(int i=1; i<LOG; ++i){
		for(int j=1; j<=N; ++j){
			if(p[j][i-1] && p[p[j][i-1]][i-1]){
				p[j][i] = p[p[j][i-1]][i-1];
			}
		}
	}

	for(int i=1; i<=Q; ++i){
		int x, y, z; cin >> x >> y >> z;
		qr.push_back({x, {y, z}});
		if(x == 2) w.push_back(z);
	}

	sort(w.begin(), w.end());
	int xx = 0;
	for(auto it:w){
		if(M[it] == 0){
			M[it] = ++xx;
		}
	}
	for(int i=1; i<=N; ++i) c[i] = M[c[i]];
	for(auto &it:qr){
		if(it.first == 2){
			it.second.second = M[it.second.second];
		}
	}

	int X = 1, Y = 1;
	for(int i=1; i<=Q; ++i){
		int t, x, y; 
		t = qr[i-1].first;
		x = qr[i-1].second.first;
		y = qr[i-1].second.second;
		if(t == 1){
			if(in[x] > in[y]) swap(x, y);
			int z = getLCA(x, y);
			if(z == x){
				que[X].l = in[x];
				que[X].r = in[y];
				que[X].qtime = X;
				que[X].utime = Y;
				que[X].lca = 0;
			}
			else{	
				que[X].l = out[x];
				que[X].r = in[y];
				que[X].qtime = X;
				que[X].utime = Y;
				que[X].lca = z;
			}
			assert(que[X].l <= que[X].r);
			++X;
		}
		else{
			id[Y] = x;
			cc[Y] = y;
			++Y;
		}		
	}


	sort(que+1, que+X, compare);

	int l = 0, r = -1, T = 1;

	for(int i=1; i<X; ++i){
		query &q = que[i];
		// if(q.l > q.r) swap(q.l, q.r);
		// assert(q.l <= q.r);
		while(q.l < l) move(--l);
		while(r < q.r) move(++r);
		while(l < q.l) move(l++);
		while(q.r < r) move(r--);
		while(T < q.utime) refresh(T++);	
		while(q.utime < T) refresh(--T);	
		if(q.lca) add(q.lca);	
		fans[q.qtime] = ans;
		if(q.lca) remove(q.lca);
	}


	for(int i=1; i<X; ++i) cout << fans[i] << '\n';

	// for(int i=1; i<X; ++i) cout << getNode[que[i].l] << ' ' << getNode[que[i].r] << ' '  << que[i].qtime << ' ' << que[i].utime << ' ' << que[i].lca << endl;

}
