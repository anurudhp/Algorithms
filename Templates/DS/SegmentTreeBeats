//sample problem(for eg. below) - range sum query and 2 range updates(i=l...r): a[i] = a[i] % x and a[i] = x
//break_condition - when can we break eg. (l > rr || r < ll || max_value[node] < x)
//tag_condition - when can we put tag for lazy update eg. (l >= ll && r <= rr && max_value[node] == min_value[node])
void modify(int node, int l, int r, int ll, int rr) {
  if (break_condition()) return;
  if (tag_condition()) {puttag(node); return;}
  pushdown(node);
  int mid = (l + r) >> 1;
  modify(node * 2, l, mid, ll, rr);
  modify(node * 2 + 1, mid + 1, r, ll ,rr);
  update();
}
