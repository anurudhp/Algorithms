// Aho-corasick

// Implemetation 1

const int MAXN = 404, MOD = 1e9 + 7, sigma = 26;
 
int cnt[MAXN], term[MAXN], len[MAXN], to[MAXN][sigma], link[MAXN], sz = 1;
void add_str(string s)
{
	int cur = 0;
	for(auto c: s)
	{
		if(!to[cur][c - 'a'])
		{
			to[cur][c - 'a'] = sz++;
			len[to[cur][c - 'a']] = len[cur] + 1;
		}
		cur = to[cur][c - 'a'];
	}
	term[cur] = cur; 
}
 
void push_links()
{
	int que[sz];
	int st = 0, fi = 1;
	que[0] = 0;
	while(st < fi)
	{
		int V = que[st++];
		int U = link[V];
		if(!term[V]) term[V] = term[U];
		for(int c = 0; c < sigma; c++)
			if(to[V][c])
			{
				link[to[V][c]] = V ? to[U][c] : 0;
				que[fi++] = to[V][c];
			}
			else
			{
				to[V][c] = to[U][c];
			}
	}
}

void go(string &s){
	int x = 0;
	s+=’$’;
	for(auto &c: s) {
		while(1){
			if(to[x].count(c)) {
				x=to[x][c];
				break;
			}
			if(!x) {
				break;
			}
			x = link[x];
		}
		cnt[x]++;
	}
}

// Implementation 2

const int MAXN = 1e6 + 42;
 
map<char, int> to[MAXN];
int cnt[MAXN], link[MAXN], que[MAXN], sz = 1;
 
void add_str(string s, int k)
{
	int v = 0;
	for(auto c: s)
	{
		if(!to[v][c]) to[v][c] = sz++;
		v = to[v][c];
	}
}
 
void push_links()
{
	link[0] = -1;
	int st = 0, fi = 1;
	que[0] = 0;
	while(st < fi)
	{
		int v = que[st++];
		for(auto it: to[v])
		{
			int u = it.second;
			int c = it.first;
			int j = link[v];
			while(j != -1 && !to[j][c]) j = link[j];
			if(j != -1) link[u] = to[j][c];
			que[fi++] = u;
		}
	}
}

void go(string &s){
	int x = 0;
	s+=’$’;
	for(auto &c: s) {
		while(1){
			if(to[x].count(c)) {
				x=to[x][c];
				break;
			}
			if(!x) {
				break;
			}
			x = link[x];
		}
		cnt[x]++;
	}
}