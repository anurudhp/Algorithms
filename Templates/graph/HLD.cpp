int nch = 1; // number of chains. 
int narr; // position var for pos[]. 
int sub[N]; // subtree size. 
int pos[N]; // position of current node in the HLD base array over which the DS is built. 
int chain[N]; // chain no of the current node. 
int CH[N]; // first node of the current chain.
int CP[N]; // node to jump to after this chain is finished. 

void HLD(int v, int p) {
	pos[v] = ++narr;
	chain[v] = nch;
	int big = 0; 
  for(int u: g[v]) { 
		if (u == p) continue; 
		else if(!big) big = u;
		else if(sub[u] > sub[big]) big = u;
	} 
	if(big) HLD(big, v);
  for(int u: g[v]) {
 		if (u == p || u == big) continue; 
		++nch, CH[nch] = u, CP[nch] = v;
    HLD(u, v);
  }
} // query(lo, hi, pos, l, r); 
int query_up(int r, int q) {
	int ans = 0, t;
	while(chain[q] != chain[r]) {
  	t = chain[q];
  	ans += query(1, n, 1, pos[CH[t]], pos[q]);
		q = CP[t];
	}
	ans += query(1, n, 1, pos[r], pos[q]);
	return ans;
} // update_up is similar to query_up. 
