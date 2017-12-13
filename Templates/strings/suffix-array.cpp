// Call computeSA, it will calculate suffix array in sa[], position of suffix i...n in sa[] in pos[]
// and sparse table in tree[][].
// Query lcp for suffix i...n and j...n using calcLCP(i, j)
const int LEN = 100020, LOGLEN = 20;
char s[LEN];
int pos[LEN], sa[LEN], ra[2*LEN], temp[LEN], tree[LOGLEN][LEN], val[LEN], msb[LEN];

void computeSA() {
	int len, k;
	len=strlen(s);
	for(int mx=0, i=0;i<len;i++) {
		if(i>=(1<<(mx+1)))
			++mx;
		msb[i]=mx;
	}
	for(int i=0; i<(len<<1); ++i) {
		ra[i] = -1;
	}
	for(int i=0; i<len; ++i) {
		sa[i] = i;
		ra[i] = s[i];
	}
	k = 0;
	sort(sa, sa+len, [](int a,int b) {
		return ra[a]<ra[b];
	});
	k=1;
	while(k<len) {
		sort(sa, sa+len, [k](int a,int b) {
			return (ra[a]==ra[b])?(ra[a+k]<ra[b+k]):(ra[a]<ra[b]);
		});
		temp[sa[0]] = 1;
		for(int i=1; i<len; ++i){
			if(ra[sa[i]]==ra[sa[i-1]]&&ra[sa[i]+k]==ra[sa[i-1]+k]) temp[sa[i]]=temp[sa[i-1]];
			else temp[sa[i]]=temp[sa[i-1]]+1;
		}
		for(int i=0; i<len; ++i) ra[i]=temp[i];
		k<<=1;
	}
	for(int i=0; i<len; ++i) {
		pos[sa[i]] = i;
	}
	for(int i=0, l=0; i<len; ++i) {
		if(pos[i]==0) {
			l=0;
			continue;
		}
		while(s[i+l] == s[sa[pos[i]-1]+l]) l++;
		tree[0][pos[i]] = pos[i];
		val[pos[i]] = l;
		l = max(0, l-1);
	}
	for(int j = 1; j < LOGLEN; j++) {
		for(int i = 0; i + (1 << j) - 1 < len; i++) {
			if(val[tree[j - 1][i]] < val[tree[j - 1][i + (1 << (j - 1))]]) {
				tree[j][i] = tree[j-1][i];
			}
			else {
				tree[j][i] = tree[j-1][i + (1 << (j - 1))];
			}
		}
	}
}

int query(int a, int b) {
	int k=msb[b-a+1];
	if(val[tree[k][a]] < val[tree[k][b-(1<<k)+1]]) {
		return tree[k][a];
	}
	else return tree[k][b-(1<<k)+1];
}

int calcLCP(int l, int r) {
	return val[query(min(pos[l], pos[r])+1, max(pos[l], pos[r]))];
}

int main(){
	int t, len;
	long long ans;
	fr(t);
	while(t--){
		scanf(" %s",&s);
		len=strlen(s);
		computeSA();
		ans = len;
		for(int i=1; i<len; ++i) {
			ans+=calcLCP(0, i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}