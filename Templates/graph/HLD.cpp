int nch = 1, narr, sub[N], pos[N], chain[N], CH[N], CP[N]; 
// nch: number of chains, narr: position var for pos[]. 
// pos: position in basearray, CH: first node of curr chain
// CP: jump node after chain finished. 
void HLD(int v, int p) {
	pos[v] = ++narr, chain[v] = nch;
	int big = 0; 
  	for(int u: g[v]) { 
		if (u == p) continue; 
		else if(!big) big = u;
		else if(sub[u] > sub[big]) big = u;
	} if(big) HLD(big, v);
  	for(int u: g[v]) {
 		if (u == p || u == big) continue; 
		++nch, CH[nch] = u, CP[nch] = v;
    	HLD(u, v); }} // query(lo, hi, pos, l, r); 
int query_up(int r, int q) {
	int ans = 0, t;
	while(chain[q] != chain[r]) {
  		t = chain[q]; 
  		ans += query(1, n, 1, pos[CH[t]], pos[q]);
		q = CP[t];
	} ans += query(1, n, 1, pos[r], pos[q]);
	return ans;}
