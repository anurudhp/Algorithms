vector<int> prefix_function(string s) {
  vector<int> pi(SZ(s));
  FOR(i,1,SZ(s)) { int j = pi[i-1];
    while (j>0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) j++;
    pi[i] = j; }
  return pi; }
