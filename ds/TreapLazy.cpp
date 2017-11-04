// https://www.codechef.com/viewplaintext/9981566

#include<bits/stdc++.h>
using namespace std;
const int LOG = 30;
struct node{
	int val , p , arr[LOG] , size , rev , lazy;
	node* l;
	node* r;
	node(int x = 0){
		val = x;
		size = 1;
		rev = lazy = 0;
		p = rand();
		l = r = NULL;
		for(int i=0; i<LOG; ++i){
			arr[i] = (val>>i) & 1;	
		} 
	}
}; node* start;
int get_size(node* cur){
	if(cur) return cur->size;
	return 0;
}
void print(node* cur){
	if(!cur) return;	
	cout << cur->val << endl;
	print(cur->l);
	print(cur->r);
}
int get_lazy(node* cur){
	if(!cur) return 0;
	return cur->lazy;
}
void push(node* cur){
	if(!cur) return;
	if(cur->rev){
		if(cur->l) cur->l->rev ^= 1;
		if(cur->r) cur->r->rev ^= 1;
		swap(cur->l, cur->r);
		cur->rev = 0;
	}
	if(get_lazy(cur)){
		int temp = get_lazy(cur);
		if(cur->l) cur->l->lazy ^= temp;
		if(cur->r) cur->r->lazy ^= temp;
		cur->val ^= temp;
		for(int i=0; i<LOG; ++i){
			if(temp & 1LL<<i){
				cur->arr[i] = get_size(cur) - cur->arr[i];
			}
		}
		cur->lazy = 0;	

	}
}
int get(node* cur, int pos){
	if(!cur) return 0;
	return cur->arr[pos];
}
void update(node* cur){
	if(!cur) return;
	cur->size = get_size(cur->l) + 1 + get_size(cur->r);
	push(cur->l);
	push(cur->r);
	for(int i=0; i<LOG; ++i){
		cur->arr[i] = get(cur->l, i) + get(cur->r, i) + ((cur->val >> i) & 1);
	}
}
void merge(node* &cur, node* x, node* y){
	push(x);
	push(y);
	if(!x) cur = y;
	else if(!y) cur = x;
	else if(x->p > y->p){
		merge(x->r, x->r, y);
		cur = x;
	}
	else{
		merge(y->l, x, y->l);
		cur = y;
	}
	update(cur);
}
void split(node* cur, node* &L, node* &R, int key, int add = 1){
	if(!cur){
		L = R = NULL; return;
	}
	push(cur);
	int pos = add + get_size(cur->l);
	if(pos<= key){
		split(cur->r, cur->r, R, key, pos + 1);
		L = cur;
	}
	else{
		split(cur->l, L, cur->l, key, add);
		R = cur;
	}
	push(cur);
	update(cur);
}
void query(int x, int y){
	node* A = NULL;
	node* B = NULL;
	node* C = NULL;
	split(start, A, B, x-1);
	split(B, B, C, y - x + 1);
	int ans = 0;
	assert(B);
	for(int i=0; i<LOG; ++i) ans += B->arr[i];
	printf("%d\n", ans);
	merge(B, B, C);
	merge(start, A, B);
}
void reverse(int x, int y){
	node* A = NULL;
	node* B = NULL;
	node* C = NULL;
	split(start, A, B, x-1);
	split(B, B, C, y - x + 1);
	B->rev ^= 1;
	merge(B, B, C);
	merge(start, A, B);
}
void lazy(int x, int y, int z){
	node* A = NULL;
	node* B = NULL;
	node* C = NULL;
	split(start, A, B, x-1);
	split(B, B, C, y - x + 1);
	assert(B);
	B->lazy ^= z;
	merge(B, B, C);
	merge(start, A, B);
}
int main(){
	int N;
	scanf("%d", &N);
	for(int i=1; i<=N; ++i){
		int x; 
		scanf("%d", &x);
		node* temp = new node(x);
		if(i == 1) start = temp;
		else merge(start, start, temp);		
	}
	int Q;
	cin >> Q;
	for(int i=1; i<=Q; ++i){
		int t, x , y; 
		scanf("%d%d%d", &t, &x, &y);
		if(t == 1) query(x,y);
		else if(t == 2)	reverse(x,y);
		else{
			int z;
			scanf("%d", &z);
			lazy(x,y,z);
		}
	}
}