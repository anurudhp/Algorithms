struct node {
	int l, r, val; 
	node() {l = r = val = 0;}
};
int curr, root[N]; 
node seg[4 * N * LOGN];  
void init() {
	curr = 1; seg[curr].l = seg[curr].r = seg[curr].val = 0;
}
// create a new node. 
int nnode(int val, int l, int r) {
	seg[curr].val = val, seg[curr].l = l, seg[curr].r = r;
	return curr++; 		
}
// cur: current_node(along which are we travelling, idx: index to be insert at);
int Insert(int lo, int hi, int cur, int idx, int val) {
	if (idx < lo || idx > hi) return cur; 
	else if (lo == hi) return nnode(val, 0, 0); 
	int mid = (lo + hi) >> 1; 
	int pos = nnode(-1, Insert(lo, mid, seg[cur].l, idx, val), Insert(mid + 1, hi, seg[cur].r, idx, val));
	seg[pos].val = max(seg[seg[pos].l].val, seg[seg[pos].r].val);
	return pos; 
}
int query(int lo, int hi, int pos, int l, int r) {
	if (l <= lo && r >= hi) return seg[pos].val; 
	else if (lo > hi || r < lo || l > hi) return 0; 
	int mid = (lo + hi) >> 1; 
	return max(query(lo, mid, seg[pos].l, l, r), query(mid + 1, hi, seg[pos].r, l, r));
}