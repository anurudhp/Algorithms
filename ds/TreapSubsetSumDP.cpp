// https://www.codechef.com/viewplaintext/13723886

#include <bits/stdc++.h>
using namespace std;
struct node{
	node* l;
	node* r;
	int frq[15], size, rev, p, val;
	node(int v){
		l = r = NULL;
		size = 1;
		p = rand();	
		rev = 0;
		for(int i=0; i<15; ++i) frq[i] = 0;
		frq[v] = 1;
		val = v;
	}
}; node* start;

const int MAX = 1e5 + 5;
int N, Q, cnt = 0, orr[15], c[MAX];
map<int, int> MAP;
vector<int> v;
bitset<MAX> dp;

int get_size(node* cur){
	if(!cur) return 0;
	return cur->size;
}
int get(node* cur, int idx){
	if(!cur) return 0;
	return cur->frq[idx];
}
void push(node* cur){
	if(!cur) return;
	if(cur->rev){
		if(cur->l) cur->l->rev ^= 1;
		if(cur->r) cur->r->rev ^= 1;
		swap(cur->l, cur->r);
		cur->rev = 0;
	}
}
void update(node* cur){
	if(!cur) return;
	cur->size = get_size(cur->l) + 1 + get_size(cur->r);
	push(cur->l);
	push(cur->r);
	for(int i=0; i<15; ++i){
		cur->frq[i] = get(cur->l, i) + get(cur->r, i);
	}
	++cur->frq[cur->val];
}
void merge(node* &cur, node* x, node* y){
	push(x); push(y);
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
		L = R = NULL;
		return;	
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

int solve(int W){
	v.clear();
	dp.reset();
	for(int i=1; i<=W; ++i){
		if(c[i] == 0) continue;
		if(c[i] & 1){
 			--c[i];
 			v.push_back(i);
 		}
 		else{
 			--c[i]; --c[i];
 			v.push_back(i); v.push_back(i);
 		}
 		int temp = (i << 1);
 		int inc = (c[i] >> 1);
 		if(temp <= W) c[temp] += inc;
	}
	dp.set(0);
	for(auto it:v) dp |= (dp << it);
	return dp.test(W);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> Q;
	for(int i=1; i<=N; ++i){
		int w, ww; cin >> w; ww = w;
		if(MAP.find(w) == MAP.end()) MAP[w] = ++cnt;
		w = MAP[w];
		orr[w] = ww;
		node* cur = new node(w);
		if(i == 1) start = cur;
		else merge(start, start, cur);
	}
	for(int i=1; i<=Q; ++i){
		int ty; cin >> ty;
		if(ty == 1){
			int pos, w, ww; cin >> pos >> w; ww = w;
			if(MAP.find(w) == MAP.end()) MAP[w] = ++cnt;
			w = MAP[w];
			orr[w] = ww;

			node* A = NULL;
			node* B = NULL;
			node* C = NULL;

			split(start, A, B, pos - 1);
			split(B, B, C, 1);

			assert(get_size(B) == 1);
			B->frq[B->val] = 0;

			B->val = w;
			B->frq[B->val] = 1;

			merge(start, A, B);
			merge(start, start, C);
		}	
		else if(ty == 2){
			int l, r; cin >> l >> r;
			node* A = NULL;
			node* B = NULL;
			node* C = NULL;
			split(start, A, B, l - 1);
			split(B, B, C, r - l + 1);
			B->rev ^= 1;
			merge(B, B, C);
			merge(start, A, B);
		}	
		else{
			int l, r, w; 
			cin >> l >> r >> w;
			node* A = NULL;
			node* B = NULL;
			node* C = NULL;

			split(start, A, B, l - 1);
			split(B, B, C, r - l + 1);

			assert(B);

			memset(c, 0, sizeof c);
			for(int i=0; i<15; ++i){
				if(B->frq[i]){
					int val = orr[i];
					if(val) c[val] += B->frq[i];
				}
			}

			bool yes = solve(w);
			if(yes) cout << "Yes\n";
			else cout << "No\n";

			merge(start, A, B);
			merge(start, start, C);
		}
	}
}