// Values are associated with edges -> Values are associated with child node
for(auto &it:e){
	if(p[it.first.first] == it.first.second) swap(it.first.first, it.first.second);
	val[it.first.second] = it.second;
}
// get_distance from x to y is exclusive of LCA
void hld(int cur, int par, int h = 1){
	pos[cur] = ++timer; back[timer] = cur; head[cur] = h;
	int sc = 0;
	for(auto it:v[cur]) if(it.first != par) if(sub[it.first] > sub[sc]) sc = it.first;
	if(!sc) return; 
	hld(sc, cur, h);
	for(auto it:v[cur]){
		if(it.first == par || it.first == sc) continue;
		hld(it.first, cur, it.first);
	}
}
int get_distance(int x, int y){
	int ans = 0;
	while(head[x] != head[y]){
		if(lev[head[x]] < lev[head[y]]) swap(x, y);
		int l = pos[x]; int r = pos[head[x]];
		if(l > r) swap(l, r);
		ans = max(ans, query(1, N, 1, l, r));
		x = p[head[x]];
	}
	if(x == y) return ans;
	if(lev[x] < lev[y]) swap(x, y);
	int l = pos[x]; int r = pos[y];
	ans = max(ans, query(1, N, 1, min(l, r) + 1, max(l, r)));
	return ans;
}