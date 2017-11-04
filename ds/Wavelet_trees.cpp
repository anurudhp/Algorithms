#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;

int N, M, A[MAX], back[MAX];
vector<int> s[MAX * 4], v[MAX * 4], arr;
map<int, int> MAP;

void build(int low, int high, int node){
	int parent = node >> 1;
	for(auto it:s[parent]){
		if(it >= low and it <= high) s[node].push_back(it);
	}

	if(low == high) return;

	int mid = (low + high) >> 1;
	
	if(s[node].size()){
		if(s[node][0] > mid) v[node].push_back(0);
		else v[node].push_back(1);
		for(int i=1; i<s[node].size(); ++i){
			if(s[node][i] > mid) v[node].push_back(v[node].back());
			else v[node].push_back(v[node].back() + 1);			
		}
	}
	else return;

	build(low, mid, node << 1);
	build(mid + 1, high, 1 | node << 1);
}

int query(int low, int high, int node, int l, int r, int rank){

	if(low == high) return low;

	int mid = (low + high) >> 1, new_l = 0, new_r = 0, to_l = 0, to_r = 0;

	to_l = v[node][r];
	if(l) to_l = to_l - v[node][l - 1];

	to_r = r - l + 1 - to_l;

	if(to_l >= rank){
		if(l) new_l = v[node][l - 1];
		new_r = new_l + to_l - 1;
		return query(low, mid, node << 1, new_l, new_r, rank);
	}
	else{
		if(l) new_l = l - v[node][l - 1];
		new_r = new_l + to_r - 1;
		return query(mid + 1, high, 1 | node << 1, new_l, new_r, rank - to_l);
	}
}

void compress(){
	for(int i=1; i<=N; ++i) arr.push_back(A[i]);
	sort(arr.begin(), arr.end());
	int c = 0;
	for(auto it:arr){
		if(MAP.find(it) == MAP.end()) MAP[it] = ++c;
	}
	for(int i=1; i<=N; ++i){
		int v = MAP[A[i]];
		back[v] = A[i];
		A[i] = v;
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	cin >> N >> M;
	for(int i=1; i<=N; ++i) cin >> A[i];

	compress();

	int mid = (1 + MAX) >> 1;

	for(int i=1; i<=N; ++i) s[1].push_back(A[i]);

	if(s[1][0] > mid) v[1].push_back(0);
	else v[1].push_back(1);

	for(int i=1; i<N; ++i){
		if(s[1][i] > mid) v[1].push_back(v[1].back());
		else v[1].push_back(v[1].back() + 1);
	}

	build(1, mid, 2);
	build(mid + 1, MAX, 3);
	
	while(M--){
		int L, R, K; cin >> L >> R >> K;
		--L; --R;
		cout << back[query(1, MAX, 1, L, R, K)] << endl;
	}

	return 0;
}