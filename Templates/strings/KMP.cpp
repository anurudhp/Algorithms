namespace kmp {
  const int N=250005;
  int lps[N],ind[N];
  void compute(string p) {//lps represents
    int i=1,j=0; lps[0]=0;//longest length
    while(i<sz(p)) {
      if(p[i]==p[j]) lps[i]=j+1,i++,j++;
      else { if(j) j=lps[j-1];
	else lps[i++]=0;
      }}}
  void KMP(string t, string p) {
    compute(p); if(sz(p)>sz(t)) return; int i=0,j=0;
    while(i<sz(t)) {//max matching string till i
      if(t[i]==p[j]) ind[i]=j+1,i++,j++;
      if(j==sz(p)) j=lps[j-1];
      else if(i<sz(t) && t[i]!=p[j]) {
	if(!j) ind[i]=0,i++; else j=lps[j-1];
}}}};
