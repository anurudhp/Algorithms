void range_update(int val, int a, int b) {// range update range query
  update(bit1, val, a); update(bit1, -val, b+1);
  update(bit2, (a-1)*val, a); update(bit2, -b*val ,b+1); }
int pre_sum(int idx) {// now it gives sum from 1-idx. 
  return idx * query(bit1, idx) - query(bit2, idx); }
