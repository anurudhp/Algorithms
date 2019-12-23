struct ahocorasick {//SZ:no of nodes
  vector <int> sufflink,out; 
  vector< map<char, int> > trie;//call findnextstate
  ahocorasick() { 
    out.resize(1); trie.resize(1);
  }
  inline void insert(string &s) { 
    int curr = 0;//clear to reinit
    rep(i,0,sz(s)) {
      if(!trie[curr].count(s[i])) {
        trie[curr][s[i]] = sz(trie); 
        trie.push_back(map<char,int>());
        out.push_back(0);
      } curr = trie[curr][s[i]];
    } ++out[curr];
  } 
  inline void build_automation() { 
    sufflink.resize(sz(trie));
    queue <int> q;
    for(auto x: trie[0]) { 
      sufflink[x.se]=0;
      q.push(x.se);
    } 
    while(!q.empty()) { 
      int curr = q.front(); q.pop();
      for(auto x:trie[curr]) {
        q.push(x.se); int tmp=sufflink[curr];
        while(!trie[tmp].count(x.fi) && tmp) tmp = sufflink[tmp];
        if(trie[tmp].count(x.fi)) sufflink[x.se]=trie[tmp][x.fi];
        else sufflink[x.se]=0;
        out[x.se]+=out[sufflink[x.se]];
      }
    }
  }
  int findNextState(int curr,char ch) {
    while(curr && !trie[curr].count(ch)) curr=sufflink[curr];
    return (!trie[curr].count(ch)) ? 0 :trie[curr][ch];
  } 
  int query(string &s){
    int ans=0; int curr = 0;
    rep(i,0,sz(s)) {
      curr=findNextState(curr,s[i]);
      ans+=out[curr];
    } return ans;
  } 
  void clear() {
    trie.clear(); sufflink.clear(); out.clear();
    out.resize(1); trie.resize(1); 
}};