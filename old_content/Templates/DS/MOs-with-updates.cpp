//query = {l, r, id, t} sort by {l/block, r/block, t}
//update = {pos, pre, now} - point update at position
// complexity = O(n^5/3) : set block = n^2/3
FOR(i, 0, SZ(q)) {
  while(t < q[i].t) ++t, apply(u[t].pos, u[t].now);
  while(t > q[i].t) apply(u[t].pos, u[t].pre), --t;
  while(l > q[i].l) {add(--l);} while(l < q[i].l) {remove(l++);}
  while(r < q[i].r) {add(++r);} while(r > q[i].r) {remove(r--);} 
  ans[q[i].id] = get();
}
