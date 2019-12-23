vector<int> computeZ(string s) {
  vector<int> z(s.size());
	int l = -1, r = -1; z[0] = SZ(s);
	FOR(i,1,SZ(s)) { z[i]=0;
		if (r > i) z[i] = min(z[i-l],r-i+1);
		while (s[i+z[i]] == s[z[i]]) ++z[i];
		if (i+z[i]-1 > r) r = i+z[i]-1, l = i; } 
  return z; }
