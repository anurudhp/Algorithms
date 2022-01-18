struct ahocorasick { VI sufflink, out; 
  vector< map<char, int> > trie;
  ahocorasick(): out(1), trie(1) {}
  inline void insert(string &s) { int curr = 0;
    FOR(i,0,SZ(s)) {
      if(!trie[curr].count(s[i])) {
        trie[curr][s[i]] = SZ(trie); 
        trie.push_back(map<char,int>());
        out.push_back(0);
      } curr = trie[curr][s[i]];
    } ++out[curr];
  } inline void build_automation() { queue<int> q;
    sufflink.resize(SZ(trie));
    for(auto x: trie[0]) { sufflink[x.ND]=0; q.push(x.ND); } 
    while(!q.empty()) { 
      int curr = q.front(); q.pop();
      for(auto x:trie[curr]) {
        q.push(x.ND); int tmp=sufflink[curr];
        while(!trie[tmp].count(x.ST) && tmp) tmp = sufflink[tmp];
        if(trie[tmp].count(x.ST)) sufflink[x.ND]=trie[tmp][x.ST];
        else sufflink[x.ND]=0;
        out[x.ND]+=out[sufflink[x.ND]];
      }
    }
  } int findNextState(int curr, char ch) {
    while(curr && !trie[curr].count(ch)) curr=sufflink[curr];
    return (!trie[curr].count(ch)) ? 0 : trie[curr][ch];
  } int query(string &s){ int ans=0; int curr = 0;
    FOR(i,0,SZ(s)) {
      curr = findNextState(curr, s[i]);
      ans += out[curr];
    } return ans;
  }
};