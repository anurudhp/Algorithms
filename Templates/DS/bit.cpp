// update: normal point update
// query: normal point query
/// range update range query: 
void range_update(int val, int a, int b) {
  update(bit1, val, a);
  update(bit1, -val, b+1);
  update(bit2, (a-1)*val, a);
  update(bit2, -b*val ,b+1);
  return;
}
// now it gives sum from 1-idx. 
int pre_sum(int idx) {
  return idx * query(bit1, idx) - query(bit2, idx);
}
