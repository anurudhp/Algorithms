/* Author: Anurudh Peduri (codelegend) */

struct SegmentTree {
  int sz;
  // declare tree variables

  void split(int node, int x, int y) {
    // lazy propagation
  }
  void merge(int node, int x, int y) {
    // compute value of node, from children
  }

  SegmentTree(int n) {
    for (sz = 1; sz < n; sz <<= 1)
      ;
    // initialize tree
  }

  // void func(int l, int r, /*...args, */ int node = 1, int x = 0, int y = -1)
  // {
  //   if (l >= y || r <= x) return;
  //   if (l <= x && y <= r) {
  //     // process node, and return value
  //   }
  //   split(node, x, y);
  //   func(l, r, 2 * node, x, (x + y) / 2);
  //   func(l, r, 2 * node + 1, (x + y) / 2, y);
  //   merge(node, x, y);
  // }
};
