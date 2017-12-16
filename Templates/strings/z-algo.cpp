string s; int z[2000010];
void computeZ() {
	int len = s.length(), l = -1, r = -1; z[0] = len;
	for (int i=1; i<len; ++i) {
		z[i]=0;
		if (r > i) z[i] = min(z[i-l],r-i+1);
		while (s[i+z[i]] == s[z[i]]) ++z[i];
		if (i+z[i]-1 > r) r = i+z[i]-1, l = i;
	}
}
