string s;
int p[100010];
void computeKMP() {
	int len = s.length();
	p[0] = 0;
	for(int i=1; i<len; ++i) {
		int temp = p[i-1];
		while(temp) {
			if(s[i] == s[temp]) {
				p[i] = temp + 1;
				break;
			}
			temp = p[temp - 1];
		}
		if(!temp) p[i] = (s[i] == s[0]);
	}
}