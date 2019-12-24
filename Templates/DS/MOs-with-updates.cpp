//query = {l, r, id, t} sort by {l/block, r/block, t}
//update = {pos, pre, now} - point update at position
// complexity = O(n^5/3) : set block = n^2/3
REP(i, SZ(q)) {
	while(t < q[i].t) ++t, apply(u[t].pos, u[t].now);
	while(t > q[i].t) apply(u[t].pos, u[t].pre), --t;
	while(r < q[i].r) add(++r);
	while(l > q[i].l) add(--l);
	while(r > q[i].r) remove(r--);
	while(l < q[i].l) remove(l++);
	ans[q[i].id] = ds.get();
}
