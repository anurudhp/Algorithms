// 2-SAT

// Set value for NODES, then call add_impl etc. depending on use case.
// Then, call dfs1, dfs2 and in the end, iterate over topo_sort order using the loop at the end of main.

#include <bits/stdc++.h>
#define fr(x) scanf("%d", &x)
using namespace std;

const int NODES = 2*100010;

vector<int> revadj[NODES], adj[NODES], top_sort, working;
int marked[NODES];
stack<int> finishing;
int comp[NODES], c = 0;

void add_impl(int v1, int v2) {
	adj[v1].push_back(v2); revadj[v2].push_back(v1);
}
void add_equiv(int v1, int v2) {
	add_impl(v1, v2);add_impl(v2, v1);
}
void add_or(int v1, int v2) {
	add_impl(1^v1, v2);add_impl(1^v2, v1);
}
void add_xor(int v1, int v2) {
	add_or(v1, v2);add_or(1^v1, 1^v2);
}
void add_true(int v1) {
	add_impl(1^v1, v1);
}
void add_and(int v1, int v2) {
	add_true(v1);add_true(v2);
}

void dfs1(int v) {
	marked[v] = true;
	for (auto i: adj[v]){
		if (marked[i] == 0){
			dfs1(i);
		}
	}
	top_sort.push_back(v);
	finishing.push(v);
}

void dfs2(int v) {
	marked[v] = true;
	for (auto i: revadj[v]){
		if (marked[i] == 0){
			dfs2(i);
		}
	}
	comp[v] = c;
}

vector<int> v[100010];
int main() {
	// Problem Specific Code
	int n, m;
	fr(n);
	fr(m);
	for(int i=1; i<=n; ++i){
		int l;
		fr(l);
		while(l--) {
			int temp;
			fr(temp);
			v[i].push_back(temp);
		}
	}
	for(int i=2; i<=n; ++i) {
		int same = 1;
		for(int j=0; j<min(v[i].size(), v[i-1].size()); ++j) {
			if(v[i][j] != v[i-1][j]) {
				same = 0;
				if(v[i][j] > v[i-1][j]) {
					add_or(((2*v[i-1][j])), (1^(2*v[i][j])));
				}
				else {
					add_true(1^(2*v[i][j]));
					add_true((2*v[i-1][j]));
				}
				break;
			}
		}
		if(same) {
			if(v[i-1].size() > v[i].size()) {
				printf("No\n");
				return 0;
			}
		}
	}
	// From here, the 2 SAT specific code starts
	for(int i=2; i<=(2*m+1); ++i){
		if(!marked[i]){
			dfs1(i);
		}
	}
	memset(marked, 0, sizeof marked);
	while(finishing.size()) {
		if(!marked[finishing.top()]){
			c++;
			dfs2(finishing.top());
		}
		finishing.pop();
	}
	for(int i=2; i<=(2*m+1); ++i) {
		if(comp[i] == comp[i^1]) {
			printf("No\n");
			return 0;
		}
	}
	memset(marked, 0, sizeof marked);
	for(auto &z: top_sort){
		if(marked[z>>1] == 0) {
			marked[z>>1] = 1;
			if((z & 1) == 0) working.push_back(z>>1);
		}
	}
	printf("Yes\n%d\n", working.size());
	for(auto &z: working) {
		printf("%d ", z);
	}
	return 0;
}