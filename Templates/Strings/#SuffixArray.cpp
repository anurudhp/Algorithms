const int MAXN = 100010, LOGN = 18;
int blk[MAXN], sa[MAXN], cnt[MAXN], b[MAXN], tmp[MAXN], fast[MAXN];

void suffix_array(const string &s){
  int n = SZ(s);
  REP(i, n) sa[i] = n-i-1;
  stable_sort(sa, sa+n,[&](int i, int j){return s[i]<s[j];});
  REP(i, n) blk[i]=s[i];
  for(int len=1;len<n;len*=2){
    REP(i, n) b[i]=blk[i],tmp[i]=sa[i]-len,cnt[i]=i;
    REP(i,n)
      blk[sa[i]]=i&&b[sa[i-1]]==b[sa[i]]&&sa[i-1]+len<n&&b[sa[i-1]+len/2]==b[sa[i]+len/2]?blk[sa[i-1]]:i;
    REP(i,n) fast[i]=(tmp[i]>=0?blk[tmp[i]]:-1);
    REP(i,n) if(~fast[i]) sa[cnt[fast[i]]++]=tmp[i];
  }
}
vector<int> kasai(string &s){
  int n = SZ(s), k = 0;
  VI lcp(n),inv(n);
  REP(i,n) inv[sa[i]] = i;
  REP(i,n){
    if(k<0) k = 0;
    if(inv[i]==n-1){ k=0; continue; }
    for(int j=sa[inv[i]+1];i+k<n&&j+k<n&&s[i+k]==s[j+k];++k);
    lcp[inv[i]] = k--;
  }
  return lcp;
}
int LCP[LOGN][MAXN], msb[MAXN], dollar[MAXN];
void build_msb(){ int mx = -1;
  REP(i,MAXN) { if (i >= (1 << (mx+1))) mx++; msb[i]=mx; }
}
void build_LCP(string& s){ const int n = SZ(s);
  auto lcp = kasai(s);
  REP(i,n-1) {//Build the LCP array in O(NlogN)
    int ret = lcp[i];
    if(ret >= dollar[sa[i]]-sa[i]) ret=dollar[sa[i]]-sa[i];
    LCP[0][i] = ret; //LCP[i] shouldnt exceed dollar[SA[i]]
  } //dollar[i] : index of dollar to the right of i.
  LCP[0][n-1]=10*MAXN;
  FOR(i,1,LOGN) {//O(1) RMQ structure in O(NlogN)
    int add = (1<<(i-1));if(add>=n)break;//small optimization
    REP(j,n) { if(j+add<n) {
        LCP[i][j] = min(LCP[i-1][j],LCP[i-1][j+add]);
      } else { LCP[i][j] = LCP[i-1][j]; }
} } }

int lcp(int x,int y) { if(x==y) return dollar[sa[x]]-sa[x];
  //O(1) LCP.x & y are indexes of the suffix in SA!
  if(x>y) {swap(x,y);} y--;
  int idx=msb[y-x+1],sub=(1<<idx);
  return min(LCP[idx][x],LCP[idx][y-sub+1]);
}
