// computeZ calculates the Z function for the string s and stores it in the array z[].
const int LEN = 2000010;
string s;
int z[LEN];
void computeZ() {
	int len = s.length(), l, r;
	z[0] = len;
	l = r = -1;
	for(int i=1; i<len; ++i) {
		z[i]=0;
		if(r>i) {
			z[i]=min(z[i-l],r-i+1);
		}
		while(s[i+z[i]]==s[z[i]]) ++z[i];
		if(i+z[i]-1 > r) {
			r=i+z[i]-1; l=i;
		}
	}
}