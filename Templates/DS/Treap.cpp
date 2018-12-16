struct node {//combine function is refresh
  int value,priority,sz,reverse;
  node *left,*right;
}; typedef node* pnode;
int getsz(pnode t) { return t?t->sz:0; }
void refresh(pnode t) { if (!t) return;
  t->sz=getsz(t->left)+getsz(t->right)+1;
} void lazyupdate(pnode t) { if(!t || !t->reverse) return;
  swap(t->left,t->right);
  if(t->left) t->left->reverse^=1 ;
  if(t->right) t->right->reverse^=1 ;
  t->reverse=0; refresh(t);
}void merge(pnode &t,pnode l ,pnode r) {
  lazyupdate(l); lazyupdate(r);
  if(!l || !r) t=(l?l:r);
  else if(l->priority>r->priority) merge(l->right,l->right,r), t=l;
  else merge(r->left,l,r->left), t=r;  refresh(t);
}void split(pnode t,pnode &l,pnode &r,int pos,int add) { lazyupdate(t);
  if(!t) { l=r=t; return; }
  int curr_pos=add+getsz(t->left)+1;
  if(curr_pos<=pos) split(t->right,t->right,r,pos,curr_pos), l=t;
  else split(t->left,l,t->left,pos,add), r=t;
  refresh(t);
} pnode create(int val) { pnode temp=new node();
  temp->priority=rand(); temp->sz=1;
  temp->left=temp->right=NULL; temp->value=val;
  temp->reverse=0; return temp;
} void insert(pnode &t,int pos,int val) { pnode l,r;
  split(t,l,r,pos-1,0); merge(l,l,create(val)); merge(t,l,r);
} void print(pnode &t) { if(!t) return;
  lazyupdate(t); print(t->left);
  cout<<t->value<<" "; print(t->right);
}
