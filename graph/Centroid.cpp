// http://codeforces.com/gym/100570/problem/F

#include<bits/stdc++.h>
#define int long long int
using namespace std;
const int MAXN = 1e5 + 5;
int size[MAXN], answer[MAXN], h[MAXN], done[MAXN];
int tot = 0;
vector<int> parent, nodes, distanc;
vector<pair<int,int> > qr[MAXN], v[MAXN];
int N, Q;
void dfs_size(int cur, int par){
	size[cur] = 1;
	++tot;
	for(auto it:v[cur]){
		if(it.first != par && done[it.first] == 0){
			dfs_size(it.first, cur);
			size[cur] += size[it.first];
		}
	}
}
int find(int cur, int par){
	for(auto it:v[cur]){
		if(done[it.first] || it.first == par) continue;
		if(size[it.first] > (tot >> 1)) return find(it.first, cur);
	}
	return cur;
}
void dfs_parent(int cur, int par, int dis){
	h[cur] = dis;
	parent.push_back(dis);
	for(auto it:v[cur]){
		if(done[it.first] || it.first == par) continue;
		dfs_parent(it.first, cur, dis + it.second);
	}
}
void dfs_child(int cur, int par, int dis){
	distanc.push_back(dis);
	nodes.push_back(cur);
	for(auto it:v[cur]){
		if(done[it.first] || it.first == par) continue;
		dfs_child(it.first, cur, dis + it.second);
	}
}
void decompose(int cur){
	tot = 0;
	dfs_size(cur, 0);
	cur = find(cur, 0);
	parent.clear();
	dfs_parent(cur, 0, 0);
	sort(parent.begin(), parent.end());
	for(auto q:qr[cur]){
		answer[q.second] += upper_bound(parent.begin(), parent.end(), q.first) - parent.begin();
	}
	done[cur] = 1;
	for(auto it:v[cur]){
		if(done[it.first]) continue;
		nodes.clear();
		distanc.clear();
		dfs_child(it.first, cur, it.second);
		sort(distanc.begin(), distanc.end());
		for(auto node:nodes){
			for(auto q:qr[node]){
				answer[q.second] += upper_bound(parent.begin(), parent.end(), q.first - h[node]) - parent.begin();
				answer[q.second] -= upper_bound(distanc.begin(), distanc.end(), q.first - h[node]) - distanc.begin();
			}
		}
	}
	for(auto it:v[cur]){
		if(done[it.first]) continue;
		decompose(it.first);
	}
}
main(){
	cin >> N >> Q;
	for(int i=1; i<N; ++i){
		int x, y, z;
		cin >> x >> y >> z;
		v[x].push_back({y, z});
		v[y].push_back({x, z});
	}
	for(int i=1; i<=Q; ++i){
		int node, val;
		cin >> node >> val;
		qr[node].push_back({val, i});
	}
	decompose(1);
	for(int i=1; i<=Q; ++i) cout << answer[i] << endl;
}