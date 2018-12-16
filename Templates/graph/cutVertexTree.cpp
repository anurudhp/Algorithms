vector <int> g[N], cutVtree[N], st;	//g[v]: edge-list, Take N = 2 * required:)
int a[N], b[N], compNo[N], col[N], low[N], in[N], L[N], extra[N], tim, C;
bool cutV[N]; // true for cut-vertices.
int adj(int u, int i) {
	return a[i] ^ b[i] ^ u;
}  
void dfs(int v) {
	int ch = 0;
	low[v] = in[v] = T++;
	for(int e: g[v]) {
		int u = adj(v, e);
		if (in[u] == -1) {
			L[u] = L[v] + 1, st.push_back(e), dfs(u);
			low[v] = min(low[v], low[u]);
			if (in[v] == 0 || low[u] >= in[v]) {
				if (in[v]||ch) cutV[v] = true;
				++C;
				while(sz(st)) {
					int ed = st.back();
					col[ed] = C, st.pop_back();
					if (ed == e) break;
				}
			}
		} else if (L[u] < L[v] - 1) { // back-edge.
			low[v] = min(low[v], in[u]), st.push_back(e);
		}
		++ch;
	}
	return;
}  
void run(int n) {
	SET(in, -1); st.resize(0); C = 0;
	rep(i, 1, n + 1) if (in[i] == -1) T = 0, dfs(i);
} 
void build_tree(int n) {
	run(n);
	vector < int > temp;
	SET(extra, -1);
	rep(i, 1, n + 1) {
		temp.clear();
		for(int e: g[i]) {
			temp.push_back(col[e]);
	    }
	    sort(all(temp));
	    temp.erase(unique(all(temp)), temp.end());
	    if (temp.empty()) {
	    	compNo[i] = C + i, extra[C + i] = 0;
	    } else if (sz(temp) == 1) { // belongs to only 1 component.
	    	compNo[i] = temp[0], extra[temp[0]] = 1;
	    } else { // cutVertex
	    	compNo[i] = C + i, extra[C + i] = 0;
	    	for(int u: temp) {
	    		extra[u] = 0;
	    		cutVtree[C + i].push_back(u);
	    		cutVtree[u].push_back(C + i);
	    	}
	    }
	}
	return;
} 