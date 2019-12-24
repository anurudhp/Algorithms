const int SIGMA = 256;
struct node{ // use suff_link, smart_link after copying
  int suf_lnk,len, next[SIGMA], smt_lnk[SIGMA];
  node(){ SET(next,-1); SET(smt_lnk,0); suf_lnk=0;len=0; }
};
struct eertree {
  int rto, rte, n, last; VI s; vector<node> tree;
  eertree(): rto(0), rte(1), n(0), last(1), s(1,-1), tree(2) {
    tree[rto].suf_lnk = tree[rte].suf_lnk = rto;
    tree[rto].len = -1; tree[rte].len=0;
  }
  int add(int c) { s.PB(c); n++;
    if(s[n-tree[last].len-1] != c){ 
      last = tree[last].smt_lnk[c];
    } int flag = (tree[last].next[c] == -1);
    if (flag) {
      int nnode = SZ(tree); tree.PB(node());
      tree[nnode].len=tree[last].len + 2;
      if (tree[nnode].len == 1) {
        tree[nnode].suf_lnk = rte;
      } else {
        tree[nnode].suf_lnk=tree[tree[last].smt_lnk[c]].next[c];
      } if (tree[nnode].len == 1){
        FOR(cc,0,SIGMA){tree[nnode].smt_lnk[cc]=0;}
        tree[nnode].smt_lnk[c]=1;
      } else {
        FOR(cc,0,SIGMA){ int x = tree[nnode].suf_lnk;
          if (s[n-tree[x].len]==cc)tree[nnode].smt_lnk[cc]=x;
          else tree[nnode].smt_lnk[cc]=tree[x].smt_lnk[cc];
        }
      } tree[last].next[c]=nnode;
    } last = tree[last].next[c]; return tree[last].len;
} };
