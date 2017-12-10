// AUX has vertices in form {start[vertex], vertex}
// start[i], en[i] -> according to dfs order
// tree[] is final adjacency list
int build(){
	sort(aux.begin(), aux.end()); int len = aux.size();
	for(int i=1; i<len; ++i){
		int x = LCA(aux[i].second, aux[i - 1].second);
		aux.push_back({start[x], x});
	}
	for(auto it:aux) is[it.second] = 0;
	vector<pair<int, int> >temp; temp.clear();
	for(auto it:aux){
		if(is[it.second]) continue;
		temp.push_back(it); is[it.second] = 1;
	}
	aux.clear();
	for(auto it:temp) aux.push_back(it), is[it.second] = 0;
	sort(aux.begin(), aux.end()); root = aux[0].second;
	for(auto it:aux) tree[it.second].clear();
	stack<int> s; s.push(aux[0].second);
	for(int i=1; i<aux.size(); ++i){
		int cur = aux[i].second;
		while(true){
			if(en[s.top()] < start[cur]) s.pop();
			else break;
		}
		tree[s.top()].push_back(cur); s.push(cur);
	}
	return root;
}