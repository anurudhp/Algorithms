// To check substring/LCS, run the string on the automaton. Each path in the automaton is a substring(if it ends in a terminal node, it is a suffix)
// To find occurences of a string, run it on the automaton, and the number of its occurences would be number of ways to reach a terminal node.
// Or, we can keep reverse edges of suffix links(all prefixes for that substring), and number of ways to reach a root, would be the answer(can be used to print all answers)
struct SuffixAutomaton {
  vector<map<char,int>> edges;
  vector<int> link, length;
  // length[i]: longest string in i-th class
  int last; // index of equivalence class of whole string

  SuffixAutomaton(string s) {
    edges.push_back(map<char,int>());
    link.push_back(-1); length.push_back(0);
    last = 0;

    for(int i=0;i<s.size();i++) {
      edges.push_back(map<char,int>());
      length.push_back(i+1);
      link.push_back(0);
      int r = edges.size() - 1;
      int p = last;
      while(p >= 0 && edges[p].find(s[i]) == edges[p].end())
        edges[p][s[i]] = r, p = link[p];
      if(p != -1) {
        int q = edges[p][s[i]];
        if(length[p] + 1 == length[q]) link[r] = q;
        else {
          edges.push_back(edges[q]);
          length.push_back(length[p] + 1);
          link.push_back(link[q]);
          int qq = edges.size()-1;
          link[q] = qq; link[r] = qq;
          while(p >= 0 && edges[p][s[i]] == q)
            edges[p][s[i]] = qq, p = link[p];
        }
      }
      last = r;
    }
    vector<int> terminals; int p = last;
    while(p > 0) terminals.push_back(p), p = link[p];
  }
};
