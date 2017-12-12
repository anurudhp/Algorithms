struct node{
  int val , p , arr[LOG] , size , rev , lazy;
  node* l; node* r;
  node(int x = 0){
    val = x; size = 1; rev = lazy = 0; p = rand(); l = r = NULL;
  }
}; node* start;
int get_size(node* cur){ if(cur) return cur->size; return 0; }
void push(node* cur){
  if(!cur) return;
  if(cur->rev){
    if(cur->l) cur->l->rev ^= 1; if(cur->r) cur->r->rev ^= 1;
    swap(cur->l, cur->r); cur->rev = 0;
  } //First reverse then other ADD/XOR etc
}
void update(node* cur){
  if(!cur) return;
  cur->size = get_size(cur->l) + 1 + get_size(cur->r);
  push(cur->l); push(cur->r);
}
void merge(node* &cur, node* x, node* y){
  push(x); push(y);
  if(!x) cur = y; else if(!y) cur = x;
  else if(x->p > y->p){ merge(x->r, x->r, y); cur = x; }
  else{ merge(y->l, x, y->l); cur = y; }
  update(cur);
}
void split(node* cur, node* &L, node* &R, int key, int add = 1){
  if(!cur){ L = R = NULL; return; }
  push(cur); int pos = add + get_size(cur->l);
  if(pos<= key){ split(cur->r, cur->r, R, key, pos + 1); L = cur; }
  else{ split(cur->l, L, cur->l, key, add); R = cur; }
  push(cur); update(cur);
}
void reverse(int x, int y){
  node* A = NULL; node* B = NULL; node* C = NULL;
  split(start, A, B, x-1); split(B, B, C, y - x + 1);
  /*B->rev ^= 1;*/ //Operation on B
  merge(B, B, C); merge(start, A, B);
}//MAIN
for(int i=1; i<=N; ++i){
  node* temp = new node(x);
  if(i == 1) start = temp;
  else merge(start, start, temp);
}