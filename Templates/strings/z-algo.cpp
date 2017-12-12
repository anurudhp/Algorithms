// Z Algo

// computeZ calculates the Z function for the string s and stores it in the array z[].

#include<bits/stdc++.h>
#define fr(x) scanf("%d",&x)
using namespace std;

const int LEN = 2000010;

string s;
int z[LEN];

void computeZ() {
	int len, l, r;
	len = s.length();
	z[0] = len;
	l = r = -1;
	for(int i=1; i<len; ++i) {
		z[i]=0;
		if(r>i) {
			z[i]=min(z[i-l],r-i+1);
		}
		while(s[i+z[i]]==s[z[i]]) ++z[i];
		if(i+z[i]-1 > r) {
			r=i+z[i]-1;
			l=i;
		}
	}
}

char temps[1000010];
int main(){
	int t;
	fr(t);
	string a, b;
	vector<int> ans;
	while(t--) {
		ans.clear();
		scanf(" %s", temps);
		b = string(temps);
		scanf(" %s", temps);
		a = string(temps);
		s = a + '$' + b;
		computeZ();
		for(int i=a.length(); i<s.length(); ++i) {
			if(z[i] == a.length()) {
				ans.push_back(i - a.length());
			}
		}
		if(ans.size()) {
			printf("%d\n", ans.size());
			for(auto&z2: ans) {
				printf("%d ", z2);
			}
			puts("");
		}
		else {
			printf("Not Found\n");
		}
	}
}
