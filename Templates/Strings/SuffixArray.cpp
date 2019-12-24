//LCP[0][i]= len(LCP) of SA[i] & SA[i+1](sorted suffixes).
//RA[i][j] = Rank of suffix S[j...j+2^i]
//SA[i] = i’th Lexicographically smallest suffix’s index.
int RA[LOGN][N],SA[N],tempSA[N],cnt[N],msb[N];
int LCP[LOGN][N],dollar[N];
void countingSort(int l,int k,int n) { SET(cnt, 0);
  REP(i,n) { int idx=(i+k<n ? RA[l][i+k] : 0); cnt[idx]++; }
  int maxi = max(300,n), sum = 0;
  REP(i,maxi) { int t=cnt[i]; cnt[i]=sum; sum+=t; }
  REP(i,n){ int idx = SA[i] + k < n ? RA[l][SA[i]+k] : 0;
    tempSA[cnt[idx]++]=SA[i];
  } REP(i,n)SA[i]=tempSA[i];
}
void build_SA(string &s) { const int n = SZ(s);
  REP(i,n) RA[0][i]=s[i], SA[i]=i;
  REP(i, LOGN-1) {
    int k = (1<<i); if (k >= n) break;
    countingSort(i,k,n); countingSort(i,0,n);
    int rank = 0; RA[i+1][SA[0]] = rank;
    FOR(j,1,n) {
      if (RA[i][SA[j]]  == RA[i][SA[j-1]]
      && RA[i][SA[j]+k] == RA[i][SA[j-1]+k]) {
        RA[i+1][SA[j]]=rank;
      } else { RA[i+1][SA[j]]=++rank; }
} } }
void build_msb(){ int mx = -1;
  REP(i,N) { if (i >= (1 << (mx+1))) mx++; msb[i]=mx; }
}
void build_LCP(string& s){ const int n = SZ(s);
  REP(i,n-1) {//Build the LCP array in O(NlogN)
    int x = SA[i], y = SA[i+1], ret = 0;
    for(int k = LOGN-1; k>=0 && x<n && y<n; k--) {
      if((1<<k) >= n) continue;
      if(RA[k][x]==RA[k][y]) x += 1<<k, y += 1<<k, ret += 1<<k;
    } if(ret >= dollar[SA[i]]-SA[i]) ret=dollar[SA[i]]-SA[i];
    LCP[0][i] = ret; //LCP[i] shouldnt exceed dollar[SA[i]]
  } //dollar[i] : index of dollar to the right of i.
  LCP[0][n-1]=10*N;
  FOR(i,1,LOGN) {//O(1) RMQ structure in O(NlogN)
    int add = (1<<(i-1));if(add>=n)break;//small optimization
    REP(j,n) { if(j+add<n) {
        LCP[i][j] = min(LCP[i-1][j],LCP[i-1][j+add]);
      } else { LCP[i][j] = LCP[i-1][j]; }
} } }
int lcp(int x,int y) { if(x==y) return dollar[SA[x]]-SA[x];
  //O(1) LCP.x & y are indexes of the suffix in SA!
  if(x>y) {swap(x,y);} y--;
  int idx=msb[y-x+1],sub=(1<<idx);
  return min(LCP[idx][x],LCP[idx][y-sub+1]);
} 
bool equal(int i,int j,int p,int q){
  if(j - i != q - p) return false;
  int idx = msb[j-i+1], sub = (1<<idx);
  return RA[idx][i] == RA[idx][p] && 
  RA[idx][j-sub+1] == RA[idx][q-sub+1];
} //Note : Do not forget to add a terminating ’$’
