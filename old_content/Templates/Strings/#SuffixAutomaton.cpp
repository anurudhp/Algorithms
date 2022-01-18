//To check substring/LCS, run string on the automaton. 
//Each path in the automaton is a substring 
//(if it ends in a terminal node, it is a suffix)
//To find occurences of a string, run it on the automaton
//and #occurences = no.of.ways to reach a terminal node.
//Or, keep reverse edges of suffix links(all prefixes for that
// substring), and no.of.ways to reach a root, would be the ans
struct SuffixAutomaton { using ADJ = map<char,int>;
  vector<ADJ> edges;
  VI link, length; //length[i]: longest string in i-th class
  int last; // index of equivalence class of whole string
  SuffixAutomaton(string s) {
    edges.PB(ADJ()); link.PB(-1); length.PB(0); last = 0;
    REP(i,SZ(s)) { edges.PB(ADJ()); length.PB(i+1); link.PB(0);
      int r = SZ(edges) - 1, p = last;
      while(p >= 0 && edges[p].find(s[i]) == edges[p].end()) {
        edges[p][s[i]] = r, p = link[p];
      } if(p != -1) {
        int q = edges[p][s[i]];
        if(length[p] + 1 == length[q]) link[r] = q;
        else {
          edges.PB(edges[q]); length.PB(length[p] + 1);
          link.PB(link[q]); int qq = SZ(edges)-1;
          link[q] = qq; link[r] = qq;
          while(p >= 0 && edges[p][s[i]] == q) {
            edges[p][s[i]] = qq, p = link[p];
        } }
      } last = r;
    } VI terminals; 
    for (int p = last; p > 0; p = link[p]) terminals.PB(p);
  }
};
