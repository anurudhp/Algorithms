const int SIGMA = 256;
struct node{
  int suff_link,len;
  int next[SIGMA];
  int smart_link[SIGMA];
  node(){
    SET(next,-1);
    SET(smart_link,0);
    suff_link=0;len=0;
  }
};
struct eertree{
  int rto,rte;
  vector<node> tree;
  vector<int> s;int n;
  int last;
  eertree(){
    FOR(_i, 0,2){tree.EB(node());}
    rto=0;rte=1;s.assign(1,-1);n=0;
    tree[rto].suff_link = tree[rte].suff_link = rto;
    tree[rto].len = -1;tree[rte].len=0;
    last=rte;
  }
  int add(int c){
    s.EB(c);n++;
    if(s[n-tree[last].len-1]!=c){
      last=tree[last].smart_link[c];
    }
    int flag=(tree[last].next[c]==-1);
    if(flag){
      int nnode=tree.size();
      tree.EB(node());
      tree[nnode].len=tree[last].len+2;
      if(tree[nnode].len==1)tree[nnode].suff_link = rte;
      else tree[nnode].suff_link=tree[tree[last].smart_link[c]].next[c];
      if(tree[nnode].len==1){
        FOR(cc,0,SIGMA){tree[nnode].smart_link[cc]=0;}
        tree[nnode].smart_link[c]=1;
      }else{
        FOR(cc,0,SIGMA){
          int x=tree[nnode].suff_link;
          if(s[n-tree[x].len]==cc)tree[nnode].smart_link[cc]=x;
          else tree[nnode].smart_link[cc]=tree[x].smart_link[cc];
        }
      }
      tree[last].next[c]=nnode;
    }
    last = tree[last].next[c];
    return tree[last].len;
  }
}mytree;
