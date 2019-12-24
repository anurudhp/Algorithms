vector<int> prefix_function(string s) {
  vector<int> pi(SZ(s));
  FOR(i,1,SZ(s)) { int j = pi[i-1];
    while (j>0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) j++;
    pi[i] = j; }
  return pi; }
void compute_automaton(string s, vector<vector<int>>& aut) {
  s += '#';vector<int> pi = prefix_function(s);
  aut.assign(SZ(s), vector<int>(26));
  FOR(i,0,SZ(s)) {FOR(c,0,26) {
    if (i > 0 && 'a' + c != s[i]) aut[i][c] = aut[pi[i-1]][c];
    else aut[i][c] = i + ('a' + c == s[i]);}}}
