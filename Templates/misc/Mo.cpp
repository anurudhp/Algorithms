// query(u, v) and ST[u]<=ST[v], if LCA is u, [ST(u), ST(v)]
// else [EN(u), ST(v)] + [ST(u), ST(u)](LCA). node which lies on path occurs odd no. of times.
bool compare(query &x, query &y){
	if(x.l / BLOCK == y.l / BLOCK){
		if(x.r / BLOCK == y.r / BLOCK){
			return x.utime < y.utime;
		} return x.r / BLOCK < y.r / BLOCK;
	} return x.l / BLOCK < y.l / BLOCK;
} int l = 0, r = -1, T = 1;
for(int i=1; i<X; ++i){
	query &q = que[i];
	while(q.l < l) move(--l); while(r < q.r) move(++r);
	while(l < q.l) move(l++); while(q.r < r) move(r--);
	while(T < q.utime) refresh(T++); while(q.utime < T) refresh(--T);
}
