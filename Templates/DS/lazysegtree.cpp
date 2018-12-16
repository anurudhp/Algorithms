// This lazy update means if parent's is lazy tag 
// is set then child's value and lazy tag needs to be updated
// and parent is already updated
void build(int low, int high, int pos) {
	if (low == high) {
		seg[pos] = arr[low];
		return;
	}
	int mid = (low + high) >> 1;
	build(low, mid, 2 * pos);
	build(mid + 1, high, 2 * pos + 1);
	seg[pos] = seg[2 * pos] + seg[2 * pos + 1];
	return;
}
void split(int low, int high, int pos) {
	if (low != high) {
		int mid = (low + high) >> 1;
		// propagate lazy to children 
		seg[2 * pos] = (mid - low + 1) - seg[2 * pos]; 
		seg[2 * pos + 1] = (high - mid) - seg[2 * pos + 1];
		lazy[2 * pos] = 1 - lazy[2 * pos];
		lazy[2 * pos + 1] = 1 - lazy[2 * pos + 1];
	}
	lazy[pos] = 0;
	return;
}
int query(int low, int high, int pos, int l, int r) {
	if (lazy[pos]) split(low, high, pos);	
	if (low	> high || l > high || r < low) return 0;
	else if(l <= low && r >= high) return seg[pos];
	int mid = (low + high) >> 1;
	return query(low, mid, 2 * pos, l, r) + query(mid + 1, high, 2 * pos + 1, l, r);
}
void update(int low, int high, int pos, int l, int r) {
	if (lazy[pos]) split(low, high, pos);
	if (low > high || l > high || r < low) return;
	else if(l <= low && r >= high) {
		seg[pos] = (high - low + 1) - seg[pos]; // update current. 
		lazy[pos] = 1 - lazy[pos];
		return;
	}
	int mid = (low + high) >> 1;
	update(low, mid, 2 * pos, l, r); 
	update(mid + 1, high, 2 * pos + 1, l, r);
	seg[pos] = seg[2 * pos] + seg[2 * pos + 1];
	return;
}